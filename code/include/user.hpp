#pragma once

#include <string>

class Review;

namespace classes {
class User {
  std::string login_;
  std::string password_;
  std::string name_; //access rights нахуй не надо тк это в методох будет прописано
 public:
  virtual void CreateProfile(std::string name_, std::string login_, std::string password_) = 0;
  virtual void Login(std::string login_, std::string password_) = 0;
  virtual void HandleReview(std::shared_ptr<Review> review) = 0;
  virtual std::vector<std::string> GetOptions() = 0; // будем выводить список действий, которые может сделать конкретный класс
};
}  // namespace classes