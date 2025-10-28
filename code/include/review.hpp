#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

enum class ReviewStatus {
    PENDING,
    APPROVED,
    REJECTED
};

namespace classes {
class Review {
  int id_;
  int customer_id;
  User* u_to_;
  Order* o_;
  std::string description_;
  ReviewStatus status_;
  int grade_;

 public:
  Review(int id, User* u_from, User* u_to, Order* o, std::string& d);

  User* GetFrom() const;
  
  User* GetTo() const;

  void ChangeId(int id) { id_ = id; }

  ReviewStatus GetStatus() const;

  int GetScore() {
  }
};
}  // namespace classes