#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "customer.hpp"

namespace classes {

//Поля:
// std::vector<std::shared_ptr<Order>> orders;
// std::string email;
// std::string phone;
// std::vector<Review> reviews;
// double rate;

Customer::Customer(const std::string name_, const std::string login_, const std::string password_, std::string email_,
                   const std::string phone_)
    : User(name_, login_, password_), email(email_), phone(phone_), rate(0) {
}
Customer::Customer(const User& u, const std::string& email_, const std::string& phone_)
    : User(u), email(email_), phone(phone_), rate(0) {
}

std::vector<std::shared_ptr<Order>>::iterator Customer::FindOrder(Order* o) {
  auto it =
      std::find_if(orders.begin(), orders.end(), [&](const std::shared_ptr<Order>& ptr) { return ptr.get() == o; });
  return it;
}

// std::shared_ptr<Order> releaseOrder(Order* o) {
//   auto it = FindIt(o);
//   if (it != orders.end()) {
//     std::shared_ptr<Order> tmp = std::move(*it);
//     orders.erase(it);
//     return tmp;
//   }
//   return nullptr;
// }

void Customer::AddOrder(std::string name, std::string discript, std::string price, std::string date_create,
                        std::string term) {
  orders.push_back(std::make_unique<Order>(name, this, discript, price, date_create, term));
}

void Customer::RemoveOrder(Order* o) {
  auto it = this->FindOrder(o);
  if (it != orders.end() && (*it)->status != OrderStatus::Complete) {
    orders.erase(it);
  }
}

std::string Customer::GetClass() {
  return "customer";
}

std::vector<Performer*>& Customer::GetPotPerformers(std::shared_ptr<Order> o) {
  return o->PotPerformers;
}

void Customer::ChoosePerformers(std::vector<Performer*> performers, std::shared_ptr<Order> o) {
  for (Performer* p : performers) {
    o->MainPerformers.push_back(p);
    auto it = std::find(o->PotPerformers.begin(), o->PotPerformers.end(), p);
    if (it != o->PotPerformers.end()) {
      o->MainPerformers.push_back(p);
      o->PotPerformers.erase(it);
    }
  }
}

void Customer::MakeReview(std::vector<Review> all_review, Order* o, const std::string& descrip) {
  auto it = FindOrder(o);
  if (it != orders.end()) {
    all_review.emplace_back(this, o->GetCustomer(), o, descrip);
  }
}
}  // namespace classes