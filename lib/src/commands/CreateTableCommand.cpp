#include "database/commands/CreateTableCommand.h"
#include "database/database.h"

namespace mem_db {
    void CreateTableCommand::execute(Database &db) const {
        std::map<std::string, std::shared_ptr<Table>> &tables = db.get_tables();
        if (tables.find(table_name) != tables.end()) {
            throw std::runtime_error("Table " + table_name + " already exist");
        }

        // add a new table to table list
        tables[table_name] = std::make_shared<Table>(Table(columns, table_name));

        // move create command to logger for print log
        Logger::create_log(const_cast<CreateTableCommand &>(*this));
    }
}
