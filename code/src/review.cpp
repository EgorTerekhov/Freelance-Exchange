#pragma once
#include <string>
#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/review.hpp"

namespace classes {
  Review::Review(int id , int u_from, int u_to, int order_id, std::string& d, int grade, ReviewStatus s = ReviewStatus::PENDING)
      : id_(id), u_to_(u_to), u_from_(u_from), order_id_(order_id), description_(d), grade_(grade), status_(s) {}

  
  void Review::ReDescrip(const std::string& d) {
    descrip = d;
  }

  json& Review::ToJson(json& j, const Review& r) {
    std::string status;
    if (r.GetStatus() == ReviewStatus::APPROVED) {
      status = "APPROVED";
    } else if (r.GetStatus() == ReviewStatus::PENDING) {
      status = "PENDING";
    } else {
      status = "REJECTED";
    }
    j = {
      {"id", r.GetId()},
      {"to", r.GetUTo()},
      {"from", r.GetUFrom()},
      {"description", r.GetDescription()},
      {"status", status},
      {"grade", r.GetGrade()}
    };
    return j;
  }

  bool Review::operator==(const Review* other) {
    return id_
  }
}  // namespace classes