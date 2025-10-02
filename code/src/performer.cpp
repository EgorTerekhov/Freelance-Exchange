#pragma once
#include <string>
#include <memory>
#include <vector>

#include "user.hpp"
#include "order.hpp"
#include "review.hpp"
#include "storage.hpp"

class Performer : public User {
 private:
  std::string email;
  std::string phone;
  std::string doc_path = "";
  std::string occupation;
  std::vector<std::shared_ptr<Order>> CompleteOrders;
  std::vector<std::weak_ptr<Order>> InProgressOrders;
  std::vector<std::weak_ptr<Order>> PotOrders;
  std::vector<Review> reviews;
  double rate;

  friend class Admin;

 public:
  Performer(const std::string name_, const std::string login_, const std::string password_, std::string email_,
            const std::string phone_)
      : User(name_, login_, password_), email(email_), phone(phone_), rate(0) {
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

  std::string GetClass() {
    return "performer";
  }

  void CompleteOrder(std::shared_ptr<Order>& o) {
    auto it = FindInProgressOrder(o);
    if (it != InProgressOrders.end()) {
      InProgressOrders.erase(it);
      CompleteOrders.push_back(o);
      o->CompleteOrder();
    }
  }

  void AddInProgressOrder(std::shared_ptr<Order> o) {
    InProgressOrders.emplace_back(o);
    auto it = std::find(PotOrders.begin(), PotOrders.end(), o);
    if (it != PotOrders.end()) {
      PotOrders.erase(it);
    }
  }

  void RespondToOrder(std::shared_ptr<Order> o) {
    o->AddPotPerformer(this);
    PotOrders.emplace_back(o);
  }

  void DelPotOrders() {
    for (auto it = PotOrders.begin(); it != PotOrders.end();) {
      if (auto o = it->lock()) {
        if (o->GetStatus() == OrderStatus::Complete) {
          it = PotOrders.erase(it);
          continue;
        }
      }
      ++it;
    }
  }
  // Нужно как-то настроить тригер на то, чтобы order удалялся из potorder в случае, если проект завершен
  // То есть проект, который уже ведется каким-то другим челом, может висеть у нашего performer, но должен удаляться,
  // если он завершен

  void LoadDoc(const std::string& doc) {
    doc_path = doc;
  }

  void MakeReview(std::shared_ptr<Order> o, const std::string& descrip) {
    auto it = FindCompleteOrder(o);
    if (it != CompleteOrders.end()) {
      all_review.emplace_back(this, o->GetCustomer(), o, descrip);
    }
  }
};