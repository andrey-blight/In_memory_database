#ifndef DATABASE_LOGGER_H
#define DATABASE_LOGGER_H

#include <memory>
#include <iostream>

namespace mem_db {
    class CreateTableCommand;

    class Logger {
    public:
        static void create_log(CreateTableCommand &command); // for CREATE TABLE log
    };
}

#endif //DATABASE_LOGGER_H
