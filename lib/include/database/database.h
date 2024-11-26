#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "parser.h"
#include "table.h"
#include "logger.h"
#include "response.h"

namespace mem_db {
    class Database {
    private:
        std::map<std::string, std::shared_ptr<Table>> tables{};
    public:
        Database() : tables({}) {}

        [[nodiscard]] std::map<std::string, std::shared_ptr<Table>> &get_tables() { return tables; }

        Response execute(const std::string &query);
    };
}

#endif //DATABASE_DATABASE_H
