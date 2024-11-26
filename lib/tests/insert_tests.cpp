#include <gtest/gtest.h>
#include "database/database.h"

// we will create a table with all attributes
TEST(IncludeTest, AllTypes) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    db.execute("INSERT (1, \"Andrey\", true, 0xabcdef12) to users");

    SUCCEED() << "SUCCESS INSERT";
}

TEST(IncludeTest, EqInsert) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    db.execute(R"(INSERT (id=1, name="Andrey:"Kizhinov"", is_admin=true, hash=0xabcdef12) to users)");

    SUCCEED() << "SUCCESS INSERT";
}


TEST(IncludeTest, DiffStatements) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    EXPECT_THROW(db.execute("INSERT (ids=1, name=\"Andrey\", is_admin=true, hash=0xabcdef12) to users"),
                 std::runtime_error) << "Incorrect command";

    EXPECT_THROW(db.execute("INSERT (1, \"Andrey\", true, hash=0xabcdef12) to users"),
                 std::runtime_error) << "Incorrect command";

}

TEST(IncludeTest, BadCol) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "(id : int, "
               "name : string[50], "
               "is_admin : bool, "
               "hash : bytes[8])");

    EXPECT_THROW(db.execute("INSERT (ids=1, name=\"Andrey\", true, hash=0xabcdef12) to users"),
                 std::runtime_error) << "Incorrect command";
}

TEST(IncludeTest, AutoValues) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "({autoincrement} id : int, "
               "name : string[50], "
               "is_admin : bool=false, "
               "hash : bytes[8])");

    db.execute("INSERT (, \"Andrey\",   , 0xabcdef12) to users");
    db.execute("INSERT (name=\"Andrey\", is_admin=false, hash=0xabcdef12) to users");

    SUCCEED() << "SUCCESS INSERT";
}
