#include <gtest/gtest.h>
#include "database/database.h"

// we will create a table with all attributes
TEST(CreateTest, AllAttributes) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} id : int = 0, "
                         "name : string[50], "
                         "{autoincrement} count : int, "
                         "{unique} hash : bytes[8])").status(), true) << "Table created";
}

// table with non-existent type
TEST(CreateTest, NonExistentType) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} id : int = 0, "
                         "name : string[50], "
                         "{autoincrement} count : int, "
                         "{unique} car_type : bigint)").get_error(), "Unsupported column type: bigint")
                        << "don't have bigint type";
}

TEST(CreateTest, UnsupportedCommand) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("sfjdkfjdkiew").get_error(), "Unsupportable command") << "Incorrect command";
}

TEST(CreateTest, IncorrectColumn) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} eff: id : int = 0 = 1, "
                         "name : string[50], "
                         "{autoincrement} count : int, "
                         "{unique} car_type : bigint)").get_error(), "Invalid column definition: {key}eff:id:int=0=1")
                        << "Incorrect column description";

}

TEST(CreateTest, EqulentColumns) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} id : int = 0, "
                         "name : string[50], "
                         "{autoincrement} id : int)").get_error(), "Column id already exist")
                        << "Incorrect column description";

}

TEST(CreateTest, EqulentTables) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} id : int = 0, "
                         "name : string[50], "
                         "{autoincrement} count : int, "
                         "{unique} hash : bytes[8])").status(), true);

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} user_id : int = 0)").get_error(), "Table users already exist") << "Same table names";

}

TEST(CreateTest, DefaultValues) {
    mem_db::Database db;

    EXPECT_EQ(db.execute("CREATE TABLE users "
                         "( {key} id : int = 0, "
                         "name : string[50] = \"user\", "
                         "is_admin : bool = false , "
                         "{unique} login_hash : bytes[10] = \"abcd\" ,"
                         "{unique} hash : bytes[8] = 0xabcdef)").status(), true);

}