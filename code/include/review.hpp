#pragma once
#include <string>
#include "user.hpp"
#include "order.hpp"

enum class ReviewStatus {
    PENDING,
    APPROVED,
    REJECTED
};

namespace nlohmann {
  class json;
}

namespace classes {
class Review {
  int id_;
  int u_to_;
  int u_from_;
  std::string description_;
  ReviewStatus status_;
  int grade_;

 public:
  Review(int id, User* u_from, User* u_to, Order* o, std::string& d);

  User* GetFrom() const;
  
  User* GetTo() const;

  void ChangeId(int id) { id_ = id; }
  const int GetId() const { return this->name; };
  const int GetUFrom() const { return this->u_from_; };
  const int GetUTo() const { return this->u_to_; };
  const std::string& GetDescription() const { return this->description_; };
  const int GetGrade() const { return this->grade_; };
  ReviewStatus GetStatus() const { return this->status_ };
  static json& ToJson(json& j, const Review& r);

};
}  // namespace classes