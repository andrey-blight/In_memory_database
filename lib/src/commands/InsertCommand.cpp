#include "database/commands/InsertCommand.h"
#include "database/database.h"

#include <iomanip>

namespace mem_db {
    void InsertCommand::execute(Database &db) const {
        Row row;
        std::shared_ptr<Table> table = db.get_tables()[table_name];
        auto &columns = table->get_columns();
        auto &col_names = table->get_col_names();

        for (int i = 0; i < values.size(); ++i) {
            std::string value;
            std::string col_name;

            if (eq_statement) {
                size_t eq_pos = values[i].find('=');
                col_name = values[i].substr(0, eq_pos);
                value = values[i].substr(eq_pos + 1, values[i].length() - eq_pos);
            } else {
                value = values[i];
                col_name = col_names[i];
            }

            if (columns.find(col_name) == columns.end()) {
                throw std::runtime_error("No such column: " + col_name);
            }

            const Column &current_col = (*columns.find(col_name)).second;

            if (current_col.type == "int") {
                row[col_name] = std::stoi(value);
            } else if (current_col.type == "bool") {
                row[col_name] = value == "true";
            } else if (current_col.type == "string") {
                row[col_name] = value.substr(0, current_col.length);
            } else if (current_col.type == "bytes") {
                std::vector<uint8_t> bytes;

                for (size_t j = 0; j < current_col.length; j += 2) {
                    std::string byte_str = value.substr(j, 2);
                    auto byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
                    bytes.push_back(byte);
                }

                row[col_name] = bytes;
            }
        }


        table->insert_row(row);
    }
}


