#include "database/commands/InsertCommand.h"
#include "database/database.h"
#include <iostream>

namespace mem_db {
    void InsertCommand::execute(Database &db) const {
        Row row;
        std::shared_ptr<Table> table = db.get_tables()[table_name];
        auto columns = table->get_columns();

        if (eq_statement) {
            for (const std::string &line: values) {
                auto eq_pos = line.find('=');
                std::string col_name = line.substr(0, eq_pos);
                std::string value = line.substr(eq_pos + 1, line.length() - eq_pos);

                if (columns.find(col_name) == columns.end()) {
                    throw std::runtime_error("No such column: " + col_name);
                }

                row[col_name] = value;
            }
        }

        table->insert_row(row);
    }
}


