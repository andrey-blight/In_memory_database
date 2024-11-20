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

namespace mem_db {

    // command for execute create table
//    class InsertCommand : public ParserCommand {
//    private:
//        std::string table_name;
//        std::vector<Cell> row;
//    public:
//        [[nodiscard]] std::string getType() const override { return "insert"; }
//
//        explicit InsertCommand(std::string name, const std::vector<Cell> &row) : table_name(std::move(name)),
//                                                                                 row(row) {}
//
//        [[nodiscard]] const std::string &get_table_name() const { return table_name; }
//
//        [[nodiscard]] const std::vector<Cell> &get_row() const { return row; }
//    };

    class SQLParser {
    public:
        static std::unique_ptr<ParserCommand> parse_query(const std::string &query);

    private:
        static std::unique_ptr<CreateTableCommand> parse_create_statement(const std::smatch &matches);

//        static std::unique_ptr<InsertCommand> parse_insert_statement(const std::smatch &matches);
    };
}

#endif //DATABASE_PARSER_H
