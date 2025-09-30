#pragma once
#include <string>
#include "user.h"
#include "order.h"

class Review {
  User* u_from;
  User* u_to;
  Order* o;
  std::string descrip;
 public:
  
  Review(User* u_from_, User* u_to_, Order* o_, std::string& d_)
        : u_from(u_from_), u_to(u_to_), o(o_), descrip(d_) {
  }

  void ReDescrip(const std::string& d) {
    descrip = d;
  }
};