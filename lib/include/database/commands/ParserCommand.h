#ifndef DATABASE_PARSER_COMMAND_H
#define DATABASE_PARSER_COMMAND_H

#include <string>
#include "database/response.h"

namespace mem_db {
    class Database;

    class ParserCommand {
    public:
        virtual ~ParserCommand() = default;

        virtual Response execute(Database &db) const = 0;
    };
}

#endif //DATABASE_PARSER_COMMAND_H
