#include <iostream>
#include <database/database.h>

int main() {

    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    db.execute("INSERT (1, \"Andrey\", true, 0xabcdef12) to users");

    return 0;
}