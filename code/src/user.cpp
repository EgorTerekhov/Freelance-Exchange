#pragma once
#include <string>
#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/database.hpp"
#include "../include/review.hpp"
#include <string>

namespace classes {

User::User(const std::string& name_, const std::string& login_, const std::string& password_)
    : name(name_), login(login_), password(password_) {
}

std::string User::GetClass() const {
  return "User";
}

void User::DeleteReview(Review* review) {
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
}  // namespace classes