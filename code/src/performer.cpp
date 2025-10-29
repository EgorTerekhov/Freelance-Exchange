#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <limits>
#include <vector>

#include "../include/performer.hpp"
#include "../include/review.hpp"

namespace classes {
  //Поля:
  // std::string email;
  // std::string phone;
  // std::string doc_path = "";
  // std::string occupation;
  // std::vector<std::shared_ptr<Order>> CompleteOrders;
  // std::vector<std::weak_ptr<Order>> InProgressOrders;
  // std::vector<std::weak_ptr<Order>> PotOrders;
  // std::vector<Review> reviews;
  // double rate;

  Performer::Performer(const std::string name_, const std::string login_, const std::string password_, std::string email_,
                      const std::string phone_)
      : User(name_, login_, password_), email(email_), phone(phone_), rate(0) {
  }

  Performer::Performer(const User& u, const std::string& email_, const std::string& phone_)
      : User(u), email(email_), phone(phone_), rate(0) {
  }

  std::vector<std::weak_ptr<Order>>::iterator Performer::FindInProgressOrder(std::shared_ptr<Order>& o) {
    auto it = std::find(InProgressOrders.begin(), InProgressOrders.end(), o);
    return it;
  }

  std::vector<std::shared_ptr<Order>>::iterator Performer::FindCompleteOrder(std::shared_ptr<Order>& o) {
    auto it = std::find(CompleteOrders.begin(), CompleteOrders.end(), o);
    return it;
  }

  std::string Performer::GetClass() {
    return "performer";
  }

  void Performer::HandleReview(Review* review) { // сделаем пока так, что при вызове функции он должен все поля переопределять, если же не хочет менять - enter
    if (!review || review->GetStatus() != ReviewStatus::APPROVED) {
      return;
    }
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Current id: " << review->id_ << " | Enter new id (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
      try {
        review->id_ = std::stoi(input);
      } catch (std::exception& e) {
        std::cout << "Invalid input for id. Keeping current value." << std::endl;
      }
    }

    std::cout << "Current u_to: " << review->u_to_ << " | Enter new u_to (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
      try {
        review->u_to_ = std::stoi(input);
      } catch (const std::exception& e) {
        std::cout << "Invalid input for u_to. Keeping current value." << std::endl;
      }
    }
    
    std::cout << "Current description: " << review->description_ << " | Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        review->description_ = input;
    }

    std::cout << "Current grade: " << review->grade_ << " | Enter new grade (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
      try {
          review->grade_ = std::stoi(input);
      } catch (const std::exception& e) {
          std::cout << "Invalid input for grade. Keeping current value." << std::endl;
      }
    }
    std::cout << "Review updated successfully!" << std::endl;
  }


  void Performer::CompleteOrder(std::shared_ptr<Order>& o) {
    auto it = FindInProgressOrder(o);
    if (it != InProgressOrders.end()) {
      InProgressOrders.erase(it);
      CompleteOrders.push_back(o);
      o->CompleteOrder();
    }
  }

  void Performer::AddInProgressOrder(std::shared_ptr<Order> o) {
    InProgressOrders.emplace_back(o);
    auto it = std::find(PotOrders.begin(), PotOrders.end(), o);
    if (it != PotOrders.end()) {
      PotOrders.erase(it);
    }
  }

  void Performer::RespondToOrder(std::shared_ptr<Order> o) {
    o->AddPotPerformer(this);
    PotOrders.emplace_back(o);
  }

  void Performer::DelPotOrders() {
    for (auto it = PotOrders.begin(); it != PotOrders.end();) {
      if (auto o = it->lock()) {
        if (o->GetStatus() == OrderStatus::Complete) {
          it = PotOrders.erase(it);
          continue;
        }
      }
      ++it;
    }
  }
  // Нужно как-то настроить тригер на то, чтобы order удалялся из potorder в случае, если проект завершен
  // То есть проект, который уже ведется каким-то другим челом, может висеть у нашего performer, но должен удаляться,
  // если он завершен

  void Performer::LoadDoc(const std::string& doc) {
    doc_path = doc;
  }

  void Performer::MakeReview(std::vector<Review> all_review, std::shared_ptr<Order> o, const std::string& descrip) {
    auto it = FindCompleteOrder(o);
    if (it != CompleteOrders.end()) {
      all_review.emplace_back(this, o->GetCustomer(), o, descrip);
    }
  }

  json& Customer::ToJson(json& j, const Performer& p) {
    j = {
      {"id", p.GetId()},
      {"login", p.GetLogin()},
      {"password", p.GetPass()},
      {"name", p.GetName()},
      {"email", p.GetEmail()},
      {"phone", p.GetPhone()}
    };
  }
}  // namespace classes