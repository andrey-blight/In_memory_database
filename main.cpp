#include <iostream>
#include <database/database.h>

int main() {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "( {key} id : int = 0, "
               "name : string[50], "
               "{autoincrement} count : int, "
               "{unique} weight : double)");

    std::cout << "Table created successfully!" << std::endl;

    return 0;
}