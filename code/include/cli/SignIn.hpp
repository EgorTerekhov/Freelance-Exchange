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
#include "../admin.hpp"

namespace classes {
  bool CheckLoginIn(const std::string& login);
  bool CheckPassIn(const std::string& pas);
  std::pair<std::string, std::string> SignIn();
}