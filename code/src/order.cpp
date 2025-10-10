#pragma once
#include <string>

#include "order.hpp"

namespace classes {
enum class OrderStatus { Created, InProgress, Complete };

// Поля:
// std::string name;
// std::string price;
// std::string discript;
// std::string date_create;
// std::string term;
// Customer* customer;
// OrderStatus status = OrderStatus::Created;
// std::vector<Performer*> PotPerformers;
// std::vector<Performer*> MainPerformers;

Order::Order(const std::string& name_, Customer* c_, const std::string& p, const std::string& disc,
             const std::string& d_c, const std::string& term_)
    : name(name_), price(p), discript(disc), date_create(d_c), term(term_), customer(c_) {
}

void Order::CompleteOrder() {
  status = OrderStatus::Complete;
}

OrderStatus Order::GetStatus() {
  return this->status;
}
void Order::AddPotPerformer(Performer* p) {
  PotPerformers.push_back(p);
}

void Order::AddMainPerformer(Performer* p) {
  PotPerformers.push_back(p);
}

Customer* Order::GetCustomer() {
  return this->customer;
}
// надо сделать методов по изменению отзыва
}  // namespace classes