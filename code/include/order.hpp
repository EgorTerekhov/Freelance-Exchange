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
  double price_;
  std::string description_;
  int customer_id_;
  int performer_id_;  //пока его никто не взял, это полу будет nullptr
  OrderStatus status_;

 public:
  Order(int id, const std::string& name, double price,const std::string& description, int customer_id,
        int performer_id, const OrderStatus& status = OrderStatus::WAIT);

  void CompleteOrder();
  void RejectOrder();
  void WorkOrder();
  void WaitOrder();

  OrderStatus GetStatus() { return this->status_};
  std::string& GetId() { return this->id_; };
  std::string& GetName() { return this->name; };
  double& GetPrice() { return this->price_; };
  std::string& GetDescription() { return this->description_; };
  const int GetCustomer() const { return this->customer_id_; };
  int& GetPerformer() { return this->performer_id_; };
  void ChangeId(int id) { id_ = id; }

  void ChangePerformer(int i) {
    performer_id_ = i;
  }

  void AddPerformerToOrder(int id) { performer_id_ = id };
  static json& ToJson(json& j, const Order& o);
};
}  // namespace classes