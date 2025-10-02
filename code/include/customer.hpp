#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "order.hpp"

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
           const std::string phone_)
      : User(name_, login_, password_), email(email_), phone(phone_), rate(0) {
  }
  Customer(const User& u, const std::string& email_, const std::string& phone_)
      : User(u), email(email_), phone(phone_), rate(0) {
  }

  auto FindOrder(std::shared_ptr<Order> o) {
  }

  std::shared_ptr<Order> releaseOrder(Order* o) {
  }

  void AddOrder(std::string name, std::string discript, std::string price, std::string date_create, std::string term) {
  }

  void RemoveOrder(Order* o) {
  }

  std::string GetClass() {
  }

  std::vector<Performer*>& GetPotPerformers(Order* o) {
  }

  void ChoosePerformers(std::vector<Performer*> performers, Order* o) {
  }

  void MakeReview(std::shared_ptr<Order> o, const std::string& descrip) {
  }
};