#pragma once
#include <string>
#include "customer.hpp"
#include "performer.hpp"
namespace classes {

class Order {
 private:
  int id_;
  std::string name_;
  std::string status_;  // in_progress, completed or deleted
  std::string price_;
  std::string description_;
  Customer* customer_;
  Performer* performer_;  //пока его никто не взял, это полу будет nullptr

 public:
  Order(int id, const std::string& name, std::string status, std::string price, std::string description, Customer* customer,
        Performer* performer);

  void CompleteOrder();

  std::string GetStatus();

  Customer* GetCustomer();

  Performer* GetPerformer();

  void AddPerformerToOrder(Performer* p);
};
}  // namespace classes