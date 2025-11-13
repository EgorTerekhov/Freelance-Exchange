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

using json = nlohmann::json;

namespace classes {
class Database {
 private:
  // нужно сортировать по порядку возрастания id каждый раз
  static std::vector<std::unique_ptr<Customer>> customers_;
  static std::vector<std::unique_ptr<Performer>> performers_;
  static std::vector<std::unique_ptr<Order>> orders_;
  static std::vector<std::unique_ptr<Review>> reviews_;
  static std::vector<std::unique_ptr<Admin>> admins_;
  static std::unique_ptr<Database> instance_;


  ~Database();
  Database() = default;
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  Database(Database&&) = delete;
  Database operator=(Database&&) = delete;
  static int customer_id_;
  static int performer_id_;
  static int order_id_;
  static int review_id_;
  static int admin_id_;

  friend class Admin;
  // singltone
 public:
  //тут короче все методы для создания и удаления сущностей
  static Database& getInstance();

  void DeleteCustomer(int id); // binSearchDelete шаблонный поэтому эти можно удалить
  void DeletePerformer(int id);
  void DeleteAdmin(int id);
  void DeleteOrder(int id);
  void DeleteReview(int id);

  template <class T>
  int BinSearchDelete(int id, std::vector<std::unique_ptr<T>>& vec);

  template <class W>
  void BinSearchFind(int id, std::vector<std::unique_ptr<W>>& vec);
  void CreateCustomer(const std::unique_ptr<Customer> c);
  void CreatePerformer(const std::unique_ptr<Performer> p);
  void CreateOrder(const std::unique_ptr<Order> o);
  void CreateReview(const std::unique_ptr<Review> r);
  void CreateAdmin(const std::unique_ptr<Admin> a);

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
  std::unique_ptr<Admin> FromSingleJsonAdmin(const json& j);
  
  template<typename T>
  std::unique_ptr<T> FromSingleJsonPerformerCustomer(const json& j);

  void FromJsonAdminPerformerCustomer(const json& j);
  json ToJsonPerformer() const;
  json ToJsonCustomer() const;
  json ToJsonAdmin() const;
  json ToJsonReview() const;
  json ToJsonOrder() const;

  template <class G>
  std::vector<std::unique_ptr<G>> GetArr() {
  }
  template <class W>
  json ToJsonPerformerCustomer(json& j, const W& temp) const {
    j = {{"id", temp.GetId()},     {"login", temp.GetLogin()}, {"password", temp.GetPass()},
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
};
template<class T>
int Database::BinSearchDelete(int id, std::vector<std::unique_ptr<T>>& vec) {
    int l = 0, r = static_cast<int>(vec.size()) - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        int current_id = vec[m]->GetId();
        if (id < current_id) r = m - 1;
        else if (id > current_id) l = m + 1;
        else return m;
    }
    return -1;
}

template <typename T>
std::unique_ptr<T> Database::FromSingleJsonPerformerCustomer(const json& j) {
  if (j.is_null())
    return nullptr;

  // Проверка наличия всех ключей
  if (!j.contains("id") || !j.contains("login") || !j.contains("password") ||
      !j.contains("name") || !j.contains("email") || !j.contains("phone")) {
    throw std::invalid_argument("Missing required fields in JSON");
  }

  return std::make_unique<T>(
      j["id"].get<int>(),
      j["login"].get<std::string>(),
      j["password"].get<std::string>(),
      j["name"].get<std::string>(),
      j["email"].get<std::string>(),
      j["phone"].get<std::string>()
  );
}
}  // namespace classes