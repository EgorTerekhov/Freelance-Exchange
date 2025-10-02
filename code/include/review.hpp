#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

class Review {
  User* u_from;
  User* u_to;
  Order* o;
  std::string descrip;
  int grade;

  friend class Admin;

 public:
  Review(User* u_from_, User* u_to_, Order* o_, std::string& d_) : u_from(u_from_), u_to(u_to_), o(o_), descrip(d_) {
  }

  void ReDescrip(const std::string& d) {
  }

  int GetScore() {
    return this->grade;
  }
};