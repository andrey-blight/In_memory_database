#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <utility>
#include <vector>

#include "parser.h"
#include "column.h"

namespace mem_db {

    class Table {
    private:
        std::string table_name;
        std::vector<Column> columns;
    public:
        explicit Table(const std::vector<Column> &columns, std::string table_name) : columns(columns),
                                                                                     table_name(
                                                                                             std::move(table_name)) {}

        [[nodiscard]] const std::string &get_table_name() const { return table_name; }

        [[nodiscard]] const std::vector<Column> &get_columns() const { return columns; }
    };
}

#endif