#pragma once
#include <string>

#include "customer.hpp"
#include "performer.hpp"

enum class OrderStatus { Created, InProgress, Complete };

class Order {
 private:
  std::string name;
  std::string price;
  std::string discript;
  std::string date_create;
  std::string term;
  Customer* customer;
  OrderStatus status = OrderStatus::Created;
  std::vector<Performer*> PotPerformers;
  std::vector<Performer*> MainPerformers;

  friend class Customer;
  friend class Admin;

 public:
  Order(const std::string& name_, Customer* c_, const std::string& p, const std::string& disc, const std::string& d_c,
        const std::string& term_)
      : name(name_), price(p), discript(disc), date_create(d_c), term(term_), customer(c_) {
  }

  void CompleteOrder() {
    status = OrderStatus::Complete;
  }

  OrderStatus GetStatus() {
    return this->status;
  }
  void AddPotPerformer(Performer* p) {
    PotPerformers.push_back(p);
  }

  void AddMainPerformer(Performer* p) {
    PotPerformers.push_back(p);
  }

  Customer* GetCustomer() {
    return this->customer;
  }
  // надо сделать методов по изменению отзыва
};