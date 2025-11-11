#pragma once
#include <string>
#include <memory>
#include <vector>

#include "/usr/include/nlohmann/json.hpp"
#include "user.hpp"
#include "order.hpp"
#include "review.hpp"

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

  // static std::unique_ptr<Performer> FromJson(const json& j);
};
}  // namespace classes