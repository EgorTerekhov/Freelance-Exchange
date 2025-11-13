#pragma once
#include <string>
#include <memory>

#include "user.hpp"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;


namespace classes {
class Customer;
class Performer;
class Admin : public User {
 public:
  Admin(int id, std::string login, std::string password);
  Admin(User&& u);

  void DeleteCustomer(const Customer* c);
  void DeletePerformer(const Performer* p);

  void HandleReview(int id) override;  //для админа это delete review
  std::vector<std::string> GetOptions() override;

  int GetId() const {
    return this->id_;
  };
  const std::string& GetLogin() const {
    return this->login_;
  }
  const std::string& GetPass() const {
    return this->password_;
  }

  void ChangeId(int id) {
    id_ = id;
  }

  static std::unique_ptr<Admin> CreateFromJson(const json& j);
  void LoadFromJson(const json& j);
  json ToJson() const;

  static Admin* CreateFromJsonRaw(const nlohmann::json& j);

  static json ToJson(const Admin& a);
};
}  // namespace classes