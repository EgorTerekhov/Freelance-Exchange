#pragma once
#include <string>
#include "../include/user.hpp"
#include "../include/order.hpp"
#include <string>

namespace classes {

//Поля:
// std::string name;
// std::string login;
// std::string password;

User::User(const std::string& name_, const std::string& login_, const std::string& password_)
    : name(name_), login(login_), password(password_) {
}

std::string User::GetClass() const {
  return "User";
}
}  // namespace classes