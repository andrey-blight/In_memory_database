#ifndef DATABASE_COLUMN_H
#define DATABASE_COLUMN_H

#include <string>
#include <map>
#include <utility>
#include <variant>
#include <vector>
#include <optional>
#include <stdexcept>

namespace mem_db {
    using Cell = std::variant<int, std::string, bool, std::vector<uint8_t>>;
    using Row = std::map<std::string, Cell>;

    class Column {
    private:
        std::vector<Cell> values{};
        int autoincrement{0};
    public:
        Column(std::string name, std::string type, bool is_unique, bool is_autoincrement,
               std::optional<Cell> default_value, size_t length) : name(std::move(name)), type(std::move(type)),
                                                                   is_unique(is_unique),
                                                                   is_autoincrement(is_autoincrement),
                                                                   default_value(std::move(default_value)),
                                                                   length(length) {}

        Column(const Column &col) = default;

        std::string name;
        std::string type;
        bool is_unique;
        bool is_autoincrement;
        std::optional<Cell> default_value;
        size_t length; // length only for string type and byte type

        Cell get_value();

        void add_value(const Cell &val);

        bool has_value(const Cell &value);
    };

}

#endif //DATABASE_COLUMN_H
