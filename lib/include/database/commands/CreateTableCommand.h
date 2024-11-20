#ifndef DATABASE_CREATE_TABLE_COMMAND_H
#define DATABASE_CREATE_TABLE_COMMAND_H

#include "ParserCommand.h"
#include "database/column.h"

namespace mem_db {
    class Table;

    class Logger;

    class CreateTableCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<Column> columns;
    public:

        explicit CreateTableCommand(std::string name, const std::vector<Column> &columns) : table_name(std::move(name)),
                                                                                            columns(columns) {}

        void execute(Database &db) const override;
    };

    void CreateTableCommand::execute(Database &db) const {
        auto &tables = db->get_tables();
        if (tables.find(table_name) != tables.end()) {
            throw std::runtime_error("Table " + table_name + " already exist");
        }

        // add a new table to table list
        tables[table_name] =
                std::make_shared<Table>(Table(columns, table_name));

        // move create command to logger for print log
        Logger::create_log(this);
    }
}


#endif //DATABASE_CREATE_TABLE_COMMAND_H
