#include <gtest/gtest.h>
#include "database/database.h"

// we will create a table with all attributes
TEST(IncludeTest, AllTypes) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "(id : int, "
                         "name : string[50], "
                         "is_admin : bool, "
                         "hash : bytes[8])").status(), true);

    EXPECT_EQ(db.execute("INSERT (1, \"Andrey\", true, 0xabcdef12) to users").status(), true);
}

TEST(IncludeTest, EqInsert) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "(id : int, "
                         "name : string[50], "
                         "is_admin : bool, "
                         "hash : bytes[8])").status(), true);

    EXPECT_EQ(
            db.execute(R"(INSERT (id=1, name="Andrey:"Kizhinov"", is_admin=true, hash=0xabcdef12) to users)").status(),
            true);
}


TEST(IncludeTest, DiffStatements) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "(id : int, "
                         "name : string[50], "
                         "is_admin : bool, "
                         "hash : bytes[8])").status(), true);

    EXPECT_EQ(db.execute("INSERT (id=1, \"Andrey\", is_admin=true, hash=0xabcdef12) to users").get_error(),
              "different statement (with = and without) in one request") << "Incorrect command";

    EXPECT_EQ(db.execute("INSERT (1, \"Andrey\", true, hash=0xabcdef12) to users").get_error(),
              "different statement (with = and without) in one request") << "Incorrect command";

}

TEST(IncludeTest, BadCol) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "(id : int, "
                         "name : string[50], "
                         "is_admin : bool, "
                         "hash : bytes[8])").status(), true);

    EXPECT_EQ(db.execute("INSERT (ids=1, name=\"Andrey\", is_admin=true, hash=0xabcdef12) to users").get_error(),
              "No such column: ids") << "Incorrect command";
}

TEST(IncludeTest, AutoValues) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "({autoincrement, unique} id : int, "
                         "name : string[50], "
                         "is_admin : bool=false, "
                         "hash : bytes[8])").status(), true);

    EXPECT_EQ(db.execute("INSERT (, \"Andrey\",   , 0xabcdef12) to users").status(), true);
    EXPECT_EQ(db.execute("INSERT (name=\"Andrey\", is_admin=false, hash=0xabcdef12) to users").status(), true);

}

TEST(IncludeTest, UniqueError) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "({unique} id : int)").status(), true);

    EXPECT_EQ(db.execute("INSERT (1) to users").status(), true);

    EXPECT_EQ(db.execute("INSERT (1) to users").get_error(), "Cell id is unique");
}

TEST(IncludeTest, Autoincrement) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "({autoincrement, unique} id : int,"
                         " {autoincrement} count: int)").status(), true);

    EXPECT_EQ(db.execute("INSERT (0,) to users").status(), true);
    EXPECT_EQ(db.execute("INSERT (,) to users").status(), true);

}

TEST(IncludeTest, ErrorDefault) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "({autoincrement, unique} id : int,"
                         "name: string[20])").status(), true);

    EXPECT_EQ(db.execute("INSERT (0,) to users").get_error(), "Cell name don't have default value");

    EXPECT_EQ(db.execute("CREATE TABLE main "
                         "({autoincrement, unique} id : int,"
                         "{unique} name: string[20] = \"A\")").status(), true);
    EXPECT_EQ(db.execute("INSERT (,) to main").status(), true);

    EXPECT_EQ(db.execute("INSERT (,) to main").get_error(), "Cell name is unique");
}
