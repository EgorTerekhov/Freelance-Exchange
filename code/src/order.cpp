#include <string>

#include "../include/order.hpp"
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;
namespace classes {
  Order::Order(int id, std::string name, double price, std::string description, int customer_id, int performer_id, OrderStatus status, std::vector<int> potential_performers) 
      : id_(id), name_(std::move(name)), price_(price), description_(std::move(description)), customer_id_(customer_id), performer_id_(performer_id), status_(status),  potential_performers_(potential_performers){}

  void Order::CompleteOrder() {
    this->status_ = OrderStatus::DONE;
  }

  void Order::WorkOrder() {
    this->status_ = OrderStatus::WORK;
  }

  void Order::RejectOrder() {
    this->status_ = OrderStatus::REJECTED;
  }

  void Order::WaitOrder() {
    this->status_ = OrderStatus::WAIT;
  }

  json Order::ToJson(Order& o) {
    std::string status;
    if (o.GetStatus() == OrderStatus::WORK) {
      status = "WORK";
    } else if (o.GetStatus() == OrderStatus::DONE) {
      status = "DONE";
    } else if (o.GetStatus() == OrderStatus::WAIT){
      status = "WAIT";
    } else {
      status = "REJECTED";
    }

    json j = {
      {"id", o.GetId()},
      {"name", o.GetName()},
      {"price", o.GetPrice()},
      {"description", o.GetDescription()},
      {"customer_id", o.GetCustomerId()},
      {"status", status},
      {"performer_id", o.GetPerformerId()},
      {"potential_performers", o.Getarrperformer()}
    };

    return j;
  }


// надо сделать методов по изменению отзыва
}  // namespace classes