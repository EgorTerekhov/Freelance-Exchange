#include <string>

#include "user.hpp"
#include "review.hpp"

namespace classes {
class Admin : public User {

 public:
  Admin(const std::string& name_, const std::string& login_, const std::string& password_);
  Admin(const User& u);

  void CheckReview(std::vector<Review> all_review, Review* r);

  void DeleteUser(const User& u);
};
}  // namespace classes