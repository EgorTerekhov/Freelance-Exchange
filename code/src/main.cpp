#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "../include/database.hpp"
#include "../include/cli/SignUp.hpp"
#include "../include/cli/SignIn.hpp"
#include "../include/customer.hpp"
#include "../include/performer.hpp"
#include "../include/JsonClass.hpp"
#include "../include/password.hpp"

int main() {
  classes::Database& db = classes::Database::getInstance();
  db.initialize();
  std::cout << "Hello, user" << std::endl;
  bool signup = classes::SignUp();
  if (signup) {
    std::pair<std::string, std::string> signin = classes::SignIn();
    std::cout << signin.first << std::endl;
    std::cout << signin.second << std::endl;
  }
  db.destroy();
  return 0;
}