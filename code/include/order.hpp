#pragma once
#include <string>

#include "/usr/include/nlohmann/json.hpp"
#include "customer.hpp"
#include "performer.hpp"

enum class OrderStatus { WORK, DONE, WAIT, REJECTED };

namespace classes {

class Order {
 private:
  int id_;
  std::string name_;
  double price_;
  std::string description_;
  int customer_id_;
  int performer_id_;  //пока его никто не взял, это поле будет nullptr
  OrderStatus status_;

 public:
  Order(int id, const std::string& name, double price, const std::string& description, int customer_id,
        int performer_id, const OrderStatus& status = OrderStatus::WAIT);

  void CompleteOrder();
  void RejectOrder();
  void WorkOrder();  // зачем эти два
  void WaitOrder();

  std::string ChangeName(std::string name) {
    name_ = name;
  }

  std::string ChangePrice(double price) {
    price_ = price;
  }

  std::string ChangeDescription(std::string description) {
    description_ = description;
  }

  OrderStatus ChangeStatus(OrderStatus status) {
    status_ = status;
  }

  OrderStatus GetStatus() const {
    return this->status_;
  }
  const int& GetId() const {
    return this->id_;
  };
  const std::string& GetName() const {
    return this->name_;
  };
  const double& GetPrice() const {
    return this->price_;
  };
  const std::string& GetDescription() const {
    return this->description_;
  };
  const int GetCustomer() const {
    return this->customer_id_;
  };
  const int& GetPerformer() const {
    return this->performer_id_;
  };
  const int& GetCustomerId() const {
    return this->customer_id_;
  };
  void ChangeId(int id) {
    id_ = id;
  }

  void ChangePerformer(int i) {
    performer_id_ = i;
  }

  void AddPerformerToOrder(int id) {
    performer_id_ = id;
  }

  static json& ToJson(const Order& o);
};
}  // namespace classes