#include <string>
#include <stdexcept>

#include "../include/admin.hpp"
#include "../include/database.hpp"
#include "../include/review.hpp"
#include "/usr/include/nlohmann/json.hpp"


using json = nlohmann::json;
namespace classes {

Admin::Admin(int id, std::string login, std::string password, std::string salt) : User(id, std::move(login), std::move(password), std::move(salt)) {
}
Admin::Admin(User&& u) : User(std::move(u)) {
}

void Admin::HandleReview(int id) {  // Удаление отзыва
  Database& db = Database::getInstance();
  auto it = std::find_if(db.reviews_.begin(), db.reviews_.end(), [id](const auto& ptr) { return ptr->GetId() == id; });
  if (it != db.reviews_.end()) {
    db.reviews_.erase(it);
  }
}

std::unique_ptr<Admin> Admin::CreateFromJson(const json& j) {
  if (!j.is_object()) {
    throw std::invalid_argument("JSON must be an object for Admin deserialization");
  }

  if (!j.contains("id") || !j.contains("login") || !j.contains("password") || j.contains("salt")) {
    throw std::invalid_argument("JSON for Admin must contain id, login, and password");
  }

  // Извлекаем значения с проверкой типа
  if (!j["id"].is_number_integer() || !j["login"].is_string() || !j["password"].is_string() || !j["salt"].is_string()) {
    throw std::invalid_argument("Invalid types in JSON for Admin");
  }

  try {
    return std::make_unique<Admin>(j["id"].get<int>(), j["login"].get<std::string>(), j["password"].get<std::string>(), j["salt"].get<std::string>());
  } catch (const std::exception& e) {
    throw std::runtime_error(std::string("Failed to create Admin from JSON: ") + e.what());
  }
}

json Admin::ToJson(const Admin& a) {
  json j = {{"id", a.GetId()}, {"login", a.GetLogin()}, {"password", a.GetPass()}};
  return j;
}
}  // namespace classes