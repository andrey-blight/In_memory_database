#include <database/database.h>

int main() {

    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    ;


    return 0;
}