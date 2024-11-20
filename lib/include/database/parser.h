#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <memory>
#include <string>
#include <regex>
#include <sstream>
#include <utility>
#include <set>

#include "column.h"
#include "commands/ParserCommand.h"
#include "commands/CreateTableCommand.h"
#include "commands/InsertCommand.h"

namespace mem_db {

    class SQLParser {
    public:
        static std::unique_ptr<ParserCommand> parse_query(const std::string &query);

    private:
        static std::unique_ptr<CreateTableCommand> parse_create_statement(const std::smatch &matches);

        static std::unique_ptr<InsertCommand> parse_insert_statement(const std::smatch &matches);
    };
}

#endif //DATABASE_PARSER_H
