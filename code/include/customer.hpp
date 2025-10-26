#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "order.hpp"

namespace classes {
class Customer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  std::vector<Order*> orders_;
  std::vector<Review*> reviews_;  // отзывы которые он оставил
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
};
}  // namespace classes