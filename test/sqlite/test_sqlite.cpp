#include <format>
#include <iostream>
#include <stdexcept>

#include "kotools/sqlite/sqlite3.h"

int main() {
  using namespace kotools::sqlite;
  
  SQLite3 db("test.db");
  try {
    db.exec("create table if not exists users (id integer primary key autoincrement, name text);");
    db.exec("insert into users (id, name) values (1, 'Alice');");
    db.exec("insert into users (id, name) values (2, 'Bob');");
    db.exec("insert into users (name) values ('Charlie');");
    db.exec("select * from users;", [](SQLite3::TableRow row) {
      std::cout << "User ID: " << row["id"] << ", Name: " << row["name"] << '\n';
      return true;  // Continue iteration
    });
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
