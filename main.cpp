#include <database/database.h>

int main() {

    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "( {key} id : int = 0, "
               "name : string[50] = \"user\", "
               "is_admin : bool = false , "
               "{unique} login_hash : bytes[10] = \"abcd\" ,"
               "{unique} hash : bytes[8] = 0xabcdef)");


    return 0;
}