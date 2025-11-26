#include "../../include/cli/performercli.hpp"

namespace classes {
  void show_help() {
    std::cout << "Freelance exchange cli application for performer" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "help  - show this help" << std::endl;
    std::cout << "orders - работа с заказами:" << std::endl;
    std::cout << "rate - оценка customer" << std::endl;
    std::cout << "account - описание вашего аккаунта" << std::endl;
    std::cout << "allcustomers - выведет всех заказчиков с их id" << std::endl;
    std::cout << "exit  - выйти из программы" << std::endl;
  }

  void AccountPerformerCli(Performer* p) {
    std::cout << "Ваши данные" << std::endl;
    std::cout << "Логин: " << p->GetLogin() << std::endl;
    std::cout << "Имя: " << p->GetName() << std::endl;
    std::cout << "Email: " << p->GetEmail() << std::endl;
    std::cout << "Телефон: " << p->GetPhone() << std::endl;
    std::cout << "Рейтинг: " << p->GetRate() << std::endl;  
  }

  void AllCustomersPerformerCli() {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Customer>>& customers = db.GetCustomerArr();
    for (const auto& c : customers) {
      std::cout << "Логин: " << c->GetLogin() << " id: " << c->GetId() << std::endl;
    }
  }

  bool PerformerOrders(Perfomer* p) {
    std::cout << "Вам доступны следующие функции: " << std::endl;
    std::cout << "work orders - покажет над какими заказами вы работаете" << std::endl;
    std::cout << "all orders - покажет какие заказы сейчас вы можете взять" << std::endl;
    std::cout << "work on \"id\" - взять потенциально (если вас примет заказчик) в работу заказ с выбранным id, который вы можете узнать через all orders" << std::endl;
    std::cout << "stop - чтобы выйти из функции" << std::endl;
    std::cout << "exit - чтобы завершить программу" << std::endl;
    std::string enter;
    while (true && enter != "stop" && enter != "exit") {
      std::getline(std::cin, enter);
      if (enter == "work orders") {
        WorkOrdersPerformerCli(p);
      } else if (enter == "all orders") {
        AllOrdersPerformerCli(p);
      } else if (enter.find("work on") == 0) {
        std::string id_part = enter.substr(7);
        size_t first_non_space = id_part.find_first_not_of(' ');
        if (first_non_space != std::string::npos) {
          id_part = id_part.substr(first_non_space);
        }
        if (!id_part.empty() && std::all_of(id_part.begin(), id_part.end(), ::isdigit)) {
          int order_id = std::stoi(id_part);
          workOnOrder(order_id, p->Getid());
        } else {
          std::cout << "Ошибка: после 'work on' должен быть указан числовой ID без пробелов" << std::endl;
        }
      } else if (enter == "stop") {
        break;
      } else if (enter == "exit") {
        break;
      } else {
        std::cout << "Неизвестная команда, введите еще раз" << std::endl;
      }
      }
    if (enter == "stop") {
      return true;
    }
    return false;
  }

  void workOnOrder(int id_order, int id_performer) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int o = db.BinSearchDelete<Order>(id_order, orders);
    if (o != -1) {
      orders[o]->Getarrperformer().pushback(id_performer);
      std::cout << "Успешно добавились в очередь к заявке" << std::endl;
    } else {
      std::cout << "Такого заказа нет" << std::endl;
    }
  }

  void WorkOrdersPerformerCli(Perfomer* p) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int i = 0;
    for (const auto& order : orders) {
      if (order.GetStatus() == OrderStatus::WORK && order.GetPerformer() == p->GetId()) {
        ++i;
        std::cout << "id заказа : " << order->GetId() << std::endl;
        std::cout << "название : " << order->GetName() << std::endl;
        std::cout << "цена : " << order->GetPrice() << std::endl;
        std::cout << "описание : " << order->GetDescription() << std::endl;
        std::cout << "id заказчика : " << order->GetCustomer() << std::endl;
        std::cout << std::endl;
      }
    }
    if (i = 0) {
      std::cout << "заказов в работе нет" << std::endl;
    }
  }

  void AllOrdersPerformerCli() {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    if (orders.empty()) {
      std::cout << "Заказов нет" << std::endl;
      return;
    }
    for (const auto& order : orders) {
      if (order.GetStatus() == OrderStatus::WAIT) {
        std::cout << "id заказа : " << order.GetId() << std::endl;
        std::cout << "название : " << order.GetName() << std::endl;
        std::cout << "цена : " << order.GetPrice() << std::endl;
        std::cout << "описание : " << order.GetDescription() << std::endl;
        std::cout << "id заказчика : " << order.GetCustomer() << std::endl;
        std::cout << std::endl;
      }
    }
  }

  bool RatePerformerCli(Performer* p) {
    std::cout << "Вы можете оценить customer, чьи заказы вы выполняли" << std::endl;
    std::string enter;
    Database& db = Database::getInstance();
    while (true && enter != "stop" && enter != "exit") {
      std::cout << "введите id customer (введите stop чтобы выйти из функции или exit, чтобы завершить программу): ";
      std::getline(std::cin, enter);
      if (enter == "exit") {
        break;
      } else if (enter == "stop") {
        break
      } else if (!enter.empty() && std::all_of(enter.begin(), enter.end(), ::isdigit)) {
        int customer_id = std::stoi(enter);
        int c = db.BinSearchDelete<Customer>(customer_id, db.GetCustomerArr());
        if (c != -1) {
          Order* o = db.FindOrder(db.GetCustomerArr()[c]->GetId(), p->GetId());
          if (o) {
            int rate_customer = 0;
            std::cout << "Введите оценку от 0 до 10 в целых числах : ";
            std::cin >> rate_customer;
            db.GetCustomerArr()[c].AddRate(rate_customer);
          } else {
            std::cout << "Нет такого заказа, который вы выполняли, где заказчиком был customer с id " << customer_id << std::endl;
          }
        } else {
          std::cout >> "Нет customer с таким id" << std::endl;
        }
      } else {
        std::cout << "Неизвестная команда, повторите ввод" << std::endl;
      }
    }
    if (enter == "stop") {
      return true;
    }
    return false;
  }

  bool performercli(Perfomer* p) {
    std::cout << "Здравствуй performer, напиши help, если забыл или не знаешь команды, для выхода введи exit" << std::endl;
    std::string enter;
    while (true && enter != "exit") {
      std::getline(std::cin, enter);
      if (enter == "exit") {
        break;
      } else if (enter == "help") {
        show_help();
      } else if (enter == "orders") {
        bool what = PerformerOrders(p);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "rate") {
        bool what = RatePerformerCli(p);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "account") {
        AccountPerformerCli();
      } else if (enter == "allcustomers") {
        AllCustomersPerformerCli();
      } else {
        std::cout << "Неизвестная команда, введите еще раз" << std::endl;
      }
    }
  }
}