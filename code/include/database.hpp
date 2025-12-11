#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

#include "nlohmann/json.hpp"
#include "customer.hpp"
#include "performer.hpp"
#include "order.hpp"
#include "review.hpp"
#include "admin.hpp"
#include "user.hpp"

using json = nlohmann::json;

namespace classes {
class Database {
 private:
  // нужно сортировать по порядку возрастания id каждый раз
  std::vector<std::unique_ptr<Customer>> customers_;
  std::vector<std::unique_ptr<Performer>> performers_;
  std::vector<std::unique_ptr<Order>> orders_;
  std::vector<std::unique_ptr<Review>> reviews_;
  std::vector<std::unique_ptr<Admin>> admins_;
  std::unique_ptr<Database> instance_;

  Database() = default;
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  Database(Database&&) = delete;
  Database operator=(Database&&) = delete;
  int user_id_;
  int order_id_;
  int review_id_;

  friend class Admin;
  // singletone
 public:
  //тут короче все методы для создания и удаления сущностей
  static Database& getInstance() {
    static Database instance;
    return instance;
  }

  static void initialize();
  static void destroy();

  void DeleteCustomer(int id);
  void DeletePerformer(int id);
  void DeleteAdmin(int id);
  void DeleteOrder(int id);
  void DeleteReview(int id);

  // void BinSearchFind(int id, std::vector<std::unique_ptr<W>>& vec);
  void CreateCustomer(int id, std::string login, std::string password, std::string salt,
                      std::string name, std::string email,
                      std::string phone);
  void CreatePerformer(int id, std::string login, std::string password, std::string salt,
                      std::string name, std::string email,
                      std::string phone, double rate);
  void CreateOrder(int id, std::string name,
                   double price, std::string description,
                   int customer_id, int performer_id, std::string status, std::vector<int> potenial_performers = std::vector<int>());
  void CreateReview(int id, const int u_from, const int u_to, int order_id, std::string description, double grade);
  void CreateAdmin(int id, std::string login, std::string password, std::string salt);

  std::vector<std::unique_ptr<Customer>>& GetCustomerArr() {
    return customers_;
  }
  std::vector<std::unique_ptr<Performer>>& GetPerformerArr() {
    return performers_;
  }
  std::vector<std::unique_ptr<Admin>>& GetAdminArr() {
    return admins_;
  }
  std::vector<std::unique_ptr<Order>>& GetOrderArr() {
    return orders_;
  }
  std::vector<std::unique_ptr<Review>>& GetReviewArr() {
    return reviews_;
  }
  void FromSingleJsonAdmin(const json& json);

  void FromJsonAdminPerformerCustomer(const json& j);
  json ToJsonPerformer();
  json ToJsonCustomer();
  json ToJsonAdmin();
  json ToJsonReview();
  json ToJsonOrder();


  void FromJsonOrder(const json& j);

  template <class T>
  void SortById(std::vector<std::unique_ptr<T>>& vec) {
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
      if (!a || !b)
        return false;
      return a->GetId() < b->GetId();
    });
  }

  // в json id только растет, нужно для того, чтобы при удалении потом не возникали проблемы с переопределением одного и
  // того же id
  template <class T>
  int BinSearchDelete(int id, std::vector<std::unique_ptr<T>>& vec) {
    int l = 0, r = static_cast<int>(vec.size()) - 1;
    while (l <= r) {
      int m = l + (r - l) / 2;
      int current_id = vec[static_cast<size_t>(m)]->GetId();
      if (id < current_id)
        r = m - 1;
      else if (id > current_id)
        l = m + 1;
      else
        return m;
    }
    return -1;
  }

  json ToJsonSinglePerformer(json& j, Performer& temp);
  json ToJsonSingleCustomer(json& j, Customer& temp);

  void FromSingleJsonPerformer(const json& j);
  void FromSingleJsonCustomer(const json& j);
  ~Database() = default;

  User* FindUserByLogin(std::string& login);

  void FromJsonReview(const json& j);
  void FromJsonId(const json& j);

  template <typename T>
  T* FindUserByLoginAs(std::string& login) {
    User* user = FindUserByLogin(login);
    if (user) {
      return dynamic_cast<T*>(user);
    }
    return nullptr;
  }

  Order* FindOrder(int id_customer, int id_performer);
  int& GetMaxIdOrder() { return order_id_; }
  int& GetMaxIdReview() { return review_id_; }
  int& GetMaxIdUser() { return user_id_; }
};
}  // namespace classes