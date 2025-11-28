#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

#include "../nlohmann/json.hpp"
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
  void CreateCustomer(std::unique_ptr<Customer>&& c);
  void CreatePerformer(std::unique_ptr<Performer>&& p);
  void CreateOrder(std::unique_ptr<Order>&& o);
  void CreateReview(std::unique_ptr<Review>&& r);
  void CreateAdmin(std::unique_ptr<Admin>&& a);

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
  std::unique_ptr<Admin> FromSingleJsonAdmin(const json& u);

  void FromJsonAdminPerformerCustomer(const json& j);
  json ToJsonPerformer();
  json ToJsonCustomer();
  json ToJsonAdmin();
  json ToJsonReview();
  json ToJsonOrder();


  void FromJsonOrder(const json& j);

  template <class W>
  json ToJsonSinglePerformerCustomer(json& j, W& temp) {
    j = {{"id", temp.GetId()},     {"login", temp.GetLogin()}, {"password", temp.GetPass()}, {"salt", temp.GetSalt()},
         {"name", temp.GetName()}, {"email", temp.GetEmail()}, {"phone", temp.GetPhone()}};
    return j;
  }

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

  template <typename T>
  std::unique_ptr<T> FromSingleJsonPerformerCustomer(const json& j) {
    if (j.is_null())
      return nullptr;

    // Проверка наличия всех ключей
    if (!j.contains("id") || !j.contains("login") || !j.contains("password") || !j.contains("salt") ||
        !j.contains("name") || !j.contains("email") || !j.contains("phone")) {
      throw std::invalid_argument("Missing required fields in JSON");
    }

    return std::make_unique<T>(j["id"].get<int>(), j["login"].get<std::string>(), j["password"].get<std::string>(),
                               j["salt"].get<std::string>(), j["name"].get<std::string>(),
                               j["email"].get<std::string>(), j["phone"].get<std::string>());
  }
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