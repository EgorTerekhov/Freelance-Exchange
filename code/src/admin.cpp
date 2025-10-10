#include <string>
#include "admin.hpp"
namespace classes {

Admin::Admin(const std::string& name_, const std::string& login_, const std::string& password_)
    : User(name_, login_, password_) {
}
Admin::Admin(const User& u) : User(u) {
}

void Admin::CheckReview(std::vector<Review> all_review, Review* r) {
  auto it = std::find(all_review.begin(), all_review.end(), r);
  if (it != all_review.end()) {
    // if (какая-то интересная проверка отзыва на корректность)
    if (r->u_from->GetClass() == "Performer") {
      Customer* c = dynamic_cast<Customer*>(r->u_to);
      c->reviews.emplace_back(r);
      all_review.erase(it);
    } else if (r->u_from->GetClass() == "Customer") {
      Performer* p = dynamic_cast<Performer*>(r->u_to);
      p->reviews.emplace_back(r);
      all_review.erase(it);
    }
  }
}

}  // namespace classes