#include "customer.hpp"
#include "performer.hpp"
#include "order.hpp"
#include "review.hpp"
#include "admin.hpp"
namespace classes {
class Database {
 private:
  std::vector<std::unique_ptr<Customer>> customers_;
  std::vector<std::unique_ptr<Performer>> performers_;
  std::vector<std::unique_ptr<Order>> orders_;
  std::vector<std::unique_ptr<Review>> reviews_;
  std::vector<std::unique_ptr<Admin>> admins_;
  int customer_id_ = 1;
  int performer_id_ = 1;
  int order_id_ = 1;
  int review_id_ = 1;
  int admin_id_ = 1;
 public:
  //тут короче все методы для создания и удаления сущностей

  void DeleteCustomer(const std::unique_ptr<Customer> c);
  void DeletePerformer(const std::unique_ptr<Performer> p);
  void DeleteOrder(const std::unique_ptr<Order> o);
  void DeleteReview(const std::unique_ptr<Review> r);

  void CreateCustomer(const std::unique_ptr<Customer> c);
  void CreatePerformer(const std::unique_ptr<Performer> p);
  void CreateOrder(const std::unique_ptr<Order> o);
  void CreateReview(const std::unique_ptr<Review> r);

  void CompleteOrder(std::unique_ptr<Order>);
  void AddPerformerToOrder(std::unique_ptr<Performer>);
};
}