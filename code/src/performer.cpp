#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <limits>
#include <vector>

#include "../include/performer.hpp"
#include "../include/review.hpp"
#include "../include/database.hpp"
#include "../include/admin.hpp"

namespace nlohmann {
  class json;
}

namespace classes {

  Performer::Performer(int id, const std::string& login, const std::string& password, const std::string& name, const std::string& email,
            const std::string& phone, double rate = 0) :
            User(id, login, password), name_(name), email_(email), phone_(phone), rate_(rate) {}

  Performer::Performer(const User& u, const std::string& name, const std::string& email, const std::string& phone, double rate = 0)
                       : User(u), name_(name), email_(email), phone_(phone), rate_(rate) {}

  std::string Performer::GetClass() {
    return "Performer";
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

  void Performer::DeleteReview(Review* review) {
    if (!review) {
      throw std::invalid_argument("Review pointer is null");
    }
    Database& db = Database::getInstance();
    auto it = std::find_if(db.reviews_.begin(), db.reviews_.end(),
                          [review](const auto& ptr) {
                            return ptr.get() == review;
                          });
    if (it != db.reviews_.end()) {
      Review* temp = it->release();
      db.reviews_.erase(it);
      review = temp;
    }
  }

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

  // std::unique_ptr<Performer> Performer::FromJson(const json& j) {
  //   if (!j.contains("id") || !j.contains("login") || !j.contains("password") ||
  //       !j.contains("name") || !j.contains("email") || !j.contains("phone") || !j.contains("rate"))) {
  //         throw std::invalid_argument("Missing required fields in JSON");
  //       }
    
  //   try {
  //     int id = j.at("id").get<int>();
  //     std::string login = j.at("login").get<std::string>();
  //     std::string password = j.at("password").get<std::string>();
  //     std::string name = j.at("name").get<std::string>();
  //     std::string email = j.at("email").get<std::string>();
  //     std::string phone = j.at("phone").get<std::string>();
  //     double rate = j.at("rate").get<double>();

  //     return std::make_unique<Performer>(id, login, password, name, email, phone, rate);
  //   } catch (const json::exception& a) {
  //     throw std::invalid_argument("Invalid JSON format: " + std::string(e.what()));
  //   }
  // }

}  // namespace classes