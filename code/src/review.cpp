#pragma once
#include <string>
#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/review.hpp"

namespace classes {
  Review::Review(User* u_from_, User* u_to_, Order* o_, std::string& d_)
      : u_from(u_from_), u_to(u_to_), o(o_), descrip(d_) {
  }

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