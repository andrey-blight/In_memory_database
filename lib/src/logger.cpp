#include "database/logger.h"
#include "database/commands/CreateTableCommand.h"

namespace mem_db {

    void Logger::create_log(CreateTableCommand &command) {
        std::clog << std::boolalpha;
        std::clog << "Created table:\t" << command.get_table_name() << "\n\n";

        std::clog << "Columns:\n";
        for (const auto &col: command.get_columns()) {

            std::clog << "Type:\t" << col.type << "\n"
                      << "Name:\t" << col.name << "\n"
                      << "Primary key:\t" << col.is_primary_key << "\n"
                      << "Autoincrement:\t" << col.is_autoincrement << "\n"
                      << "Unique:\t" << col.is_unique << "\n"
                      << "Default_value:\t" << col.default_value << "\n"
                      << "Length:\t" << col.length << "\n\n";
        }
    }
}