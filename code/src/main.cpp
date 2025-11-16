#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "../include/database.hpp"
#include "../include/JsonClass.hpp"
#include "../include/password.hpp"

namespace classes {

bool CheckLogin(const std::string& login) {
  if (login.empty()) {
    return false;
  }
  std::regex pattern("^[a-z0-9]+$");
  return std::regex_match(login, pattern);
}

bool CheckName(const std::string& name) {
  if (name.empty()) {
    return false;
  }
  std::regex pattern(R"(^[A-Z][a-z]+$)");
  return std::regex_match(name, pattern);
}

bool CheckPass(const std::string& pas) {
  if (pas.empty()) {
    return false;
  }
  std::regex pattern(R"(^[A-Z](?=.+\d)[a-z\d_-]{6,}$)"); //начинается с зглавной, затем минимум 5 символов, обязательно есть цифра (буквы, цифры, _-)
  return std::regex_match(pas, pattern);
}

bool CheckEmail(const std::string& email) {
  if (email.empty()) {
    return false;
  }
  std::regex pattern(R"(^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}$)");
  return std::regex_match(email, pattern);
}

bool CheckPhone(const std::string& phone) {
  if (phone.empty()) {
    return false;
  }
  std::regex pattern(R"(^(\+7|7|8)?[- ]?\(?[489]\d{2}\)?[- ]?\d{3}[- ]?\d{2}[- ]?\d{2}$)");
  return std::regex_match(phone, pattern);
}


bool SignUp() { // без админа
  std::string login;
  std::string pass;
  bool exit = false;
  while (true && !exit) {
    std::getline(std::cin, login);
    if (login == "exit") {
      exit = true;
      break;
    }
    if (login.size() < 10 && login.size() > 3 && CheckLogin(login)) {
      std::cout << "great login\n";
      break;
    } else {
      std::cout << "error, pleace repeat or exit : " << login << "\n";
    }
  }
  if (exit) {
    return false;
  }
  while (true) {
    std::getline(std::cin, pass);
    if (pass == "exit") {
      exit = true;
      break;
    }
    if (pass.size() > 6 && CheckPass(pass)) {
      std::cout << "great password \n";
      break;
    } else {
      std::cout << "error, pleace repeat or exit : " << pass << "\n";
    }
  }
  if (exit) {
    return false;
  }
  std::string type;
  while (true) {
    std::cout << "who are you (customer, performer) : ";
    std::getline(std::cin, type);
    if (type == "exit") {
      exit = true;
      break;
    }
    if (type == "customer") {
      break;
    }
    if (type == "performer") {
      break;
    }
    std::cout << "unknown type, repeat or exit\n";
  }
  if (exit) {
    return false;
  }
  std::string name;
  while (true) {
    std::cout << "enter your name : ";
    std::getline(std::cin, name);
    if (name == "exit") {
      exit = true;
      break;
    }
    if (CheckName(name)) {
      break;
    }
    std::cout << "uncorrect name, repeat or print exit\n";
  }
  std::string email;
  while (true) {
    std::cout << "enter your email : ";
    std::getline(std::cin, email);
    if (email == "exit") {
      exit = true;
      break;
    }
    if (CheckEmail(email)) {
      break;
    }
    std::cout << "uncorrect email, repeat or print exit\n";
  }
  if (exit) {
    return false;
  }
  std::string phone;
  while (true) {
    std::cout << "enter your email : ";
    std::getline(std::cin, phone);
    if (phone == "exit") {
      exit = true;
      break;
    }
    if (CheckPhone(phone)) {
      break;
    }
    std::cout << "uncorrect phone, repeat or print exit\n";
  }
  if (exit) {
    return false;
  }

  std::pair<std::string, std::string> vec = PasswordAuth::RegUser(login, pass);
  if (type == "customer") {
    std::vector<std::unique_ptr<Customer>>& cust = Database::GetCustomerArr();
    cust.emplace_back(std::make_unique<Customer>(1, login, vec.first, vec.second, name, email, phone));
  } else if (type == "performer") {
    std::vector<std::unique_ptr<Performer>>& cust = Database::GetPerformerArr();
    cust.emplace_back(std::make_unique<Performer>(1, login, vec.first, vec.second, name, email, phone));
  }
  return true;
}

}

int main() {
  classes::Database& db = classes::Database::getInstance();
  db.initialize();
  std::cout << "Hello, user\n";
  classes::SignUp();
  db.destroy();
  return 0;
}