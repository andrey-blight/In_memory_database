#include <database/column.h>

namespace mem_db {
    Cell Column::get_value() {
        if (is_autoincrement) {
            if (!is_unique) {
                return autoincrement++;
            }

            while (has_value(autoincrement)) {
                ++autoincrement;
            }

            return autoincrement;
        }

        if (!default_value.has_value()) {
            throw std::runtime_error("Cell " + name + " don't have default value");
        }

        if (is_unique && has_value(default_value.value())) {
            throw std::runtime_error("Cell " + name + " is unique");
        }

        return default_value.value();
    }

    void Column::add_value(const mem_db::Cell &val) {
        values.push_back(val);
    }

    bool Column::has_value(const mem_db::Cell &value) {
        return std::ranges::any_of(values, [&value](const Cell &element) {
            return value.index() == element.index() && value == element;
        });
    }
}