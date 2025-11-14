#pragma once
#include <string>

#include "../nlohmann/json.hpp"

using json = nlohmann::json;

namespace classes {
  enum class OrderStatus { WORK, DONE, WAIT, REJECTED };
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
    Order(int id, std::string name, double price, std::string description, int customer_id,
          int performer_id, OrderStatus status = OrderStatus::WAIT);

    void CompleteOrder();
    void RejectOrder();
    void WorkOrder();  // зачем эти два
    void WaitOrder();

    void ChangeName(std::string name) {
      name_ = name;
    }

    void ChangePrice(double price) {
      price_ = price;
    }

    void ChangeDescription(std::string description) {
      description_ = description;
    }

    void ChangeStatus(OrderStatus status) {
      status_ = status;
    }

    OrderStatus GetStatus() {
      return this->status_;
    }
    int& GetId() {
      return this->id_;
    };
    std::string& GetName() {
      return this->name_;
    };
    double& GetPrice() {
      return this->price_;
    };
    std::string& GetDescription() {
      return this->description_;
    };
    int GetCustomer() {
      return this->customer_id_;
    };
    int& GetPerformer() {
      return this->performer_id_;
    };
    int& GetCustomerId() {
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

    static json ToJson(Order& o);
  };
}  // namespace classes