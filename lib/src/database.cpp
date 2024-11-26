#include <database/database.h>

namespace mem_db {
    Response Database::execute(const std::string &query) {
        // execute SQL command
        try {
            std::unique_ptr<ParserCommand> value = SQLParser::parse_query(query);
            return value->execute(*this);
        }
        catch (const std::runtime_error &ex) {
            return {static_cast<std::string>(ex.what())};
        }
    }


}
