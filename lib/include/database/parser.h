#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <memory>
#include <string>
#include <regex>
#include <sstream>
#include <utility>

#include "column.h"

namespace mem_db {

    class ParserCommand {
    public:
        virtual ~ParserCommand() = default;

        [[nodiscard]] virtual std::string getType() const = 0;
    };

    // command for execute create table
    class CreateTableCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<Column> columns;
    public:
        [[nodiscard]] std::string getType() const override { return "create"; }

        explicit CreateTableCommand(std::string name, const std::vector<Column> &columns) : table_name(std::move(name)),
                                                                                            columns(columns) {}

        [[nodiscard]] const std::string &get_table_name() const { return table_name; }

        [[nodiscard]] const std::vector<Column> &get_columns() const { return columns; }
    };

    // command for execute create table
    class InsertCommand : public ParserCommand {
    private:
        std::string table_name;
        std::vector<Cell> row;
    public:
        [[nodiscard]] std::string getType() const override { return "insert"; }

        explicit InsertCommand(std::string name, const std::vector<Cell> &row) : table_name(std::move(name)),
                                                                                 row(row) {}

        [[nodiscard]] const std::string &get_table_name() const { return table_name; }

        [[nodiscard]] const std::vector<Cell> &get_row() const { return row; }
    };

    class SQLParser {
    public:
        static std::unique_ptr<ParserCommand> parse_query(const std::string &query);

    private:
        static std::unique_ptr<CreateTableCommand> parse_create_statement(const std::smatch &matches);

        static std::unique_ptr<InsertCommand> parse_insert_statement(const std::smatch &matches);
    };
}

#endif //DATABASE_PARSER_H
