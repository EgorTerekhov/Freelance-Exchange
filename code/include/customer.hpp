#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "review.hpp"
#include "order.hpp"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class Customer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  double rate_;

 public:
  Customer(int id, const std::string& login, const std::string& password, const std::string& name,
           const std::string& email, const std::string& phone, double rate);
  Customer(const User& u, const std::string& name, const std::string& email, const std::string& phone, double rate);

  void CreateOrder(int id, const std::string& name, const OrderStatus& status, double price,
                           const std::string description, int customer_id, int performer_id);

  void CreateReview(int id, const int u_to, int order_id, std::string& description, ReviewStatus status, int grade);
  void RemoveOrder(int id);
  void CompleteOrder(int id);
  void WorkOrder(int id);

  int GetId() const {
    return this->id_;
  };
  
  int ChangeId(int id) {
    id_ = id;
  }
  
  const std::string& GetLogin() const {
    return this->login_;
  };
  const std::string& GetPass() const {
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
  void HandleReview(int id) override;

  void HandleOrder(int id);
};
}  // namespace classes