#include "../include/performer.hpp"
#include "../include/review.hpp"
#include "../include/database.hpp"
#include "../include/order.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <memory>

using json = nlohmann::json;

namespace classes {

Performer::Performer(int id, const std::string& login, const std::string& password,
                     const std::string& name, const std::string& email,
                     const std::string& phone, double rate)
    : User(id, login, password), name_(name), email_(email), phone_(phone), rate_(rate) {}

Performer::Performer(const User& u, const std::string& name,
                     const std::string& email, const std::string& phone, double rate)
    : User(u), name_(name), email_(email), phone_(phone), rate_(rate) {}

std::string Performer::GetClass() {
    return "Performer";
}

// Обработка ревью
void Performer::HandleReview(int id) {
    if (!id) {
        return;
    }

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Current u_to: " << review->GetUTo() << " | Enter new u_to (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->GetUTo() = std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input for u_to. Keeping current value.\n";
        }
    }

    std::cout << "Current description: " << review->GetDescription()
              << " | Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        review->GetDescription() = input;
    }

    std::cout << "Current grade: " << review->GetGrade()
              << " | Enter new grade (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->GetGrade() = std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input for grade. Keeping current value.\n";
        }
    }

    std::cout << "Review updated successfully!\n";
}

// Завершение заказа
void Performer::CompleteOrder(std::shared_ptr<Order>& o) {
    auto it = std::find(InProgressOrders.begin(), InProgressOrders.end(), o);
    if (it != InProgressOrders.end()) {
        InProgressOrders.erase(it);
        CompleteOrders.push_back(o);
        o->ChangeStatus(OrderStatus::DONE);
    }
}

// Удаление ревью
void Performer::DeleteReview(Review* review) {
    if (!review) {
        throw std::invalid_argument("Review pointer is null");
    }
    Database& db = Database::getInstance();
    auto& arr = db.GetReviewArr();
    auto it = std::find_if(arr.begin(), arr.end(), [review](const auto& ptr) { return ptr.get() == review; });
    if (it != arr.end()) {
        arr.erase(it);
    }
}

// Создание ревью
void Performer::MakeReview(std::vector<std::unique_ptr<Review>>& all_review,
                           std::shared_ptr<Order> o, const std::string& descrip) {
    auto it = std::find(CompleteOrders.begin(), CompleteOrders.end(), o);
    if (it != CompleteOrders.end()) {
        all_review.push_back(std::make_unique<Review>(0, this->id_, o->GetCustomer(), o->GetId(), descrip, 0, ReviewStatus::PENDING));
    }
}

// Преобразование в JSON
json& Performer::ToJson(json& j, const Performer& p) {
    j = {
        {"id", p.GetId()},
        {"login", p.GetLogin()},
        {"password", p.GetPass()},
        {"name", p.GetName()},
        {"email", p.GetEmail()},
        {"phone", p.GetPhone()}
    };
    return j;
}

} // namespace classes


  // std::unique_ptr<Performer> Performer::FromJson(const json& j) {
  //   if (!j.contains("id") || !j.contains("login") || !j.contains("password") ||
  //       !j.contains("name") || !j.contains("email") || !j.contains("phone") || !j.contains("rate"))) {
  //         throw std::invalid_argument("Missing required fields in JSON");
  //       }
    
  //   try {
  //     int id = j.at("id").get<int>();
  //     std::string login = j.at("login").get<std::string>();
  //     std::string password = j.at("password").get<std::string>();
  //     std::string name = j.at("name").get<std::string>();
  //     std::string email = j.at("email").get<std::string>();
  //     std::string phone = j.at("phone").get<std::string>();
  //     double rate = j.at("rate").get<double>();

  //     return std::make_unique<Performer>(id, login, password, name, email, phone, rate);
  //   } catch (const json::exception& a) {
  //     throw std::invalid_argument("Invalid JSON format: " + std::string(e.what()));
  //   }
  // }
  // namespace classes