#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "order.hpp"

namespace classes {
class Customer : public User {
 private:
  std::vector<Order*> orders;
  std::string email;
  std::string phone;
  std::vector<Review*> reviews;
  double rate;

 public:
  Customer(const std::string login_, const std::string password_, const std::string name_, std::string email_,
           const std::string phone_);
  Customer(const User& u, const std::string name_, const std::string& email_, const std::string& phone_);

  void CreateProfile(const std::string login_, const std::string password_, const std::string name_, std::string email_,
                     const std::string phone_);

  Order* PlaceAnOrder(const std::string& name, Customer* c, const std::string& p, const std::string& disc, const std::string& d_c,
        const std::string& term);

  void RemoveOrder(Order*);

  void MakeReview(User* u_from_, User* u_to_, Order* o_, std::string& d_);
};
}  // namespace classes