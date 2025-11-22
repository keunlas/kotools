// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/sqlite/sqlite3.h"

#include <cstring>
#include <format>
#include <stdexcept>

#include "sqlite3/sqlite3.h"

namespace kotools::sqlite {

SQLite3::SQLite3(const std::string_view& db_name) : db_name_(db_name) {
  auto errcode = sqlite3_open(db_name.data(), &db_);
  if (errcode != SQLITE_OK) {
    db_ = nullptr;
    auto errstr = sqlite3_errstr(errcode);
    if (errstr == nullptr) errstr = "Unknown error";
    throw std::runtime_error(
        std::format("Failed to open SQLite database '{}': {} (code {})",
                    db_name, errstr, errcode));
  }
}

SQLite3::SQLite3(SQLite3&& other) {
  db_name_ = std::move(other.db_name_);
  db_ = other.db_;
  other.db_ = nullptr;
}

SQLite3& SQLite3::operator=(SQLite3&& other) {
  if (this == &other) {
    return *this;
  }

  auto tmp_db = db_;

  db_name_ = std::move(other.db_name_);
  db_ = other.db_;
  other.db_ = nullptr;

  if (tmp_db) {
    sqlite3_close_v2(tmp_db);
  }

  return *this;
}

SQLite3::~SQLite3() {
  if (db_) {
    sqlite3_close_v2(db_);
    db_ = nullptr;
  }
}

int SQLite3::close() {
  auto errcode = sqlite3_close(db_);
  if (errcode == SQLITE_OK) {
    db_ = nullptr;
  }
  return errcode;
}

void SQLite3::exec(const std::string_view& sql) {
  char* errstr = nullptr;
  int errcode = sqlite3_exec(db_, sql.data(), nullptr, nullptr, &errstr);

  if (errcode != SQLITE_OK) {
    std::string msg = errstr ? errstr : "Unknown error";
    sqlite3_free(errstr);
    throw std::runtime_error(
        std::format("Failed to execute SQL: {}\nError SQL: {}", msg, sql));
  }
}

void SQLite3::exec(const std::string_view& sql, ExecCallback callback) {
  auto c_callback = [](void* context, int col_size, char** col_values,
                       char** col_names) -> int {
    auto* cb = static_cast<ExecCallback*>(context);
    TableRow row;
    for (int i = 0; i < col_size; i++) {
      std::string col_name = col_names[i];
      std::string value = col_values[i] ? col_values[i] : "";
      row[col_name] = value;
    }
    bool success = (*cb)(row);
    return success ? 0 : 1;
  };
  char* errstr = nullptr;
  int errcode = sqlite3_exec(db_, sql.data(), c_callback, &callback, &errstr);
  if (errcode != SQLITE_OK) {
    std::string msg = errstr ? errstr : "Unknown error";
    sqlite3_free(errstr);
    throw std::runtime_error(std::format(
        "Failed to execute SQL with callback: {}\nError SQL: {}", msg, sql));
  }
}

}  // namespace kotools::sqlite
