#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include <vector>
#include "column.h"

namespace mem_db {

    class Response {
    private:
        std::vector<Row> resp;
        bool is_ok;
        std::string error;
    public:
        bool status() const { return is_ok; }

        std::string get_error() const { return error; }

        using iterator = std::vector<Row>::iterator;
        using const_iterator = std::vector<Row>::const_iterator;

        iterator begin() { return resp.begin(); }

        iterator end() { return resp.end(); }

        const_iterator begin() const { return resp.cbegin(); }

        const_iterator end() const { return resp.cend(); }

        const_iterator cbegin() const { return resp.cbegin(); }

        const_iterator cend() const { return resp.cend(); }
    };
}

#endif //DATABASE_RESPONSE_H
