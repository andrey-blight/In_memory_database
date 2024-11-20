#include <database/database.h>

namespace mem_db {
    void Database::execute(const std::string &query) {
        // execute SQL command

        std::unique_ptr<ParserCommand> value = SQLParser::parse_query(query);

        // CREATE TABLE query
        if (value->getType() == "create") {
            // try to cast parser command to create table command
            auto *raw_create_cmd = dynamic_cast<CreateTableCommand *>(value.get());

            if (raw_create_cmd) {
                // if successfully cast ParserCommand to CreateCommand get unique ptr
                std::unique_ptr<CreateTableCommand> create_cmd(
                        dynamic_cast<CreateTableCommand *>(value.release())
                );

                const std::string new_table_name = create_cmd->get_table_name();

                if (tables.find(create_cmd->get_table_name()) != tables.end()) {
                    throw std::runtime_error("Table " + new_table_name + " already exist");
                }

                // add a new table to table list
                tables[create_cmd->get_table_name()] =
                        std::make_shared<Table>(Table(create_cmd->get_columns(), create_cmd->get_table_name()));

                // move create command to logger for print log
                Logger::create_log(std::move(create_cmd));
            } else {
                throw std::runtime_error("Invalid command type");
            }
        }
    }


}
