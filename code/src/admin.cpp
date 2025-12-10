#include <string>
#include <stdexcept>

#include "../include/admin.hpp"
#include "../include/database.hpp"
#include "../include/review.hpp"
#include "../include/nlohmann/json.hpp"


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

json Admin::ToJson(const Admin& a) {
  json j = {{"id", a.GetId()}, {"login", a.GetLogin()}, {"password", a.GetPass()}, {"salt", a.GetSalt()}};
  return j;
}
}  // namespace classes