#include "database/table.h"

namespace mem_db {

    Table::Table(const std::vector<Column> &columns, const std::string &table_name) {
        this->table_name = table_name;

        for (const Column &col: columns) {
            this->columns[col.name] = col;
        }
    }
}