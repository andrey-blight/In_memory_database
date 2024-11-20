#include <iostream>
#include <database/database.h>

int main() {
    mem_db::Database db;
    db.execute("CREATE TABLE users (id : int, name:string[30])");
//    db.execute("INSERT (   ,1, \"Andrey Kizhinov\") to users");

    std::cout << "Table created successfully!" << std::endl;

    return 0;
}