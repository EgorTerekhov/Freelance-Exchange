#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>
#include <iostream>

#include "../include/customer.hpp"
#include "../include/database.hpp"
#include "../include/order.hpp"

namespace classes {

Customer::Customer(int id, const std::string& login, const std::string& password, const std::string& name, const std::string& email,
            const std::string& phone, double rate = 0) :
            User(id, login, password), name_(name), email_(email), phone_(phone), rate_(rate) {}

Customer::Customer(const User& u, const std::string& name, const std::string& email, const std::string& phone, double rate = 0)
                   : User(u), name_(name), email_(email), phone_(phone), rate_(rate) {}


// std::vector<std::shared_ptr<Order>>::iterator Customer::FindOrder(Order* o) {
//   auto it =
//       std::find_if(orders.begin(), orders.end(), [&](const std::shared_ptr<Order>& ptr) { return ptr.get() == o; });
//   return it;
// }

 void Customer::CreateOrder(int id, const std::string& name, std::string status, std::string price, std::string description,
                      int customer, int performer) {
  Order o = Order(id, name, price, description, this->id_, OrderStatus::WAIT, performer);
  Database& db = Database::getInstance();
  db.GetOrderArr.push_back(o);
  db.SortById()
}

void Customer::RemoveOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  int iter_search = db.BinSearchDelete(id, db.GetOrderArr);
  if (iter_search != -1 && arr[id_search]->GetStatus != OrderStatus::DONE) {
    arr.erase(arr.begin() + iter_search);
  }
}

void Customer::HandleOrder(int id) {
  Database& db = Database::getInstance();
  auto& arr = db.GetOrderArr();
  int iter_search = db.BinSearchDelete(id, arr);
  if (iter_search == -1 || !arr[iter_search] || arr[iter_search]->GetStatus() != ReviewStatus::WAIT) {
    return;
  }
  std::string input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Current name: " << arr[iter_search]->GetName() << " | Enter new name (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
      arr[iter_search]->GetDescription() = input;
  }

  std::cout << "Current price: " << arr[iter_search]->GetPrice() << " | Enter new price (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      arr[iter_search]->GetPrice() = std::stod(input);
    } catch (const std::exception& e) {
      std::cout << "Invalid input for performer. Keeping current value." << std::endl;
    }
  }

  std::cout << "Current description: " << arr[iter_search]->GetDescription() << " | Enter new description (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
      arr[iter_search]->GetDescription() = input;
  }

  //можно еще прям здесь добавить хрень, чтобы статус менять, но, мне кажется, легче отдельно сделать метод для этого.

  std::cout << "Current perfomer: " << arr[iter_search]->GetPerformer() << " | Enter new perfromer (or press Enter to keep current): ";
  std::getline(std::cin, input);
  if (!input.empty()) {
    try {
      arr[iter_search]->GetPerformer() = std::stoi(input);
    } catch (const std::exception& e) {
      std::cout << "Invalid input for performer. Keeping current value." << std::endl;
    }
  } //нужно делать проверки на существование perfomer нового
  
  std::cout << "Order updated successfully!" << std::endl;
}

std::string Customer::GetClass() {
  return "customer";
}

// Возможно стоит функции по изменению ордера и ревью сделать с другой сигнатурой (изначально уже известно, че меняться будет)
// возможно стоит функции с ревью и ордером делать по указателю, но пока хз
void Customer::HandleReview(int id) { // сделаем пока так, что при вызове функции он должен все поля переопределять, если же не хочет менять - enter
    Database& db = Database::getInstance();
    auto& arr = db.GetReviewArr();
    int iter_search = db.BinSearchDelete(id, arr);
    if (iter_search == -1 || !arr[iter_search] || arr[iter_search]->GetStatus() != ReviewStatus::PENDING) {
      return;
    }
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Current u_to: " << arr[iter_search]->GetUTo() << " | Enter new u_to (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
      try {
        arr[iter_search]->GetUTo() = std::stoi(input);
      } catch (const std::exception& e) {
        std::cout << "Invalid input for u_to. Keeping current value." << std::endl;
      }
    } //нужно делать проверки на существование u_to_ нового
    
    std::cout << "Current description: " << arr[iter_search]->GetDescription() << " | Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        arr[iter_search]->GetDescription() = input;
    }

    std::cout << "Current grade: " << arr[iter_search]->GetGrade() << " | Enter new grade (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
      try {
          arr[iter_search]->GetGrade() = std::stoi(input);
      } catch (const std::exception& e) {
          std::cout << "Invalid input for grade. Keeping current value." << std::endl;
      }
    }
    std::cout << "Review updated successfully!" << std::endl;
  }

  void Customer::CompleteOrder(int id) {
    Database& db = Database::getInstance();
    auto& arr = db.GetReviewArr();
    int iter_search = db.BinSearchDelete(id, arr);
    if (iter_search == -1 || arr[iter_search]->GetStatus() != Work) {
      return;
    } else {
      arr[iter_search]->GetStatus() = OrderStatus::DONE;
    }
  }

  void Customer::WorkOrder(int id) {
    Database& db = Database::getInstance();
    auto& arr = db.GetReviewArr();
    int iter_search = db.BinSearchDelete(id, arr);
    if (iter_search == -1 || arr[iter_search]->GetStatus() != Wait) {
      return;
    } else {
      arr[iter_search]->GetStatus() = OrderStatus::WORK;
    }
  }

  void Customer::CreateReview(int id, const int u_to, int order_id, std::string& description, int grade) {
    Order r = Order(id, this->id_, u_to, order_id, description, grade);
    Database& db = Database::getInstance();
    db.GetReviewArr.push_back(r);
    db.SortById();
  }
}  // namespace classes