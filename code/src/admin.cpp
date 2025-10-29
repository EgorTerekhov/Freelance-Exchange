#include <string>
#include "../include/admin.hpp"
#include <stdexcept>
#include "../include/database.hpp"
#include "../include/review.hpp"
namespace classes {

  Admin::Admin(int id, const std::string& login_, const std::string& password_)
      : User(id, login_, password_) {}
  Admin::Admin(const User& u) : User(u) {}

  void Admin::HandleReview(Review*& review) {
    if (!review) {
      throw std::invalid_argument("Review pointer is null");
    }
    Database& db = Database::getInstance();
    auto it = std::find_if(db.reviews_.begin(), db.reviews_.end(),
                          [review](const auto& ptr) {
                            return ptr.get() == review;
                          });
    if (it != db.reviews_.end()) {
      Review* temp = it->release();
      db.reviews_.erase(it);
      review = temp;
    }
  }

  std::unique_ptr<Admin> Admin::CreateFromJson(const nlohmann::json& j) {
    if (!j.is_object()) {
      throw std::invalid_argument("JSON must be an object for Admin deserialization");
    }

    if (!j.contains("id") || !j.contains("login") || !j.contains("password")) {
      throw std::invalid_argument("JSON for Admin must contain id, login, and password");
    }

    // Извлекаем значения с проверкой типа
    if (!j["id"].is_number_integer() || 
        !j["login"].is_string() || 
        !j["password"].is_string()) {
      throw std::invalid_argument("Invalid types in JSON for Admin");
    }

    try {
      return std::make_unique<Admin>(
        j["id"].get<int>(),
        j["login"].get<std::string>(),
        j["password"].get<std::string>()
      );
    } catch (const std::exception& e) {
      throw std::runtime_error(std::string("Failed to create Admin from JSON: ") + e.what());
    }
  }

  json& Admin::ToJson(const Admin& a) {
    json j = {
      {"id", p`.GetId()},
      {"login", p.GetLogin()},
      {"password", p.GetPass()}
    };
  }
}