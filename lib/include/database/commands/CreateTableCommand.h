#ifndef DATABASE_CREATE_TABLE_COMMAND_H
#define DATABASE_CREATE_TABLE_COMMAND_H

#include "ParserCommand.h"
#include "database/column.h"

#include <vector>

namespace mem_db {

    class CreateTableCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<Column> columns;
    public:

        explicit CreateTableCommand(std::string name, const std::vector<Column> &columns) : table_name(std::move(name)),
                                                                                            columns(columns) {}

        [[nodiscard]] std::string get_table_name() const { return table_name; }

        [[nodiscard]] std::vector<Column> get_columns() const { return columns; }

        void execute(Database &db) const override;
    };

}

#endif //DATABASE_CREATE_TABLE_COMMAND_H
