#include "database/commands/SelectCommand.h"
#include "database/database.h"
#include <iostream>

namespace mem_db {
    Response SelectCommand::execute(Database &db) const {
        std::cout << "Executing SELECT on table: " << table_name << "\n";

        return {true};
    }
}