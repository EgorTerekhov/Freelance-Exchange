#include <string>

#include "user.hpp"
#include "review.hpp"

class Admin : public User {

 public:
  Admin(const std::string& name_, const std::string& login_, const std::string& password_)
      : User(name_, login_, password_) {
  }
  Admin(const User& u) : User(u) {
  }

  void CheckReview(Review* r) {
  }

  void DeleteUser(const User& u) {
  }
};