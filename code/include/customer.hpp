#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "order.hpp"

namespace nlohmann {
  class json;
}
namespace classes {
class Customer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  int id_ = 0;
  // std::vector<Order*> orders_;
  // std::vector<Review*> reviews_;  // отзывы которые он оставил
  double rate_;

 public:
  Customer(int id, const std::string& login, const std::string& password, const std::string& name, const std::string& email,
           const std::string& phone, const std::vector<Order*>& orders, const std::vector<Review*>& reviews);
  Customer(const User& u, const std::string& name, const std::string& email, const std::string& phone,
           const std::vector<Order*>& orders, const std::vector<Review*>& reviews);

  Order* CreateOrder(const std::string& name, std::string status, std::string price, std::string description,
                      Customer* customer, Performer* performer);

  void RemoveOrder(Order*);

  void HandleReview(Review* review) override;

  void CompleteOrder(std::unique_ptr<Order>);
  void AddPerformerToOrder(std::unique_ptr<Performer>);
  

  int GetId() const { return this->id_; };
  int ChangeId(int id) { id_ = id;}
  const std::string& GetLogin() const { return this->login_; };
  const std::string& GetPass() const { return this->password_; };
  const std::string& GetName() const { return this->name; };
  const std::string& GetEmail() const { return this->email_; };
  const std::string& GetPhone() const { return this->phone_; };
  void HandleReview(Review* review) override;

  static Customer* FromJsonRaw(const nlohmann::json& j);
  static std::unique_ptr<Customer> FromJson(const nlohmann::json& j);


};
}  // namespace classes