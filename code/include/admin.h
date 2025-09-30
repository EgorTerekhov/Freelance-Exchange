// надо сделать класс админа и методы его, чтобы через него отзывы проходили в 

#include <string>
#include "user.h"
#include "review.h"

class Admin : public User {

 public:
  Admin(const std::string& name_, const std::string& login_, const std::string& password_) : User(name_, login_, password_) {
	}
  Admin(const User& u) : User(u) {
  }

  void CheckReview(Review* r) {
    
  }
};