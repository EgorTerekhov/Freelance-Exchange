#include <string>

#include "user.hpp"
#include "review.hpp"

namespace classes {
class Admin : public User {
 public:
  Admin(const std::string& login, const std::string& password);
  Admin(const User& u);

  void DeleteReview(std::vector<Review> all_review, Review* r);
  void DeleteCustomer(const Customer& c);
  void DeletePerformer(const Performer& p);
  void DeleteOrder(const Order& o);
  
  void HandleReview(std::shared_ptr<Review> review) override;
  std::vector<std::string> GetOptions() override;
  //деструктор не переопределял тк нет доп. полей
};
}  // namespace classes