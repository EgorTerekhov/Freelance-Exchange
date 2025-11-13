#pragma once
#include <string>

#include "../nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
enum class ReviewStatus { PENDING, APPROVED, REJECTED };
class Review {
  int id_;
  int u_to_;
  int u_from_;
  int order_id_;
  std::string description_;
  int grade_;
  ReviewStatus status_;

 public:
  Review(int id, int u_from, int u_to, int order_id, std::string& d, int grade_,
         ReviewStatus s = ReviewStatus::PENDING);

  void ChangeId(int id) {
    id_ = id;
  }
  int& GetId() {
    return this->id_;
  };
  int& GetUFrom() {
    return this->u_from_;
  };
  int& GetUTo() {
    return this->u_to_;
  };
  std::string& GetDescription() {
    return this->description_;
  };
  int& GetGrade() {
    return this->grade_;
  };
  ReviewStatus GetStatus() const {
    return this->status_;
  }
  static json& ToJson(const Review& r);
  bool operator==(const Review* other);
};
}  // namespace classes