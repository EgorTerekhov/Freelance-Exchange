#include "../../include/cli/SignIn.hpp"

namespace classes {
  bool CheckLoginIn(const std::string& login) {
    if (login.empty()) {
      return false;
    }
    std::regex pattern("^[a-z0-9]+$");
    return std::regex_match(login, pattern);
  }

  bool CheckPassIn(const std::string& pas) {
    if (pas.empty()) {
      return false;
    }
    std::regex pattern(R"(^[A-Z](?=.+\d)[a-z\d_-]{6,}$)"); //начинается с зглавной, затем минимум 5 символов, обязательно есть цифра (буквы, цифры, _-)
    return std::regex_match(pas, pattern);
  }

  std::pair<std::string, std::string> SignIn() {
    std::pair<std::string, std::string> vec("", "");
    std::string login;
    std::string pass;
    bool exit = false;
    while (true && !exit) {
      std::cout << "enter your login: ";
      std::getline(std::cin, login);
      if (login == "exit") {
        exit = true;
        break;
      }
      std::cout << "enter your password: ";
      std::getline(std::cin, pass);
      if (pass == "exit") {
        exit = true;
        break;
      }
      bool signin = PasswordAuth::SignInUser(login, pass);
      if (signin) {
        std::cout << "Вы успешно вошли" << std::endl;
        break;
      } else {
        std::cout << "Неправильный логин или пароль" << std::endl;
      }
    }
    if (exit) {
      return vec;
    }
    vec.first = login;
    vec.second = pass;
    return vec;
  }
}