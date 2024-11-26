#include <database/database.h>

int main() {

    mem_db::Database db;

//    db.execute("CREATE TABLE users "
//               "( id : int, "
//               "name : string[50])");
//
//    db.execute("INSERT (1, \"Andrey\") to users");
//    db.execute("INSERT (name=\"Vadim\", id=2) to users");

    db.execute("SELECT id, name from users where something");

    return 0;
}