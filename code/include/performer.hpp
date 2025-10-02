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
  }

  auto FindCompleteOrder(std::shared_ptr<Order>& o) {
  }

  std::string GetClass() {
  }

  void CompleteOrder(std::shared_ptr<Order>& o) {
  }

  void AddInProgressOrder(std::shared_ptr<Order> o) {
  }

  void RespondToOrder(std::shared_ptr<Order> o) {
  }

  void DelPotOrders() {
  }
  // Нужно как-то настроить тригер на то, чтобы order удалялся из potorder в случае, если проект завершен
  // То есть проект, который уже ведется каким-то другим челом, может висеть у нашего performer, но должен удаляться, если он завершен


  void LoadDoc(const std::string& doc) {
    doc_path = doc;
  }

  void MakeReview(std::shared_ptr<Order> o, const std::string& descrip) {
  }
};