#include "database/table.h"

namespace mem_db {

    Table::Table(const std::vector<Column> &columns, const std::string &table_name) {
        this->columns = columns;
        this->table_name = table_name;

        // create map column_name -> index
        for (int i = 0; i < columns.size(); ++i) {
            this->column_to_index[this->columns[i].name] = i;
        }
    }
}