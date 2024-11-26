#include "database/commands/InsertCommand.h"
#include "database/database.h"

namespace mem_db {
    void InsertCommand::execute(Database &db) const {
        Row row;
        std::shared_ptr<Table> table = db.get_tables()[table_name];
        auto &columns = table->get_columns();
        auto &col_names = table->get_col_names();

        for (int i = 0; i < values.size(); ++i) {
            std::string value = values[i];
            std::string col_name;
            Cell insert_val;

            if (eq_statement) {
                size_t eq_pos = values[i].find('=');
                col_name = values[i].substr(0, eq_pos);
                value = value.substr(eq_pos + 1, values[i].length() - eq_pos);
            } else {
                col_name = col_names[i];
            }

            if (columns.find(col_name) == columns.end()) {
                throw std::runtime_error("No such column: " + col_name);
            }

            Column &current_col = (*columns.find(col_name)).second;

            if (value.empty()) {
                insert_val = current_col.get_value();
            } else {
                if (current_col.type == "int") {
                    insert_val = std::stoi(value);
                } else if (current_col.type == "bool") {
                    insert_val = value == "true";
                } else if (current_col.type == "string") {
                    insert_val = value.substr(0, current_col.length);
                } else if (current_col.type == "bytes") {
                    std::vector<uint8_t> bytes;

                    for (size_t j = 0; j < current_col.length; j += 2) {
                        std::string byte_str = value.substr(j, 2);
                        auto byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
                        bytes.push_back(byte);
                    }

                    insert_val = bytes;
                }
            }

            row[col_name] = insert_val;

            if (current_col.is_unique) {
                current_col.add_value(insert_val);
            }
        }


        table->insert_row(row);
    }
}


