#pragma once
#include <string>
#include "customer.hpp"
#include "performer.hpp"

enum class OrderStatus {
    WORK,
    DONE,
    WAIT,
    REJECTED
};

namespace nlohmann {
  class json;
}

namespace classes {

class Order {
 private:
  int id_;
  std::string name_;
  std::string price_;
  std::string description_;
  int customer_id_;
  OrderStatus status_;
  int performer_id_;  //пока его никто не взял, это полу будет nullptr

 public:
  Order(int id, const std::string& name, std::string status, std::string price, std::string description, Customer* customer,
        Performer* performer);

  void CompleteOrder();
  void RejectOrder();
  void WorkOrder();
  void WaitOrder();

  OrderStatus GetStatus() const { return this->status_};
  const std::string& GetId() const { return this->id_; };
  const std::string& GetName() const { return this->name; };
  const std::string& GetPrice() const { return this->price_; };
  const std::string& GetDescription() const { return this->description_; };
  const int GetCustomer() const { return this->customer_id_; };
  const int GetPerformer() const { return this->performer_id_; };
  void ChangeId(int id) { id_ = id; }

  void ChangePerformer(int i) {
    performer_id_ = i;
  }

  void AddPerformerToOrder(int id) { performer_id_ = id };
  static json& ToJson(json& j, const Order& o);
};
}  // namespace classes