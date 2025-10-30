#pragma once
#include <string>

#include "../include/order.hpp"

namespace classes {
  Order::Order(int id, const std::string& name, double price, const std::string& description, int customer_id, int performer_id, OrderStatus& status) 
      : id_(id), name_(name), price_(price), description_(description), customer_id_(customer_id), performer_id_(performer_id), status_(status) {}

  void Order::CompleteOrder() {
    status = OrderStatus::DONE;
  }

  void Order::WorkOrder() {
    status = OrderStatus::WORK;
  }

  void Order::RejectOrder() {
    status = OrderStatus::REJECTED;
  }

  void Order::WaitOrder() {
    status = OrderStatus::WAIT;
  }

  void Order::AddPotPerformer(Performer* p) {
    PotPerformers.push_back(p);
  }

  void Order::AddMainPerformer(Performer* p) {
    PotPerformers.push_back(p);
  }

  json& Order::ToJson(json& j, const Order& o) {
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

    j = {
      {"id", o.GetId()},
      {"name", o.GetName()},
      {"price", o.GetPrice()},
      {"description", o.GetDescription()},
      {"customer_id", o.GetCustomerId()},
      {"status", status},
      {"performer_id", o.GetPerformer()}
    };

    return j;
  }


// надо сделать методов по изменению отзыва
}  // namespace classes