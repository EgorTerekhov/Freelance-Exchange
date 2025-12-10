#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "../include/database.hpp"
#include "../include/cli/SignUp.hpp"
#include "../include/cli/SignIn.hpp"
#include "../include/cli/admincli.hpp"
#include "../include/cli/customercli.hpp"
#include "../include/cli/performercli.hpp"
#include "../include/customer.hpp"
#include "../include/performer.hpp"
#include "../include/JsonClass.hpp"
#include "../include/password.hpp"

int main() {
  classes::Database& db = classes::Database::getInstance();
  db.initialize();
  std::cout << "Hello, user" << std::endl;
  std::string enter;
  std::string login;
  
  while (true && enter != "exit") {
    std::cout << "sign in or sign up (type 1 or 2) or type exit to close programm" << std::endl;
    std::getline(std::cin, enter);
    if (enter == "exit") {
      break;
    }
    if (enter == "1") {
      std::pair<std::string, std::string> signin = classes::SignIn();
      if (signin.first.empty()) {
        enter = "exit";
        break;
      } else {
        login = signin.first;
        break;
      }
    }
    if (enter == "2") {
      bool signup = classes::SignUp();
      if (!signup) {
        enter = "exit";
        break;
      }
    }
  }
  if (enter == "exit") {
    db.destroy();
    return 0;
  }



  classes::Performer* p = db.FindUserByLoginAs<classes::Performer>(login);
  classes::Customer* c = db.FindUserByLoginAs<classes::Customer>(login);
  classes::Admin* a = db.FindUserByLoginAs<classes::Admin>(login);
  if (p) {
    classes::performercli(p);
  }
  if (c) {
    classes::customercli(c);
  }
  if (a) {
    classes::AdminCli(a);
  }

  db.destroy();
  return 0;
}