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
  std::vector<std::shared_ptr<Order>> orders;
  std::string email;
  std::string phone;
  std::vector<Review> reviews;
  double rate;

  friend class Admin;

 public:
  Customer(const std::string name_, const std::string login_, const std::string password_, std::string email_,
           const std::string phone_);
  Customer(const User& u, const std::string& email_, const std::string& phone_);

  std::vector<std::shared_ptr<Order>>::iterator FindOrder(Order* o);

  std::shared_ptr<Order> releaseOrder(std::shared_ptr<Order> o);

  void AddOrder(std::string name, std::string discript, std::string price, std::string date_create, std::string term);

  void RemoveOrder(Order* o);

  std::string GetClass();

  std::vector<Performer*>& GetPotPerformers(std::shared_ptr<Order> o);

  void ChoosePerformers(std::vector<Performer*> performers, std::shared_ptr<Order> o);

  void MakeReview(std::vector<Review> all_review, Order* o, const std::string& descrip);
};
}  // namespace classes