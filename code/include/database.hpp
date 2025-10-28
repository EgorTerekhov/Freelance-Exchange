#pragma once
#include "customer.hpp"
#include "performer.hpp"
#include "order.hpp"
#include "review.hpp"
#include "admin.hpp"
#include <algorithm>
#include <iostream>

namespace nlohmann {
  class json;
}
namespace classes {
class Database {
 private:
  // нужно сортировать по порядку возрастания id каждый раз
  std::vector<std::unique_ptr<Customer>> customers_;
  std::vector<std::unique_ptr<Performer>> performers_;
  std::vector<std::unique_ptr<Order>> orders_;
  std::vector<std::unique_ptr<Review>> reviews_;
  std::vector<std::unique_ptr<Admin>> admins_;

  Database() = default;
  static std::unique_ptr<Database> instance_;
  ~Database();
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  Database(Database&&) = delete;
  Database operator=(Database&&) = delete;
  static int customer_id_;
  static int performer_id_;
  static int order_id_;
  static int review_id_;
  static int admin_id_;
  // singltone
 public:
  //тут короче все методы для создания и удаления сущностей
  static Database& getInstance();
  
  void DeleteCustomer(int id);
  void DeletePerformer(int id);
  void DeleteAdmin(int id);
  void DeleteOrder(int id);
  void DeleteReview(int id);

  void CreateCustomer(const std::unique_ptr<Customer> c);
  void CreatePerformer(const std::unique_ptr<Performer> p);
  void CreateOrder(const std::unique_ptr<Order> o);
  void CreateReview(const std::unique_ptr<Review> r);
  void CreateAdmin(const std::unique_ptr<Admin> a);

  void FromSingleJsonAdmin(const json& j);
  void FromSingleJsonPerformerCustomer(const json& j);
  void FromJsonAdminPerformerCustomer(const nlohmann::json& j);
  json ToJsonPerformer() const;
  json ToJsonCustomer() const;
  json ToJsonAdmin() const;
  json ToJsonReview() const;
  json ToJsonOrder() const;
  
  template<class W>
  json ToJsonPerformerCustomer(json& j, const W& temp) const {
    j = {
    {"id", temp.GetId()},
    {"login", temp.GetLogin()},
    {"password", temp.GetPass()},
    {"name", temp.GetName()},
    {"email", temp.GetEmail()},
    {"phone", temp.GetPhone()}
    };
    return j;
  }

  template<class T>
  void SortById(std::vector<std::pair<int, std::unique_ptr<T>>>& vec) {
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
      return a.first < b.first;
    });
  }

  // в json id только растет, нужно для того, чтобы при удалении потом не возникали проблемы с переопределением одного и того же id
};
}