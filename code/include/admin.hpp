#include <string>

#include "user.hpp"
#include "review.hpp"
namespace classes {
class Admin : public User {
 public:
  Admin(int id, const std::string& login, const std::string& password);
  Admin(const User& u);

  void DeleteCustomer(const Customer* c);
  void DeletePerformer(const Performer* p);
  void DeleteOrder(const Order* o);
  
  void HandleReview(Review* review) override; //для админа это delete review
  std::vector<std::string> GetOptions() override;
  //деструктор не переопределял тк нет доп. полей
};
}  // namespace classes