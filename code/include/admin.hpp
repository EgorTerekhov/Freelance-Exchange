#pragma once
#include <string>
#include <memory>

#include "/usr/include/nlohmann/json.hpp"
#include "user.hpp"
#include "review.hpp"
#include "database.hpp"

namespace classes {
class Admin : public User {
 public:
  Admin(int id, const std::string& login, const std::string& password);
  Admin(const User& u);

  void DeleteCustomer(const Customer* c);
  void DeletePerformer(const Performer* p);

  void HandleReview(int id) override;  //для админа это delete review
  std::vector<std::string> GetOptions() override;

  int GetId() const {
    return this->id_;
  };

  void ChangeId(int id) {
    id_ = id;
  }

  const std::string& GetLogin() const {
    return this->login_;
  };
  const std::string& GetPass() const {
    return this->password_;
  };

  static std::unique_ptr<Admin> CreateFromJson(const json& j);
  void LoadFromJson(const json& j);
  json ToJson() const;

  static Admin* CreateFromJsonRaw(const nlohmann::json& j);

  int GetId() {
    return id_;
  }
  static json& ToJson(const Admin& a);
  
  const std::string& GetLogin() const {
    return this->login_;
  }
  const std::string& GetPass() const {
    return this->password_;
  }
};
}  // namespace classes