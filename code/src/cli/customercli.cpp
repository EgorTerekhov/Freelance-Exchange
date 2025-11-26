#include "../../include/cli/customercli.hpp"

namespace classes {
  void show_help() {
    std::cout << "Freelance exchange cli application for customer" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "help  - show this help" << std::endl;
    std::cout << "orders - работа с заказами:" << std::endl;
    std::cout << "review - работа с отзывами" << std::endl;
    std::cout << "rate - оценка performer" << std::endl;
    std::cout << "account - описание вашего аккаунта" << std::endl;
    std::cout << "allperformers - выведет всех perfromer с их id и ролью" << std::endl;
    std::cout << "exit  - выйти из программы" << std::endl;
  }

  bool createOrderCustomerCli(Customer* c) {

  }

  void AllPerformersCustomerCli() {

  }

  void AccountCustomerCli() {
    
  }

  void ReviewCustomerCli(Customer* c) {

  }

  bool RateCustomerCli(Customer* c) {

  }

  void AllOrdersCustomerCli() {

  }

  bool customerOrders(Customer* c) {

  }

  bool customercli(Customer* c) {
    std::cout << "Здравствуй customer, напиши help, если забыл или не знаешь команды, для выхода введи exit" << std::endl;
    std::string enter;
    while (true && enter != "exit") {
      std::getline(std::cin, enter);
      if (enter == "exit") {
        break;
      } else if (enter == "help") {
        show_help();
      } else if (enter == "orders") {
        bool what = customerOrders(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "rate") {
        bool what = RateCustomerCli(p);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "account") {
        AccountCustomerCli();
      } else if (enter == "allperformers") {
        AllPerformersCustomerCli();
      } else if (enter == "review") {
        ReviewCustomerCli(c);
      } else {
        std::cout << "Неизвестная команда, введите еще раз" << std::endl;
      }
    }
  }
}