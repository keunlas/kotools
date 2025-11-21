// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_SQLITE_SQLITE3_H
#define KOTOOLS_SQLITE_SQLITE3_H

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

struct sqlite3;

namespace kotools::sqlite {

class SQLite3 {
 public:
  using TableRow = std::unordered_map<std::string, std::string>;
  using ExecCallback = std::function<bool(TableRow)>;

 public:
  SQLite3(const std::string_view& db_name);
  SQLite3(SQLite3&& other);
  SQLite3& operator=(SQLite3&& other);
  SQLite3(const SQLite3&) = delete;
  SQLite3& operator=(const SQLite3&) = delete;

  ~SQLite3();
  int close();

  void exec(const std::string_view& sql);
  void exec(const std::string_view& sql, ExecCallback callback);

 private:
  std::string db_name_;
  sqlite3* db_{nullptr};
};

}  // namespace kotools::sqlite

#endif  // !KOTOOLS_SQLITE_SQLITE3_H
