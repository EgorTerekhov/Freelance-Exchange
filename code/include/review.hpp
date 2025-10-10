#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

namespace classes {
class Review {
  User* u_from;
  User* u_to;
  Order* o;
  std::string descrip;
  int grade;

  friend class Admin;

 public:
  Review(User* u_from_, User* u_to_, Order* o_, std::string& d_);

  void ReDescrip(const std::string& d);

  int GetScore() {
    return this->grade;
  }
};
}  // namespace classes