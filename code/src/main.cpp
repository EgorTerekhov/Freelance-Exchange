#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "../include/database.hpp"
#include "../include/customer.hpp"
#include "../include/performer.hpp"
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
  std::regex pattern("^[A-Z][a-z]+[a-z]*$");
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
  Database& db = Database::getInstance();
  std::string login;
  std::string pass;
  bool exit = false;
  std::cout << "имя не должно содержать цифр, оно не должно начичинаться с заглавной буквы и все должно быть на латинице\n";
  while (true && !exit) {
    std::cout << "enter your name: ";
    std::getline(std::cin, login);
    if (login == "exit") {
      exit = true;
      break;
    }
  if (login.size() < 10 && login.size() > 3 && CheckLogin(login)) {
    if (db.FindUserByLoginAs<Performer>(login) || db.FindUserByLoginAs<Customer>(login) || db.FindUserByLoginAs<Admin>(login)) {
      std::cout << "такой логин уже есть\n";
    } else {
      std::cout << "great login\n";
      break;
    }
  } else {
      std::cout << "error, pleace repeat or exit: " << login << "\n";
  }
  }
  if (exit) {
    return false;
  }
  std::cout << "пароль должен начинаться с большой буквы, может содержать символы латиницы и цифр\n";
  while (true) {
    std::cout << "enter your password : ";
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
  std::cout << "имя должно начинаться с большой буквы и буквы только латиницы\n";
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
  std::cout << "имейл должен иметь вид email@chtoto.chtoto\n";
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
  std::cout << "только российские номера форматов 89174523333 и тп\n";
  while (true) {
    std::cout << "enter your phone : ";
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
    db.CreateCustomer(std::move(std::make_unique<Customer>(1, login, vec.first, vec.second, name, email, phone, 0)));
  } else if (type == "performer") {
    db.CreatePerformer(std::move(std::make_unique<Performer>(1, login, vec.first, vec.second, name, email, phone, 0)));
  }
  std::cout << "Вы успешно зарегистрировались\n";
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