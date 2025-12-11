#include "../../include/cli/SignUp.hpp"

namespace classes {
  bool CheckLoginUp(const std::string& login) {
    if (login.empty()) {
      return false;
    }
    std::regex pattern("^[a-z0-9]+$");
    return std::regex_match(login, pattern);
  }

  bool CheckNameUp(const std::string& name) {
    if (name.empty()) {
      return false;
    }
    std::regex pattern("^[A-Z][a-z]+[a-z]*$");
    return std::regex_match(name, pattern);
  }

  bool CheckPassUp(const std::string& pas) {
    if (pas.empty()) {
      return false;
    }
    std::regex pattern(R"(^[A-Z](?=.+\d)[a-z\d_-]{6,}$)"); //начинается с зглавной, затем минимум 5 символов, обязательно есть цифра (буквы, цифры, _-)
    return std::regex_match(pas, pattern);
  }

  bool CheckEmailUp(const std::string& email) {
    if (email.empty()) {
      return false;
    }
    std::regex pattern(R"(^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}$)");
    return std::regex_match(email, pattern);
  }

  bool CheckPhoneUp(const std::string& phone) {
    if (phone.empty()) {
      return false;
    }
    std::regex pattern(R"(^(\+7|7|8)?[- ]?\(?[489]\d{2}\)?[- ]?\d{3}[- ]?\d{2}[- ]?\d{2}$)");
    return std::regex_match(phone, pattern);
  }


  bool SignUp() {
    Database& db = Database::getInstance();
    std::string login;
    std::string pass;
    bool exit = false;
    std::cout << "логин не должно содержать цифр, оно не должно начичинаться с заглавной буквы и все должно быть на латинице\n";
    while (true && !exit) {
      std::cout << "enter your login: ";
      std::getline(std::cin, login);
      if (login == "exit") {
        exit = true;
        break;
      }
    if (login.size() < 10 && login.size() > 3 && CheckLoginUp(login)) {
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
      if (pass.size() > 6 && CheckPassUp(pass)) {
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
      std::cout << "who are you (customer, performer, admin) : ";
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
      if (type == "admin") {
        break;
      }
      std::cout << "unknown type, repeat or exit\n";
    }
    if (exit) {
      return false;
    }

    if (type == "admin") {
      std::pair<std::string, std::string> vec = PasswordAuth::RegUser(login, pass);
      db.CreateAdmin(++db.GetMaxIdUser(), login, vec.first, vec.second);
      std::cout << "Вы успешно зарегистрировались\n";
      return true;
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
      if (CheckNameUp(name)) {
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
      if (CheckEmailUp(email)) {
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
      if (CheckPhoneUp(phone)) {
        break;
      }
      std::cout << "uncorrect phone, repeat or print exit\n";
    }
    if (exit) {
      return false;
    }

    std::pair<std::string, std::string> vec = PasswordAuth::RegUser(login, pass);
    if (type == "customer") {
      db.CreateCustomer(++db.GetMaxIdUser(), login, vec.first, vec.second, name, email, phone);
    } else if (type == "performer") {
      db.CreatePerformer(++db.GetMaxIdUser(), login, vec.first, vec.second, name, email, phone, 0);
    }
    std::cout << "Вы успешно зарегистрировались\n";
    return true;
  }
}