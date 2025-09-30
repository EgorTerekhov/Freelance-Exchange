#pragma once
#include <string>
#include <memory>
#include <vector>
#include "user.h"
#include "order.h"
#include "review.h"
#include "admin.h"


class Performer : public User {
 private:
  std::string email;
  std::string phone;
  std::string doc_path = "";
  std::string occupation;
  std::vector<std::shared_ptr<Order>> CompleteOrders;
  std::vector<Order*> InProgressOrders;
  std::vector<Review> reviews;
  double rate;

  friend class Admin;

 public:
  Performer(const std::string name_, const std::string login_,
           const std::string password_, std::string email_,
           const std::string phone_) :
           User(name_, login_, password_),
           email(email_),
           phone(phone_),
           rate(0) {
  }
  Performer(const User& u, const std::string& email_, const std::string& phone_)
           : User(u), email(email_), phone(phone_), rate(0) {
  }

  auto FindInProgressOrder(std::shared_ptr<Order>& o) {
    auto it = std::find(InProgressOrders.begin(), InProgressOrders.end(), o);
    return it;
  }

  auto FindCompleteOrder(std::shared_ptr<Order>& o) {
    auto it = std::find(CompleteOrders.begin(), CompleteOrders.end(), o);
    return it;
  }

  void CompleteOrder(std::shared_ptr<Order>& o) {
    auto it = FindInProgressOrder(o);
    if (it != InProgressOrders.end()) {
      InProgressOrders.erase(it);
      CompleteOrders.push_back(o);
      o->CompleteOrder();
    }
  }

  void RespondToOrder(std::shared_ptr<Order> o) {
    o->AddPotPerformer(this);
  }

  void LoadDoc(const std::string& doc) {
    doc_path = doc;
  }

  void MakeReview(std::shared_ptr<Order> o, const std::string& descrip) {
    auto it = FindCompleteOrder(o);
    if (it != CompleteOrders.end()) {
      // o->customer->reviews.emplace_back(this, o->customer, o, descrip);
      
    }
  }
  // отзывы через админа должны проходить
};