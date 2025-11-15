// чет тут писать надо, в cpp файлы мб нужно перенести реализацию методов. 
// в main должны лежать сценарии, как пользоваться кодом и как через командную строку взаимодействовать вообще
#include <iostream>
#include <string>
#include <map>

void show_help() {
  std::cout << "Freelance exchange cli application\n";
  std::cout << "Available commands:\n";
  std::cout << "help  - show this help\n";
  std::cout << "options - show you what actions you can perform on the freelance exchange\n"
  std::cout << "exit  - exit the program\n";
}

void SignUp() {
}

void SignIn() {
}

void CheckLoginSignUp() {
}

void CheckPassSignUp() {
}

void CheckLoginSignIn() {
}

void CheckLoginSignUp() {
}

void CheckName() {
}

void CheckEmail() {
}

void CheckExit() {
}

int main() {
  // std::cout << "Welcome to freelance_exchange CLI!\n";
  // std::coit << "sign in or sign up (type 1 or 2): ";
  // std::string enter;
  // while (true && enter != "exit") {
  //   std::getline(std::cin, enter);
  //   if (enter == "exit") {
  //     break;
  //   }
  //   if (enter == "1") {
  //     std::cout << "type login and password\n";
  //     std::string login;
  //     std::string pass;
  //     std::cout << "login: ";
  //     std::getline(std::cin, login);
  //     std::cout << "pass: ";
  //     std::getline(std::cin, pass);
  //     // тут чек функция на существование таких логинов и паролей. Далее получаем все данные по пользователю
  //   } else if (enter == "2") {
  //     // нужно делать проверку на корректность символов пароля и логина
  //     bool continue = true; // нужно, чтоб цикл блокнуть, если где-то exit написали
  //     std::cout << "type login and password\n";
  //     std::string login;
  //     std::string pass;
  //     std::cout << "login: ";
  //     std::getline(std::cin, login);
  //     // if login correct
  //     std::cout << "pass: ";
  //     std::getline(std::cin, pass);
  //     // if pass correct && continue;
  //     std::cout << "type who are you (performer, customer): ";
  //     std::string type;
  //     while (true && continue) {
  //       std::getline(std::cin, type);
  //       if (type == "exit") {
  //         enter = "exit";
  //         continue = false;
  //         break;
  //       }
  //       if (type == "performer") {
  //         break;
  //       } else if (type == "customer") {
  //         break;
  //       } else {
  //         std::cout << "Unknown type: " << type << "\n";
  //         std::cout << "repeat or type exit to break programm\n";
  //       }
  //     }
  //     if (!continue) {
  //       enter = "exit";
  //       break;
  //     } // возможно часто придется такое писать
  //     std::cout << "type your name: ";
  //     std::string name;
  //     std::getline(std::cin, name);
  //     // if name correct && continue
  //     std::cout << "type your email: ";
  //     std::string email;
  //     std::getline(std::cin, name);
  //     // if email correct && continue
  //     std::cout << "type your phone: ";
  //     std::string phone;
  //     std::getline(std::cin, phone);
  //     // if name correct && continue
  //   } else {
  //     std::cout << "Unknown command: " << enter << "\n";
  //     std::cout << "repeat or type exit to break programm\n";
  //   }
  // }

  // if (enter == "exit") {
  //   return 0;
  // }
  // std::cout << "Type 'help' for available commands.\n\n";
  
  // std::string input;
  // while (true) {
  //     std::cout << "simple_cli> ";
  //     std::getline(std::cin, input);
      
  //     if (input == "hello") {
  //         std::cout << "hello, user\n";
  //     }
  //     else if (input == "help") {
  //         show_help();
  //     }
  //     else if (input == "exit") {
  //         std::cout << "Goodbye!\n";
  //         break;
  //     }
  //     else if (!input.empty()) {
  //         std::cout << "Unknown command: " << input << "\n";
  //         std::cout << "Type 'help' for available commands.\n";
  //     }
  // }
  
  return 0;
}