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

Performer::Performer(int id, std::string login, std::string password, std::string salt, std::string name,
                     std::string email, std::string phone, double rate)
    : User(id, std::move(login), std::move(password), std::move(salt))
    , name_(std::move(name))
    , email_(std::move(email))
    , phone_(std::move(phone))
    , rate_(rate) {
}

Performer::Performer(User&& u, std::string name, std::string email, std::string phone, double rate)
    : User(std::move(u)), name_(std::move(name)), email_(std::move(email)), phone_(std::move(phone)), rate_(rate) {
}

// Обработка ревью
void Performer::HandleReview(int id) {
  if (!id) {
    return;
  }
  Database& db = Database::getInstance();
  auto& arr = db.GetReviewArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));

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

// Преобразование в JSON
json& Performer::ToJson(json& j, const Performer& p) {
  j = {{"id", p.GetId()},     {"login", p.GetLogin()}, {"password", p.GetPass()},
       {"name", p.GetName()}, {"email", p.GetEmail()}, {"phone", p.GetPhone()}};
  return j;
}

double Performer::FindAvgRate() {
  if (rate_.empty()) {
    return 0.0;
  }

  int sum = 0;
  for (int r : rate_) {
    sum += r;
  }

  return static_cast<double>(sum) / rate_.size();
}

void Performer::SetCustomerRate(int id, int rate) {
  Database& db = Database::getInstance();
  auto& arr = db.GetCustomerArr();
  size_t iter_search = static_cast<size_t>(db.BinSearchDelete(id, arr));
  arr[iter_search]->AddRate(rate);
}

  double Performer::GetRate(int id) {
    return this->FindAvgRate();
  }

}  // namespace classes

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