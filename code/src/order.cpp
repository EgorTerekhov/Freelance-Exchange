#pragma once
#include <string>

#include "../include/order.hpp"

Order::Order(const std::string& name_, Customer* c_, const std::string& p, const std::string& disc,
             const std::string& d_c, const std::string& term_)
    : name(name_), price(p), discript(disc), date_create(d_c), term(term_), customer(c_) {
}

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