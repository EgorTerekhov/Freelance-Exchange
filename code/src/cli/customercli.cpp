#include "../../include/cli/customercli.hpp"
namespace classes {

  bool CheckNameOrder(std::string& tmp) {
    if (tmp.empty()) {
      return false;
    }
    std::regex pattern("^[A-Z][a-z]+[a-z]*$");
    return std::regex_match(tmp, pattern);
  }

  void help_order() {
    std::cout << "Вам доступны следующие функции: " << std::endl;
    std::cout << "create order - сможете в этой функции создать заказ" << std::endl;
    std::cout << "handle order - сможете изменить содержание заказов, которые еще не в работе" << std::endl;
    std::cout << "work orders - покажет над какими вашими заказами уже работают" << std::endl;
    std::cout << "complete order \"id\" - завершить заказ с определенным id" << std::endl;
    std::cout << "wait orders - покажет какие заказы вы создали, но над которыми еще не работают" << std::endl;
    std::cout << "done orders - завершенные заказы, которые вы создавали" << std::endl;
    std::cout << "potential performers to \"id\" - покажет потенциальных performer на заказ" << std::endl;
    std::cout << "choise \"id_performer\" to \"id_order\" - выбрать для проекта определенного performer, после этого проект считается в работе" << std::endl;
    std::cout << "stop - чтобы завершить работу с orders" << std::endl;
    std::cout << "exit - чтобы завершить работу программы" << std::endl;
  }

  void help_review() {
    std::cout << "Вам доступны следующие функции работы с ревью: " << std::endl;
    std::cout << "all review - показать все ревью, которые вы создавали" << std::endl;
    std::cout << "create review on \"id\" - сделать ревье на заказ с определенным id" << std::endl;
    std::cout << "delete review - удалить ревью" << std::endl;
    std::cout << "stop - чтобы завершить работу с orders" << std::endl;
    std::cout << "exit - чтобы завершить работу программы" << std::endl;
  }

  void show_help_customer() {
    std::cout << "Freelance exchange cli application for customer" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "help  - show this help" << std::endl;
    std::cout << "orders - работа с заказами:" << std::endl;
    std::cout << "review - работа с отзывами" << std::endl;
    std::cout << "account - описание вашего аккаунта" << std::endl;
    std::cout << "allperformers - выведет всех perfromer с их id и ролью" << std::endl;
    std::cout << "exit  - выйти из программы" << std::endl;
  }

  void AllPerformersCustomerCli() {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Performer>>& performers = db.GetPerformerArr();
    for (const auto& p : performers) {
      std::cout << "Логин: " << p->GetLogin() << " id: " << p->GetId() << std::endl;
    }
  }

  void AccountCustomerCli(Customer* c) {
    std::cout << "Ваши данные" << std::endl;
    std::cout << "Логин: " << c->GetLogin() << std::endl;
    std::cout << "Имя: " << c->GetName() << std::endl;
    std::cout << "Email: " << c->GetEmail() << std::endl;
    std::cout << "Телефон: " << c->GetPhone() << std::endl;
    std::cout << "Рейтинг: " << c->GetRate() << std::endl;  
  }

  void AllReviewCustomerCli(Customer* c) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Review>>& reviews = db.GetReviewArr();
    int i = 0;
    for (const auto& review : reviews) {
      if (review->GetUFrom() == c->GetId()) {
        ++i;
        std::cout << "id review : " << review->GetId() << std::endl;
        std::cout << "id_from : " << review->GetUFrom() << std::endl;
        std::cout << "id_to : " << review->GetUTo() << std::endl;
        std::cout << "order_id : " << review->GetOrderId() << std::endl;
        std::cout << "description : " << review->GetDescription() << std::endl;
        std::cout << "grade : " << review->GetGrade() << std::endl;
        std::cout << std::endl;
      }
    }
    if (i == 0) {
      std::cout << "Вы не создавали ни разу review" << std::endl;
    }
  }
  
  bool createReviewCustomerCli(Customer* c, int order_id) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    auto it = std::find_if(orders.begin(), orders.end(), 
                [order_id](std::unique_ptr<Order>& order) {
                  return order->GetId() == order_id;
    });
    if (it == orders.end()) {
      std::cout << "Такого заказа не существует" << std::endl;
      return true;
    }
    Order* found_order = it->get();
    if (found_order->GetCustomerId() != c->GetId()) {
      std::cout << "Это не ваш заказ" << std::endl;
      return true;
    }
    std::vector<std::unique_ptr<Review>>& reviews = db.GetReviewArr();
    auto it_review = std::find_if(reviews.begin(), reviews.end(), 
                [found_order](std::unique_ptr<Review>& review) {
                  return found_order->GetId() == review->GetOrderId();
    });
    if (it_review != reviews.end()) {
      std::cout << "Вы уже создавали review на этот заказ, вы можете только удалить его" << std::endl;
      return true;
    }
    std::cout << "напишите stop чтобы выйти из функции или exit, чтобы завершить работу программы)" << std::endl;
    int id_to = 0;
    std::string id_to_str;
    while (true && id_to_str != "exit" && id_to_str != "stop") {
      std::cout << "Введите id_performer: ";
      std::getline(std::cin, id_to_str);
      std::regex pattern(R"(^\d+$)");
      if (id_to_str == "exit" || id_to_str == "stop") {
        break;
      }
      if (std::regex_match(id_to_str, pattern)) {
        id_to = std::stoi(id_to_str);
        int iter = db.BinSearchDelete<Performer>(id_to, db.GetPerformerArr());
        if (iter == -1) {
          std::cout << "performer с таким id не существует, он либо удален, либо вы неправильно ввели" << std::endl;
        }
        break;
      } else {
        std::cout << "неправильный ввод, должны быть только цифры без пробелов" << std::endl;
      }
    }
    if (id_to_str == "stop") {
      return true;
    }
    if (id_to_str == "exit") {
      return false;
    }
    std::string description;
    while (true && description != "exit" && description != "stop") {
      std::cout << "Введите описание ревью : ";
      std::getline(std::cin, description);
      break;
    }
    if (description == "stop") {
      return true;
    }
    if (description == "exit") {
      return false;
    }
    double grade;
    std::string grade_str;
    while (true && grade_str != "exit" && grade_str != "stop") {
      std::cout << "Введите оценку за заказ (от 0 до 10): ";
      std::getline(std::cin, grade_str);
      std::regex pattern(R"(^\d+$)");
      if (grade_str == "exit" || grade_str == "stop") {
        break;
      }
      if (std::regex_match(grade_str, pattern)) {
        grade = std::stod(grade_str);
        if (grade <= 0.0 || grade >= 10.0) {
          std::cout << "неправильный ввод, число должно быть от 0 до 10" << std::endl;
        } else {
          break;
        }
      } else {
        std::cout << "неправильный ввод, должны быть только цифры без пробелов" << std::endl;
      }
    }
    db.CreateReview(++db.GetMaxIdReview(), c->GetId(), id_to, order_id, description, grade);
    return true;
  }

  bool ReviewCustomerCli(Customer* c) {
    std::string enter;
    while (true && enter != "exit" && enter != "stop") {
      std::cout << "Введите команду (введите helpReview, если нужна помощь): ";
      std::getline(std::cin, enter);
      if (enter == "helpReview") {
        help_review();
      } else if (enter == "all review") {
        AllReviewCustomerCli(c);
      } else if (std::regex_match(enter, std::regex(R"(create review on \d+)"))) {
        std::regex pattern(R"(create review on (\d+))");
        std::smatch matches;
        if (std::regex_search(enter, matches, pattern) && matches.size() == 2) {
          int id_order = std::stoi(matches[1].str());
          bool what = createReviewCustomerCli(c, id_order);
          if (!what) {
            enter = "exit";
            break;
          }
        }
      } else if (enter == "delete review") {
        bool what = DeleteReviewCustomerCli(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "stop") {
        return true;
      } else if (enter == "exit") {
        return false;
      } else {
        std::cout << "Неизвестная команда" << std::endl;
      }
    }
    return false;
  }

  bool ChoisePerformertoOrder(int id_order, int id_performer, int cust_id) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Performer>>& performers = db.GetPerformerArr();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int perf_id = db.BinSearchDelete(id_performer, performers);
    size_t ord_id = static_cast<size_t>(db.BinSearchDelete(id_order, orders));
    if (perf_id == -1) {
      std::cout << "performer с таким id не существует" << std::endl;
      return false;
    }
    if (ord_id == static_cast<size_t>(-1)) {
      std::cout << "order с таким id не существует" << std::endl;
      return false;
    }
    if (orders[ord_id]->GetCustomerId() != cust_id) {
      std::cout << "это не ваш заказ" << std::endl;
      return false;
    }
    if (orders[ord_id]->GetStatus() != OrderStatus::WAIT) {
      std::cout << "заказ уже находится в работе";
      return false;
    }
    orders[ord_id]->ChangePerformer(id_performer);
    orders[ord_id]->ChangeStatus(OrderStatus::WORK);
    return true;
  }

  bool createOrderCustomerCli(Customer* c) {
    Database& db = Database::getInstance();
    std::cout << "напишите stop чтобы выйти из функции или exit, чтобы завершить работу программы)" << std::endl;
    std::string name;
    while (true && name != "exit" && name != "stop") {
      std::cout << "введите название заказа: ";
      std::getline(std::cin, name);
      if (!CheckNameOrder(name)) {
        std::cout << "неправильный формат, название должно начинаться с большой буквы и содержать только буквы латиницы" << std::endl;
      } else {
        break;
      }
    }
    if (name == "stop") {
      return true;
    }
    if (name == "exit") {
      return false;
    }
    double price;
    std::string price_str;
    while (true && price_str != "exit" && price_str != "stop") {
      std::cout << "Введите цену за заказ: ";
      std::getline(std::cin, price_str);
      std::regex pattern(R"(^\d+$)");
      if (price_str == "exit" || price_str == "stop") {
        break;
      }
      if (std::regex_match(price_str, pattern)) {
        price = std::stod(price_str);
        break;
      } else {
        std::cout << "неправильный ввод, должны быть только цифры без пробелов" << std::endl;
      }
    }
    if (price_str == "stop") {
      return true;
    }
    if (price_str == "exit") {
      return false;
    }
    std::string description;
    while (true && description != "exit" && description != "stop") {
      std::cout << "Введите описание заказа : ";
      std::getline(std::cin, description);
      break;
    }
    if (description == "stop") {
      return true;
    }
    if (description == "exit") {
      return false;
    }
    std::string status = "WAIT";
    db.CreateOrder(++db.GetMaxIdOrder(), name, price, description, c->GetId(), -1, status);
    return true;
  }

  bool HandleOrderCustomerCli(Customer* c) {
    int order_id = 0;
    std::string order_id_str;
    while (true && order_id_str != "exit" && order_id_str != "stop") {
      std::cout << "Введите order id : ";
      std::getline(std::cin, order_id_str);
      std::regex pattern(R"(^\d+$)");
      if (!std::regex_match(order_id_str, pattern)) {
        std::cout << "Некорректно введен id, повторите попытку" << std::endl;
        continue;
      }
      order_id = std::stoi(order_id_str);
      return c->HandleOrder(order_id); // мб стоит сюда переписать, но оч лень как будто. Там можно просто enter протыкать и всё.
    }
    if (order_id_str == "stop") {
      return true;
    }
    return true;
  }
  void WorkOrderCustomerCli(Customer* c) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int i = 0;
    for (const auto& order : orders) {
      if (order->GetCustomerId() == c->GetId() && order->GetStatus() == OrderStatus::WORK) {
        ++i;
        std::cout << "id заказа : " << order->GetId() << std::endl;
        std::cout << "название : " << order->GetName() << std::endl;
        std::cout << "цена : " << order->GetPrice() << std::endl;
        std::cout << "описание : " << order->GetDescription() << std::endl;
        std::cout << "id исполнителя : " <<  order->GetPerformerId() << std::endl;
        std::cout << std::endl;
      }
    }
    if (i == 0) {
      std::cout << "заказов в работе нет" << std::endl;
    }
  }
  void WaitOrderCustomerCli(Customer* c) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int i = 0;
    for (const auto& order : orders) {
      if (order->GetCustomerId() == c->GetId() && order->GetStatus() == OrderStatus::WAIT) {
        ++i;
        std::cout << "id заказа : " << order->GetId() << std::endl;
        std::cout << "название : " << order->GetName() << std::endl;
        std::cout << "цена : " << order->GetPrice() << std::endl;
        std::cout << "описание : " << order->GetDescription() << std::endl;
        std::cout << "id исполнителя : " <<  order->GetPerformerId() << std::endl;
        std::cout << std::endl;
      }
    }
    if (i == 0) {
      std::cout << "заказов в ожидании нет" << std::endl;
    }
  }
  void DoneOrderCustomerCli(Customer* c) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    int i = 0;
    for (const auto& order : orders) {
      if (order->GetCustomerId() == c->GetId() && order->GetStatus() == OrderStatus::DONE) {
        ++i;
        std::cout << "id заказа : " << order->GetId() << std::endl;
        std::cout << "название : " << order->GetName() << std::endl;
        std::cout << "цена : " << order->GetPrice() << std::endl;
        std::cout << "описание : " << order->GetDescription() << std::endl;
        std::cout << "id исполнителя : " <<  order->GetPerformerId() << std::endl;
        std::cout << std::endl;
      }
    }
    if (i == 0) {
      std::cout << "завершенных заказов нет" << std::endl;
    }
  }
  void PotentialPerformersCustomerCli(Customer* c, int order_id) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    size_t id = static_cast<size_t>(db.BinSearchDelete<Order>(order_id, orders));
    if (id == static_cast<size_t>(-1)) {
      std::cout << "Заказа с таким id не существует" << std::endl;
      return;
    }
    if (orders[id]->GetCustomerId() != c->GetId()) {
      std::cout << "Этот заказ вам не принадлежит" << std::endl;
    }
    std::vector<std::unique_ptr<Performer>>& performers = db.GetPerformerArr();
    for (const auto& performer : orders[id]->Getarrperformer()) {
      size_t performer_id = static_cast<size_t>(db.BinSearchDelete<Performer>(performer, performers));
      if (performer_id != static_cast<size_t>(-1)) {
        std::cout << performers[performer_id]->GetId() << " - " << performers[performer_id]->GetLogin() << std::endl;
      }
    }
  }

  bool DeleteReviewCustomerCli(Customer* c) {
    int review_id = 0;
    std::string review_id_str;
    std::cout << "Здесь вы можете только удалить ревью" << std::endl;
    while (true && review_id_str != "exit" && review_id_str != "stop") {
      std::cout << "Введите review id : ";
      std::getline(std::cin, review_id_str);
      std::regex pattern(R"(^\d+$)");
      if (!std::regex_match(review_id_str, pattern)) {
        std::cout << "Некорректно введен id, повторите попытку" << std::endl;
        continue;
      }
      review_id = std::stoi(review_id_str);
      c->HandleReview(review_id); // мб стоит сюда переписать, но оч лень как будто. Там можно просто enter протыкать и всё.
      return true;
    }
    if (review_id_str == "exit") {
      return false;
    }
    return true;
  }

  void CompeteOrderCustomerCli(Customer* c, int id_order) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    size_t id = static_cast<size_t>(db.BinSearchDelete<Order>(id_order, orders));
    if (id == static_cast<size_t>(-1)) {
      std::cout << "Заказа с таким id не существует" << std::endl;
      return;
    }
    if (orders[id]->GetCustomerId() != c->GetId()) {
      std::cout << "Этот заказ вам не принадлежит" << std::endl;
    }
    orders[id]->ChangeStatus(OrderStatus::DONE);
    std::cout << "Вы успешно поменяли статус" << std::endl;
  }

  bool customerOrders(Customer* c) {
    std::string enter;
    while (true && enter != "stop" && enter != "exit") {
      std::cout << "Введите команду (helpOrder, если нужна помощь): ";
      std::getline(std::cin, enter);
      if (enter == "stop") {
        return true;
      }
      if (enter == "exit") {
        return false;
      }
      if (enter == "helpOrder") {
        help_order();
      } else if (enter == "create order") {
        bool what = createOrderCustomerCli(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "handle order") {
        bool what = HandleOrderCustomerCli(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "work orders") {
        WorkOrderCustomerCli(c);
      } else if (enter == "wait orders") {
        WaitOrderCustomerCli(c);
      } else if (std::regex_match(enter, std::regex(R"(choise \d+ to \d+)"))) {
        std::regex pattern(R"(choise (\d+) to (\d+))");
        std::smatch matches;
        if (std::regex_search(enter, matches, pattern) && matches.size() == 3) {
          int id_performer = std::stoi(matches[1].str());
          int id_order = std::stoi(matches[2].str());
          ChoisePerformertoOrder(id_order, id_performer, c->GetId());
        }
      } else if (std::regex_match(enter, std::regex(R"(potential performers to \d+)"))) {
        std::regex pattern_(R"(potential performers to (\d+))");
        std::smatch matches_;
        if (std::regex_search(enter, matches_, pattern_) && matches_.size() == 2) {
          int id_order = std::stoi(matches_[1].str());
          PotentialPerformersCustomerCli(c, id_order);
        }
      } else if (enter == "done orders") {
        DoneOrderCustomerCli(c);
      } else if (std::regex_match(enter, std::regex(R"(complete order \d+)"))) {
        std::regex pattern__(R"(complete order (\d+))");
        std::smatch matches__;
        if (std::regex_search(enter, matches__, pattern__) && matches__.size() == 2) {
          int id_order = std::stoi(matches__[1].str());
          CompeteOrderCustomerCli(c, id_order);
        }
      } else {
        std::cout << "Неверный вход" << std::endl;
      }
    }
    if (enter == "stop") {
      return true;
    }
    return false;
  }
  
  void customercli(Customer* c) {
    std::cout << "Здравствуй customer, напиши help, если забыл или не знаешь команды, для выхода введи exit" << std::endl;
    std::string enter;
    while (true && enter != "exit") {
      std::cout << "Введите команду (или напиши help, чтобы показать все возможности): ";
      std::getline(std::cin, enter);
      if (enter == "exit") {
        break;
      } else if (enter == "help") {
        show_help_customer();
      } else if (enter == "orders") {
        bool what = customerOrders(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else if (enter == "account") {
        AccountCustomerCli(c);
      } else if (enter == "allperformers") {
        AllPerformersCustomerCli();
      } else if (enter == "review") {
        bool what = ReviewCustomerCli(c);
        if (!what) {
          enter = "exit";
          break;
        }
      } else {
        std::cout << "Неизвестная команда, введите еще раз" << std::endl;
      }
    }
  }
}