#include "database/logger.h"

namespace mem_db {

    void Logger::create_log(std::unique_ptr<CreateTableCommand> command) {
        std::clog << std::boolalpha;
        std::clog << "Created table:\t" << command->get_table_name() << "\n\n";

        std::clog << "Columns:\n";
        for (const auto &col: command->get_columns()) {

            std::clog << "Type:\t" << col.type << "\n"
                      << "Name:\t" << col.name << "\n"
                      << "Primary key:\t" << col.is_primary_key << "\n"
                      << "Autoincrement:\t" << col.is_autoincrement << "\n"
                      << "Unique:\t" << col.is_unique << "\n"
                      << "default_value:\t" << col.default_value << "\n\n";
        }
    }
}