#include "database/commands/SelectCommand.h"
#include "database/database.h"
#include <iostream>

namespace mem_db {
    void SelectCommand::execute(Database &db) const {
        std::cout << "Executing SELECT on table: " << table_name << "\n";
    }
}