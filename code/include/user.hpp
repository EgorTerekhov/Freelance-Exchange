#pragma once

#include <string>

class Review;

namespace classes {
class User {
  std::string login_;
  std::string password_;
 public:
  User(std::string login, std::string password) : login_(login), password_(password){
  };
  // убрал create profile тк он у всех одинаковый будет и смысла нет в наследовании, а админу он вообще не нужен
  virtual void HandleReview(std::shared_ptr<Review> review) = 0;
  virtual std::vector<std::string> GetOptions() = 0; // будем выводить список действий, которые может сделать конкретный класс
  virtual ~User() = default; //виртуальный деструктор для удаления наследников через указатель на юзера.
};
}  // namespace classes