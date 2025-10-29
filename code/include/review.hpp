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
  int order_id;
  std::string description_;
  ReviewStatus status_;
  int grade_;

 public:
  Review(int id, int u_from, int u_to, int order_id, std::string& d);

  void ChangeId(int id) { id_ = id; }
  const int GetId() const { return this->name; };
  const int GetUFrom() const { return this->u_from_; };
  const int GetUTo() const { return this->u_to_; };
  const std::string& GetDescription() const { return this->description_; };
  const int GetGrade() const { return this->grade_; };
  ReviewStatus GetStatus() const { return this->status_ };
  static json& ToJson(json& j, const Review& r);

};
 // namespace classes