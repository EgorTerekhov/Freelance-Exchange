#include "../include/customer.hpp"
#include "../include/database.hpp"
#include "../include/order.hpp"
#include "../include/review.hpp"
#include "../include/nlohmann/json.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <regex>

using json = nlohmann::json;

namespace classes {

Customer::Customer(int id, std::string login, std::string password, std::string salt,
                   std::string name, std::string email,
                   std::string phone, double rate)
    : User(id, std::move(login), std::move(password), std::move(salt)), name_(std::move(name)), email_(std::move(email)), phone_(std::move(phone)), rate_() {
      if (rate != 0) {
        rate_.push_back(rate);
      }
    }

bool Customer::HandleOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1) {
    std::cout << "Заказа с таким id не существует" << std::endl;
    return true;
  }
  if (!arr[iter_search]) {
    std::cout << "Заказ уже был удален" << std::endl;
    return true;
  }
  if (arr[iter_search]->GetStatus() != OrderStatus::WAIT) {
    std::cout << "Заказ не находится в режиме wait" << std::endl;
    return true;
  }

  std::string input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "Current name: " << arr[iter_search]->GetName()
            << " | Enter new name (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (input == "exit") {
      return false;
    }
    if (input == "stop") {
      return true;
    }
    std::regex pattern("^[A-Z][a-z]+[a-z]*$");
    if (!input.empty()) {
      if (!std::regex_match(input, pattern)) {
        std::cout << "Неверный ввод имени, повторите" << std::endl;
        continue;
      }
      arr[iter_search]->ChangeName(input);
      break;
    }
    break;
  }

  while (true) {
    std::cout << "Current price: " << arr[iter_search]->GetPrice()
            << " | Enter new price (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (input == "exit") {
      return false;
    }
    if (input == "stop") {
      return true;
    }
    if (!input.empty()) {
      std::regex pattern(R"(^\d+$)");
      if (!std::regex_match(input, pattern)) {
        std::cout << "Некорректно введен price, повторите попытку" << std::endl;
        continue;
      }
      double new_price = std::stod(input);
      arr[iter_search]->ChangePrice(new_price);
    }
    break;
  }

  while (true) {
    std::cout << "Current description: " << arr[iter_search]->GetDescription()
              << " | Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (input == "exit") {
      return false;
    }
    if (input == "stop") {
      return true;
    }
    std::regex pattern("^[A-Z][a-z]+[a-z]*$");
    if (!input.empty()) {
      if (!std::regex_match(input, pattern)) {
        std::cout << "Неверный ввод описания, повторите" << std::endl;
        continue;
      }
      arr[iter_search]->ChangeDescription(input);
      break;
    }
    break;
  }

  while (true) {
    std::cout << "Current performer: " << arr[iter_search]->GetPerformerId()
            << " | Enter new performer (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (input == "exit") {
      return false;
    }
    if (input == "stop") {
      return true;
    }
    if (!input.empty()) {
      std::regex pattern(R"(^\d+$)");
      if (!std::regex_match(input, pattern)) {
        std::cout << "Некорретно введен id для performer" << std::endl;
        continue;
      }
      int new_perf = std::stoi(input);
      arr[iter_search]->ChangePerformer(new_perf);
      break;
    }
    break;
  }

  std::cout << "Order updated successfully!" << std::endl;
  return true;
}

void Customer::HandleReview(int id) {
  Database& db = Database::getInstance();
  std::vector<std::unique_ptr<Review>>& arr = db.GetReviewArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1) {
    std::cout << "review с таким id не существует" << std::endl;
    return;
  }
  if (!arr[iter_search]) {
    std::cout << "review уже был удален" << std::endl;
    return;
  }
  int id_perf = arr[iter_search]->GetUTo();
  size_t performer_id = static_cast<size_t>(db.BinSearchDelete<Performer>(id_perf, db.GetPerformerArr()));
  if (performer_id != static_cast<size_t>(-1)) {
    db.GetPerformerArr()[performer_id]->DeleteRate(arr[iter_search]->GetGrade());
  }
  arr.erase(arr.begin() + static_cast<int>(iter_search));
}

void Customer::CompleteOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1 || arr[iter_search]->GetStatus() != OrderStatus::WORK) {
    return;
  }
  arr[iter_search]->ChangeStatus(OrderStatus::DONE);
}

void Customer::WorkOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1 || arr[iter_search]->GetStatus() != OrderStatus::WAIT) {
    return;
  }
  arr[iter_search]->ChangeStatus(OrderStatus::WORK);
}

void Customer::SetPerformerRate(int id, int rate) {
    Database& db = Database::getInstance();
    auto& arr = db.GetPerformerArr();
    size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
    arr[iter_search]->AddRate(rate);
}

double Customer::FindAvgRate() {
  if (rate_.empty()) {
    return 0.0;
  }

  double sum = 0;
  for (double r : rate_) {
    sum += static_cast<double>(r);
  }

  return sum / static_cast<double>(rate_.size());
}

double Customer::GetRate() {
  return FindAvgRate();
}
} // namespace classes
