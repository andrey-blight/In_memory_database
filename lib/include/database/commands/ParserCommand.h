#ifndef DATABASE_PARSER_COMMAND_H
#define DATABASE_PARSER_COMMAND_H

#include <string>

namespace mem_db {
    class Database;

    class ParserCommand {
    public:
        virtual ~ParserCommand() = default;

        virtual void execute(Database &db) const = 0;
    };
}

#endif //DATABASE_PARSER_COMMAND_H
