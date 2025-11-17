#include "../include/customer.hpp"
#include "../include/database.hpp"
#include "../include/order.hpp"
#include "../include/review.hpp"
#include "/usr/include/nlohmann/json.hpp"

#include <iostream>
#include <limits>
#include <memory>

using json = nlohmann::json;

namespace classes {

Customer::Customer(int id, std::string login, std::string password, std::string salt,
                   std::string name, std::string email,
                   std::string phone, double rate)
    : User(id, std::move(login), std::move(password), std::move(salt)), name_(std::move(name)), email_(std::move(email)), phone_(std::move(phone)), rate_(rate) {}

Customer::Customer(User&& u, std::string name,
                   std::string email, std::string phone, double rate)
    : User(std::move(u)), name_(std::move(name)), email_(std::move(email)), phone_(std::move(phone)), rate_(rate) {}

void Customer::CreateOrder(int id, std::string& name, OrderStatus& status,
                           double price, std::string description,
                           int customer_id, int performer_id) {
  auto order = std::make_unique<Order>(id, name, price, description, customer_id, performer_id, status);
  Database& db = Database::getInstance();
  db.CreateOrder(std::move(order));
}

void Customer::DeleteOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  db.DeleteOrder(id);
}

void Customer::HandleOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1 || !arr[static_cast<size_t>(iter_search)] || arr[static_cast<size_t>(iter_search)]->GetStatus() != OrderStatus::WAIT) {
    return;
  }

  std::string input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Current name: " << arr[iter_search]->GetName()
            << " | Enter new name (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    arr[iter_search]->ChangeName(input);
  }

  std::cout << "Current price: " << arr[iter_search]->GetPrice()
            << " | Enter new price (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      double new_price = std::stod(input);
      arr[iter_search]->ChangePrice(new_price);
    } catch (const std::exception&) {
      std::cout << "Invalid input for price. Keeping current value.\n";
    }
  }

  std::cout << "Current description: " << arr[iter_search]->GetDescription()
            << " | Enter new description (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    arr[iter_search]->ChangeDescription(input);
  }

  std::cout << "Current performer: " << arr[iter_search]->GetPerformer()
            << " | Enter new performer (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      int new_perf = std::stoi(input);
      arr[iter_search]->ChangePerformer(new_perf);
    } catch (const std::exception&) {
      std::cout << "Invalid input for performer. Keeping current value.\n";
    }
  }

  std::cout << "Order updated successfully!\n";
}


void Customer::HandleReview(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetReviewArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  if (static_cast<int>(iter_search) == -1 || !arr[iter_search] || arr[iter_search]->GetStatus() != ReviewStatus::PENDING) {
    return;
  }

  std::string input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Current u_to: " << arr[iter_search]->GetUTo()
            << " | Enter new u_to (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      int new_to = std::stoi(input);
      arr[iter_search]->GetUTo() = new_to;
    } catch (const std::exception&) {
      std::cout << "Invalid input for u_to. Keeping current value.\n";
    }
  }

  std::cout << "Current description: " << arr[iter_search]->GetDescription()
            << " | Enter new description (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    arr[iter_search]->GetDescription() = input;
  }

  std::cout << "Current grade: " << arr[iter_search]->GetGrade()
            << " | Enter new grade (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      int new_grade = std::stoi(input);
      arr[iter_search]->GetGrade() = new_grade;
    } catch (const std::exception&) {
      std::cout << "Invalid input for grade. Keeping current value.\n";
    }
  }

  std::cout << "Review updated successfully!\n";
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

void Customer::CreateReview(int id, const int u_to, int order_id, std::string& description,
                            ReviewStatus status, int grade) {
  auto review = std::make_unique<Review>(id, this->id_, u_to, order_id, description, grade, status);
  Database& db = Database::getInstance();
  db.CreateReview(std::move(review));
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

    int sum = 0;
    for (int r : rate_) {
      sum += r;
    }

    return static_cast<double>(sum) / rate_.size();
  }

  double Customer::GetRate(int id) {
    return this->FindAvgRate();
  }
} // namespace classes
