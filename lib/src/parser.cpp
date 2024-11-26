#include <database/parser.h>
#include <iostream>

namespace mem_db {
    std::unique_ptr<ParserCommand> SQLParser::parse_query(const std::string &query) {
        // regex for all types of query
        std::regex create_table_regex(
                R"(^\s*CREATE\s+TABLE\s+([A-Za-z_]\w*)\s*\((.+)\)\s*$)",
                std::regex_constants::icase);
        std::regex insert_regex(
                R"(^\s*INSERT\s+\(([^)]+)\)\s+TO\s+([A-Za-z_][\w]*)\s*$)",
                std::regex_constants::icase);

        // check what query we have by matching with all regex
        std::smatch matches;
        if (std::regex_match(query, matches, create_table_regex)) {
            return parse_create_statement(matches);
        } else if (std::regex_match(query, matches, insert_regex)) {
            return parse_insert_statement(matches);
        } else {
            throw std::runtime_error("Unsupportable command");
        }
    }

    std::unique_ptr<CreateTableCommand> SQLParser::parse_create_statement(const std::smatch &matches) {
        // regex for parse column parameters
        std::regex column_regex(
                R"(^\s*(\{.*?\})?\s*([A-Za-z_]\w*)\s*:\s*([A-Za-z_]\w*(?:\[\d+\])?)\s*(?:=\s*(.+))?\s*$)");

        std::string table_name = matches[1];
        std::string columns_str = matches[2];


        std::vector<std::string> column_definitions; // column separated by comma

        // parse column (we have comma inside {} like {key, autoincrement}, so we need could not just split by a comma)
        size_t start_column = 0, depth = 0;
        for (size_t i = 0; i < columns_str.length(); ++i) {
            if (columns_str[i] == '{') {
                ++depth;  // if we inside {} set depth + 1
            } else if (columns_str[i] == '}') {
                --depth;  // if we exit {} set depth -1
            } else if (columns_str[i] == ',' && depth == 0) {
                // push column if we find it
                column_definitions.push_back(columns_str.substr(start_column, i - start_column));
                start_column = i + 1;
            }
        }
        // push last column
        column_definitions.emplace_back(columns_str.substr(start_column));

        // Убираем пробелы вокруг колонок
        for (auto &col: column_definitions) {
            col.erase(std::remove_if(col.begin(), col.end(), ::isspace),
                      col.end());
        }

        std::vector<Column> columns; // array where we will store column objects
        std::set<std::string> used_names;

        for (auto &column: column_definitions) {

            // parse column
            std::smatch column_matches;
            if (!std::regex_match(column, column_matches, column_regex)) {
                throw std::runtime_error("Invalid column definition: " + column);
            }

            // get definition
            std::string attributes = column_matches[1];
            std::string name = column_matches[2];
            std::string type = column_matches[3];
            std::string default_value = column_matches[4];

            std::cout << default_value << "\n";

            if (used_names.find(name) != used_names.end()) {
                throw std::runtime_error("Column " + name + " already exist");
            }
            used_names.insert(name);

            // parse attributes
            bool is_unique =
                    attributes.find("unique") != std::string::npos || attributes.find("key") != std::string::npos;
            bool is_autoincrement = attributes.find("autoincrement") != std::string::npos;

            // parse type and length
            size_t length = 0;
            if (type.find('[') != std::string::npos) {

                // if we have type[length] parse length
                size_t start = type.find('[') + 1;
                size_t end = type.find(']');
                length = std::stoi(type.substr(start, end - start));
                type = type.substr(0, start - 1);
            }

            // check allowed types
            if (type != "int" && type != "bool" && type != "string" && type != "bytes") {
                throw std::runtime_error("Unsupported column type: " + type);
            }

            Column col{name, type, is_unique, is_autoincrement, default_value, length};
            // push column
            columns.push_back(col);
        }

        return std::make_unique<CreateTableCommand>(CreateTableCommand{table_name, columns});
    }

    std::unique_ptr<InsertCommand> SQLParser::parse_insert_statement(const std::smatch &matches) {
        std::string table_name = matches[2]; // get table name
        std::string all_values = matches[1]; // create values stream for splitting by comma
        std::vector<std::string> values;

        // parse column (we have comma inside {} like {key, autoincrement}, so we need could not just split by a comma)
        size_t start_column = 0;
        int status = 0; // 0 — not inside ", 1 — inside "
        for (size_t i = 0; i < all_values.length(); ++i) {
            if (all_values[i] == '\"' && status == 0) { // if it first " set we inside
                ++status;  // if we inside {} set depth + 1
            } else if (all_values[i] == '\"' &&
                       (status == 1 || status == 2)) { // if we already inside or has > 1 " (like "some "name" here")
                status = 2;  // if we exit {} set depth -1
            } else if (all_values[i] == ',' && (status == 2 || status == 0)) { // coma after closed "
                // push column if we find it
                values.push_back(all_values.substr(start_column, i - start_column));
                start_column = i + 1;
            }
        }
        // push last column
        values.emplace_back(all_values.substr(start_column));

        bool eq_statement = false;
        bool first = true;

        for (std::string &value: values) {
            // delete trailing and leading spaces
            const size_t new_begin = value.find_first_not_of(" \t");

            if (new_begin != std::string::npos) {
                const size_t new_end = value.find_last_not_of(" \t");
                value = value.substr(new_begin, new_end - new_begin + 1);
            } else if (!value.empty()) {
                // this branch means we have value like "  \t " and we need delete spaces.
                value = "";
            }

            if (value.empty()) {
                values.push_back(value);
                continue;
            }

            // if we have value like col_name=value we will watch only on value.
            auto start_search = value.begin();
            size_t eq_pos = value.find('=');
            size_t quote_pos = value.find('\"');
            if (eq_pos != std::string::npos && (quote_pos == std::string::npos || eq_pos < quote_pos)) {
                if (!eq_statement && !first) {
                    throw std::runtime_error("different statement (with = and without) in one request");
                }
                eq_statement = true;
                start_search += static_cast<std::string::difference_type>(eq_pos + 1);
            } else {
                if (eq_statement && !first) {
                    throw std::runtime_error("different statement (with = and without) in one request");
                }
                eq_statement = false;
            }
            first = false;

            size_t start_index, length;
            // if value like "something" -> something
            if (*start_search == '"' && *(value.end() - 1) == '"') {
                start_index = std::distance(value.begin(), start_search) + 1; // skip first "
                length = value.size() - start_index - 1;                     // len before second "
            } else if (*start_search == '0' && start_search + 1 != value.end() && *(start_search + 1) == 'x') {
                start_index = std::distance(value.begin(), start_search) + 2; // skip 0x
                length = value.size() - start_index;
            } else {
                start_index = 0;
                length = value.size() - start_index;
            }

            if (eq_statement && start_index != 0) {
                value = value.substr(0, std::distance(value.begin(), start_search)) +
                        value.substr(start_index, length);
            } else {
                value = value.substr(start_index, length);
            }
        }

        return std::make_unique<InsertCommand>(InsertCommand(eq_statement, table_name, values));
    }
}
