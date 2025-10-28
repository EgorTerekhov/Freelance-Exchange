#pragma once
#include <string>
#include <memory>
#include <vector>

#include "user.hpp"
#include "order.hpp"
#include "review.hpp"

namespace nlohmann {
  class json;
}


namespace classes {
class Performer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  // std::vector<Order*> complete_orders_;  //при вызове метода удаления от пользоваетля мы под капотом вызовем метод бд и                                     //освободим память переданного указателя
  // std::vector<Order*> in_progress_orders_;
  // std::vector<Review> reviews_;
  int id_;
  double rate_;

 public:
  Performer(int id, const std::string& login, const std::string& password, const std::string& name, const std::string& email,
            const std::string& phone, const std::vector<Order*>& complete_orders,
            const std::vector<Order*>& in_progress_orders, const std::vector<Review>& reviews, double rate);

  Performer(const User& u, const std::string& name, const std::string& email, const std::string& phone,
            const std::vector<Order*>& complete_orders, const std::vector<Order*>& in_progress_orders,
            const std::vector<Review>& reviews, double rate);

  void CompleteOrder(Order* o);

  void AddInProgressOrder(Order* o); // закинуть какой то заказ в массив заказов, которые он делает

  void RespondToOrder(Order* o);

  void ChangeId(int id) { id_ = id; }

  void HandleReview(Review* review) override;
  int GetId() const { return this->id_; };
  const std::string& GetLogin() const { return this->login_; };
  const std::string& GetPass() const { return this->password_; };

  static Performer* FromJsonRaw(const nlohmann::json& j);
  static std::unique_ptr<Performer> FromJson(const nlohmann::json& j);
};
}  // namespace classes