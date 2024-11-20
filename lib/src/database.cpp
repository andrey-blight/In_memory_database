#include <database/database.h>

namespace mem_db {
    void Database::execute(const std::string &query) {
        // execute SQL command

        std::unique_ptr<ParserCommand> value = SQLParser::parse_query(query);
        value->execute(*this);
    }


}
