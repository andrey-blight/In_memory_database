#ifndef DATABASE_INSERT_COMMAND_H
#define DATABASE_INSERT_COMMAND_H

#include <utility>
#include <vector>

#include "ParserCommand.h"
#include "database/column.h"


namespace mem_db {

    class InsertCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<std::string> values;
    public:
        explicit InsertCommand(std::string table_name, std::vector<std::string> values) : table_name(
                std::move(table_name)), values(std::move(values)) {}

        void execute(Database &db) const override;
    };

}

#endif //DATABASE_INSERT_COMMAND_H
