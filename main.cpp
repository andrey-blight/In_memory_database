#include <database/database.h>

int main() {

    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "({autoincrement} id : int, "
               "name : string[50], "
               "is_admin : bool=false, "
               "{unique} hash : bytes[8])");

//    db.execute("INSERT (, \"Andrey\",, 0xabcdef12) to users");
    db.execute("INSERT (name=\"Andrey\",is_admin=false, hash=0xabcdef12) to users");


    return 0;
}