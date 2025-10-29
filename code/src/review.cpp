#pragma once
#include <string>
#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/review.hpp"

namespace classes {
  Review::Review(int id , int u_to_, int o_, int o_, std::string& d_)
      : id_(id), u_from(u_from_), u_to(u_to_), order_id(o_), descrip(d_) {}

  
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
}  // namespace classes