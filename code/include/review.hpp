#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

namespace classes {
class Review {
  int id_;
  User* u_from_;
  User* u_to_;
  Order* o_;
  std::string description_;
  int grade_;

 public:
  Review(int id, User* u_from, User* u_to, Order* o, std::string& d);

  User* GetFrom() const {
  }
  
  User* GetTo() const {
  }

  int GetScore() {
  }
};
}  // namespace classes