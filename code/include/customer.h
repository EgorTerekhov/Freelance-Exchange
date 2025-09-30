#pragma once
#include <string>
#include "user.h"
#include "order.h"
#include <vector>
#include <memory>
#include <algorithm>

class Customer : public User {
 private:
  std::vector<std::shared_ptr<Order>> orders;;
  std::string email;
  std::string phone;
  std::vector<Review> reviews;
  double rate;
   
  friend class Admin;
 public:
  Customer(const std::string name_, const std::string login_,
           const std::string password_, std::string email_,
           const std::string phone_) :
           User(name_, login_, password_),
           email(email_),
           phone(phone_),
           rate(0) {
  }
  Customer(const User& u, const std::string& email_, const std::string& phone_)
           : User(u), email(email_), phone(phone_), rate(0) {
  }

  auto FindIt(Order* o) {
    auto it = std::find_if(
      orders.begin(),
      orders.end(),
      [&](const std::unique_ptr<Order>& ptr) { return ptr.get() == o;}
    );
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

  void AddOrder(std::string name, std::string discript, std::string price, std::string date_create, std::string term) {
    orders.push_back(std::make_unique<Order>(name, this, discript, price, date_create, term));
  }
  
  void RemoveOrder(Order* o) {
    auto it = FindIt(o);
    if (it != orders.end() && (*it)->status != OrderStatus::Complete) {
      orders.erase(it);
    }
  }

  std::vector<Performer*>& GetPotPerformers(Order* o) {
    return o->PotPerformers;
  }

  void ChoosePerformers(std::vector<Performer*> performers, Order* o) {
    for (Performer* p : performers) {
      o->MainPerformers.push_back(p);
      auto it = std::find(o->PotPerformers.begin(), o->PotPerformers.end(), p);
      if (it != o->PotPerformers.end()) {
        o->MainPerformers.push_back(p);
        o->PotPerformers.erase(it);
      }
    }
  }


  // void MakeReview(std::shared_ptr<Order> o, Performer* p, const std::string& descrip) {
    
  //   if (o->status == OrderStatus::Complete) {
  //     p->rew.emplace_back(this, o->customer, o, descrip);
  //   }
  // }
  // отзывы через админа должны проходить
};