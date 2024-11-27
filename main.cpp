#include <database/database.h>

int main() {

    mem_db::Database db;
    db.execute("CREATE TABLE main "
               "({autoincrement, unique} id : int,"
               "{unique} name: string[20] = \"A\")");
    db.execute("INSERT (,) to main");

    auto val = db.execute("INSERT (,) to main").get_error();

    std::cout << val;
//
//    db.execute("INSERT (1, \"Andrey\") to users");
//    db.execute("INSERT (name=\"Vadim\", id=2) to users");

//    db.execute("SELECT id, name from users where something");

    return 0;
}