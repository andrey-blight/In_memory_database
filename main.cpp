#include <iostream>
#include <database/database.h>

int main() {
    mem_db::Database db;

    db.execute("INSERT (a,b,c) to users");

//    std::cout << "Table created successfully!" << std::endl;

    return 0;
}