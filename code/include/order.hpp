#pragma once
#include <string>
#include "customer.hpp"
#include "performer.hpp"

enum class OrderStatus {
    WORK,
    DONE,
    REJECTED
};

namespace classes {

class Order {
 private:
  int id_;
  std::string name_;
  std::string status_;  // in_progress, completed or deleted
  std::string price_;
  std::string description_;
  int customer_id_;
  OrderStatus status_;
  int performer_id_;  //пока его никто не взял, это полу будет nullptr
  int id_;
 public:
  Order(int id, const std::string& name, std::string status, std::string price, std::string description, Customer* customer,
        Performer* performer);

  void CompleteOrder();

  OrderStatus GetStatus();

  int GetCustomer();

  void ChangeId(int id) { id_ = id; }

  int GetPerformer();

  void ChangePerformer(int i) {
    performer_id_ = i;
  }

  void AddPerformerToOrder(Performer* p);
};
}  // namespace classes