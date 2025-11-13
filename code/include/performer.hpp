#pragma once
#include <string>
#include <memory>
#include <vector>

#include "user.hpp";
#include "order.hpp"
#include "review.hpp"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class Performer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  double rate_;

 public:
  Performer(int id, const std::string& login, const std::string& password, const std::string& name,
            const std::string& email, const std::string& phone, double rate);

  Performer(const User& u, const std::string& name, const std::string& email, const std::string& phone, double rate);

  void ChangeId(int id) {
    id_ = id;
  }

  void HandleReview(int id) override;

  int GetId() const {
    return id_;
  };
  const std::string& GetLogin() const {
    return this->login_;
  };
  const std::string& GetClass() const {
    return "Performer";
  };
  const std::string& GetPass() const { // нахай баааля
    return this->password_;
  };
  const std::string& GetName() const {
    return this->name_;
  };
  const std::string& GetEmail() const {
    return this->email_;
  };
  const std::string& GetPhone() const {
    return this->phone_;
  };

  json& ToJson(json& j, const Performer& p);

  void DeleteReview(int id);
  // static std::unique_ptr<Performer> FromJson(const json& j);
};
}  // namespace classes