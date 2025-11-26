#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "../database.hpp"
#include "../customer.hpp"
#include "../performer.hpp"
#include "../password.hpp"

namespace classes {
  bool CheckLoginUp(const std::string& login);
  bool CheckNameUp(const std::string& name);
  bool CheckPassUp(const std::string& pas);
  bool CheckEmailUp(const std::string& email);
  bool CheckPhoneUp(const std::string& phone);
  bool SignUp(); // без админа
}