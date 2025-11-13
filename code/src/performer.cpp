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


// Обработка ревью
void Performer::HandleReview(int id) {
    if (!id) {
        return;
    }
    Database& db = Database::getInstance();
    auto& arr = db.GetReviewArr();
    int iter_search = db.BinSearchDelete(id, arr);

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Current u_to: " << arr[iter_search]->GetUTo() << " | Enter new u_to (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            arr[iter_search]->GetUTo() = std::stoi(input);
        } catch (...) {
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
            arr[iter_search]->GetGrade() = std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input for grade. Keeping current value.\n";
        }
    }

    std::cout << "Review updated successfully!\n";
}

void Performer::DeleteReview(int id) {
    if (!id) {
        throw std::invalid_argument("Id is null!");
    }
    Database& db = Database::getInstance(); 
    db.DeleteReview(id);
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