#include <gtest/gtest.h>
#include "database/database.h"

// we will create a table with all attributes
TEST(CreateTest, AllAttributes) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "( {key} id : int = 0, "
               "name : string[50], "
               "{autoincrement} count : int, "
               "{unique} hash : bytes[8])");

    SUCCEED() << "Table created";
}

// table with non-existent type
TEST(CreateTest, NonExistentType) {
    mem_db::Database db;

    EXPECT_THROW(db.execute("CREATE TABLE users "
                            "( {key} id : int = 0, "
                            "name : string[50], "
                            "{autoincrement} count : int, "
                            "{unique} car_type : bigint)"), std::runtime_error) << "don't have bigint type";
}

TEST(CreateTest, UnsupportedCommand) {
    mem_db::Database db;

    EXPECT_THROW(db.execute("sfjdkfjdkiew"), std::runtime_error) << "Incorrect command";
}

TEST(CreateTest, IncorrectColumn) {
    mem_db::Database db;

    EXPECT_THROW(db.execute("CREATE TABLE users "
                            "( {key} eff: id : int = 0 = 1, "
                            "name : string[50], "
                            "{autoincrement} count : int, "
                            "{unique} car_type : bigint)"), std::runtime_error) << "Incorrect column description";

}

TEST(CreateTest, EqulentColumns) {
    mem_db::Database db;

    EXPECT_THROW(db.execute("CREATE TABLE users "
                            "( {key} id : int = 0, "
                            "name : string[50], "
                            "{autoincrement} id : int)"), std::runtime_error) << "Incorrect column description";

}

TEST(CreateTest, EqulentTables) {
    mem_db::Database db;

    db.execute("CREATE TABLE users "
               "( {key} id : int = 0, "
               "name : string[50], "
               "{autoincrement} count : int, "
               "{unique} hash : bytes[8])");

    EXPECT_THROW(db.execute("CREATE TABLE users "
                            "( {key} user_id : int = 0)"), std::runtime_error) << "Same table names";

}
