#ifndef DATABASE_COLUMN_H
#define DATABASE_COLUMN_H

#include <string>
#include <map>

namespace mem_db {
    struct Column {
        std::string name;
        std::string type;
        bool is_unique;
        bool is_primary_key;
        bool is_autoincrement;
        std::string default_value;
        size_t length; // length only for string type and byte type
    };

    using Cell = std::variant<int, std::string, bool, std::vector<uint8_t>>;
    using Row = std::map<std::string, Cell>;
}

#endif //DATABASE_COLUMN_H
