#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

namespace classes {
//Поля:
// User* u_from;
// User* u_to;
// Order* o;
// std::string descrip;

Review::Review(User* u_from_, User* u_to_, Order* o_, std::string& d_)
    : u_from(u_from_), u_to(u_to_), o(o_), descrip(d_) {
}

void Review::ReDescrip(const std::string& d) {
  descrip = d;
}
}  // namespace classes