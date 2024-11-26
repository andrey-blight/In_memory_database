#ifndef DATABASE_SELECT_COMMAND_H
#define DATABASE_SELECT_COMMAND_H

#include <utility>
#include <vector>
#include <iostream>

#include "ParserCommand.h"

namespace mem_db {

    class SelectCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<std::string> values;
    public:
        explicit SelectCommand(std::string table_name, std::vector<std::string> values) :
                table_name(std::move(table_name)),
                values(std::move(values)) {}

        Response execute(Database &db) const override;
    };

}
#endif //DATABASE_SELECT_COMMAND_H
