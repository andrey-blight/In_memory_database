#ifndef DATABASE_LOGGER_H
#define DATABASE_LOGGER_H

#include <memory>
#include <iostream>
#include "parser.h"

namespace mem_db {
    class Logger {
    public:
        static void create_log(std::unique_ptr<CreateTableCommand> command); // for CREATE TABLE log
    };
}

#endif //DATABASE_LOGGER_H
