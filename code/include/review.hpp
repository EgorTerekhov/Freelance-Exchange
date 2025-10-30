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
  int order_id_;
  std::string description_;
  int grade_;
  ReviewStatus status_;

 public:
  Review(int id, int u_from, int u_to, int order_id, std::string& d, int grade_, ReviewStatus s = ReviewStatus::PENDING);

  void ChangeId(int id) { id_ = id; }
  int& GetId() { return this->name; };
  int& GetUFrom() { return this->u_from_; };
  int& GetUTo() { return this->u_to_; };
  std::string& GetDescription() { return this->description_; };
  int& GetGrade() { return this->grade_; };
  ReviewStatus GetStatus() { return this->status_ };
  static json& ToJson(json& j, const Review& r);
  bool operator==(const Review* other);
};
 // namespace classes