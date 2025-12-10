#pragma once

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class User {
 protected:
  int id_;
  // при создании performer, admin, customer присваивается id_ = -1, затем вызывается функция из database (std::move(item) делаем там) и там уже корректный id присваивается
  std::string login_;
  std::string password_;
  std::string salt_;

 public:
  User(int id, std::string login, std::string password, std::string salt);
  // убрал create profile тк он у всех одинаковый будет и смысла нет в наследовании, а админу он вообще не нужен
  virtual void HandleReview(int id) = 0;
  virtual ~User() = default;  //виртуальный деструктор для удаления наследников через указатель на юзера.
  std::string GetSalt() const { return salt_; }
  std::string GetHash() const { return password_; }
  std::string GetLogin() const { return login_; }
};
}  // namespace classes