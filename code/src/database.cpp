#include "../include/database.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
template<class T>
void BinSearchDelete(int id, std::vector<std::unique_ptr<T>>& vec) {
  if (vec.size() == 0) {
    return nullptr;
  }
  int l = 0;
  int r = vec.size();
  while (l < r - 1) {
    int m = (l + r) / 2;
    if (id < vec[m].GetId()) {
      r = m;
    } else if (id > vec[m].GetId()) {
      l = m;
    } else {
      return vec[m].erase();
    }
  }
  if (vec[l].GetId() == id) {
    return vec[l].erase();
  }
}

namespace classes {
  Database& Database::getInstance() {
    if (!instance_) {
      instance_ = std::make_unique<Database>();
    }
    return *instance_;
  }

  void Database::DeleteCustomer(int id) {
    BinSearchDelete(id, customers_);
    orders_.erase(
      std::remove_if(orders_.begin(), orders_.end(), 
                    [id](const std::unique_ptr<Order>& s) {
                      return s->GetCustomer() == id && s->GetStatus() == OrderStatus::WORK ||
                              s->GetStatus() == OrderStatus::REJECTED;
                      }
                    ), orders_.end()
                 ); // сортированность вроде сохраняется при такой операции
  }

  void Database::DeletePerformer(int id) {
    BinSearchDelete(id, performers_);
    for (size_t i = 0; i < orders_.size(); ++i) {
      if (orders_[i]->GetPerformer() == id && orders_[i]->GetStatus() == OrderStatus::WORK) {
        orders_[i]->ChangePerformer(0);
      }
    }
  }

  void Database::DeleteOrder(int id) {
    BinSearchDelete(id, orders_);
  }

  void Database::DeleteAdmin(int id) {
    BinSearchDelete(id, admins_);
  }

  void Database::DeleteReview(int id) {
    BinSearchDelete(id, reviews_);
  }

  void Database::CreateCustomer(const std::unique_ptr<Customer> c) {
    int id = ++customer_id_;
    c->ChangeId(id);
    customers_.emplace_back(std::move(c));
    SortById(customers_);
  }

  void Database::CreatePerformer(const std::unique_ptr<Performer> c) {
    int id = ++performer_id_;
    c->ChangeId(id);
    performers_.emplace_back(std::move(c));
    SortById(performers_);
  }

  void Database::CreateOrder(const std::unique_ptr<Order> c) {
    int id = ++order_id_;
    c->ChangeId(id);
    orders_.emplace_back(std::move(c));
    SortById(orders_);
  }

  void Database::CreateReview(const std::unique_ptr<Review> c) {
    int id = ++review_id_;
    c->ChangeId(id);
    reviews_.emplace_back(std::move(c));
    SortById(reviews_);
  }

  void Database::CreateAdmin(const std::unique_ptr<Admin> a) {
    int id = ++admin_id_;
    a->ChangeId(id);
    admins_.emplace_back(std::move(a));
    SortById(admins_);
  }

  std::unique_ptr<Admin> Database::FromSingleJsonPerformerCustomer(const json& j) {
    if (j.is_null()) {
      std::cout << "Json is not NULL"
      return nullptr;
    }

    if (!j.contains("id") || !j.contains("login") || !j.contains("password") || !j.contains("name") || !j.contains("email") || !j.contains("phone")) {
      throw std::invalid_argument("JSON for Performer or Customer must contain id, login, and password");
    }

    if (!j["id"].is_number_integer() || 
        !j["login"].is_string() || 
        !j["password"].is_string() ||
        !j["name"].is_string() ||
        !j["email"].is_string() ||
        !j["phone"].is_string()) {
      throw std::invalid_argument("Invalid types in JSON for customer and performer");
    }

    try {
      return std::make_unique<Admin>(
        j["id"].get<int>(),
        j["login"].get<std::string>(),
        j["password"].get<std::string>(),
        j["name"].get<std::string>(),
        j["email"].get<std::string>(),
        j["phone"].get<std::string>()
      );
    } catch (const std::exception& e) {
      throw std::runtime_error(std::string("Failed to create Admin from JSON: ") + e.what());
    }
  }

  void Database::FromSingleJsonAdmin(const json& j) {
    if (!j.is_null()) {
      std::cout << "Json is not NULL"
      return;
    }

    if (!j.contains("id") || !j.contains("login") || !j.contains("password")) {
      throw std::invalid_argument("JSON for Admin must contain id, login, and password");
    }

    if (!j["id"].is_number_integer() || 
        !j["login"].is_string() || 
        !j["password"].is_string()) {
      throw std::invalid_argument("Invalid types in JSON for Admin");
    }

    try {
      return std::make_unique<Admin>(
        j["id"].get<int>(),
        j["login"].get<std::string>(),
        j["password"].get<std::string>()
      );
    } catch (const std::exception& e) {
      throw std::runtime_error(std::string("Failed to create Admin from JSON: ") + e.what());
    }
  }

  void Database::FromJsonAdminPerformerCustomer(const json& j) {
    if ((j.contains("admins") && j["admins"].is_array()) || 
        (j.contains("performers") && j["performers"].is_array()) || 
        (j.contains("customers") && j["customers"].is_array())) {
      if (j.contains("type")) {
        std::string type = j["type"].get<std::string>();
        if (type == "admin" && j.contains("admins") && j["admins"].is_array()) {
          const auto& admins_array = j["admins"];
          for (size_t i = 0; i < admins_array.size(); ++i) {
              try {
                  const auto& admin_json = admins_array[i];
                  if (admin_json.is_null()) {
                      std::cout << "Warning: null admin at index " << i << ", skipping" << std::endl;
                      continue;
                  }
                  auto admin = FromSingleJsonAdmin(admin_json);
                  if (admin) {
                      CreateAdmin(std::move(admin));
                  }
              } catch (const std::exception& e) {
                  throw std::runtime_error("Failed parse admin at index: " + std::to_string(i) + " - " + e.what());
              }
          }
        }
        else if (type == "performer" && j.contains("performers") && j["performers"].is_array()) {
          const auto& performers_array = j["performers"];
          for (size_t i = 0; i < performers_array.size(); ++i) {
              try {
                  const auto& performer_json = performers_array[i];
                  if (performer_json.is_null()) {
                      std::cout << "Warning: null performer at index " << i << ", skipping" << std::endl;
                      continue;
                  }
                  auto performer = FromSingleJsonPerformerCustomer(performer_json);
                  if (performer) {
                      CreatePerformer(std::move(performer));
                  }
              } catch (const std::exception& e) {
                  throw std::runtime_error("Failed parse performer at index: " + std::to_string(i) + " - " + e.what());
              }
          }
        }
        else if (type == "customer" && j.contains("customers") && j["customers"].is_array()) {
          const auto& customers_array = j["customers"];
          for (size_t i = 0; i < customers_array.size(); ++i) {
              try {
                  const auto& customer_json = customers_array[i];
                  if (customer_json.is_null()) {
                      std::cout << "Warning: null customer at index " << i << ", skipping" << std::endl;
                      continue;
                  }
                  auto customer = FromSingleJsonPerformerCustomer(customer_json);
                  if (customer) {
                      CreateCustomer(std::move(customer));  // Исправлено на CreateCustomer
                  }
              } catch (const std::exception& e) {
                  throw std::runtime_error("Failed parse customer at index: " + std::to_string(i) + " - " + e.what());
              }
          }
        }
        else {
          throw std::invalid_argument("Unknown type or missing array for type: " + type);
        }
      } else {
        throw std::invalid_argument("Missing 'type' field in JSON");
      }
    } else {
      throw std::invalid_argument("Incorrect JSON structure: missing required arrays");
    }
  }


  json Database::ToJsonAdmin() const {
    json j;
    json admin_array = json::array();
    for (const auto& admin : admins_) {
      if (admin) {
        admin_array.push_back(admin->ToJson(admin));
      }
    }
    j["admins"] = admin_array;
    return j;
  }

  json Database::ToJsonPerformer() const {
    json j;
    json performer_array = json::array();
    for (const auto& performer : performers_) {
      if (performer) {
        json k;
        performer_array.push_back(ToJsonPerformerCustomer(k, performer));
      }
    }
    j["performers"] = performer_array;
    return j;
  }

  json Database::ToJsonCustomer() const {
    json j;
    json customer_array = json::array();
    for (const auto& customer : customers_) {
      if (performer) {
        json k;
        customer_array.push_back(ToJsonPerformerCustomer(k, customer));
      }
    }
    j["customers"] = customer_array;
    return j;
  }

  json Database::ToJsonReview() const {
    json j;
    json review_array = json::array();
    for (const auto& review : reviews_) {
      if (review) {
        json k;
        review_array.push_back(review->ToJson(k, review));
      }
    }
    j["customers"] = review_array;
    return j;
  }

  json Database::ToJsonOrder() const {
    json j;
    json order_array = json::array();
    for (const auto& order : orders_) {
      if (order) {
        json k;
        order_array.push_back(order->ToJson(k, order));
      }
    }
    j["orders"] = review_array;
    return j;
  }


























}

// void Database::DeleteOrder(int id)
