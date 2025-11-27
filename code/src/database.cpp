#include "../include/database.hpp"
#include "../include/JsonClass.hpp"
#include "/usr/include/nlohmann/json.hpp"
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

namespace classes {

// ====== Методы создания сущностей ======
void Database::CreateCustomer(std::unique_ptr<Customer>&& c) {
  c->ChangeId(++user_id_);
  customers_.push_back(std::move(c));
  SortById(customers_);
}

void Database::CreatePerformer(std::unique_ptr<Performer>&& p) {
  p->ChangeId(++user_id_);
  performers_.push_back(std::move(p));
  SortById(performers_);
}

void Database::CreateOrder(std::unique_ptr<Order>&& o) {
  o->ChangeId(++order_id_);
  orders_.push_back(std::move(o));
  SortById(orders_);
}

void Database::CreateReview(std::unique_ptr<Review>&& r) {
  
  r->ChangeId(++review_id_);
  reviews_.push_back(std::move(r));
  int id_performer = r->GetUTo();
  int id = BinSearchDelete<Performer>(id_performer, performers_);
  if (id != -1) {
    performers_[id]->AddRate(r->GetGrade());
  }
  SortById(reviews_);
}

void Database::CreateAdmin(std::unique_ptr<Admin>&& a) {
  a->ChangeId(++user_id_);
  admins_.push_back(std::move(a));
  SortById(admins_);
}

// ====== Методы удаления ======
void Database::DeleteCustomer(int id) {
  int idx = BinSearchDelete(id, customers_);
  if (idx != -1)
    customers_.erase(customers_.begin() + idx);

  // Удаляем заказы этого клиента с WORK или REJECTED
  orders_.erase(
      std::remove_if(orders_.begin(), orders_.end(),
                     [id](const std::unique_ptr<Order>& o) {
                       return o && o->GetCustomer() == id &&
                              (o->GetStatus() == OrderStatus::WORK || o->GetStatus() == OrderStatus::REJECTED);
                     }),
      orders_.end());
}

void Database::DeletePerformer(int id) {
  int idx = BinSearchDelete(id, performers_);
  if (idx != -1)
    performers_.erase(performers_.begin() + idx);

  // Обнуляем performer у активных заказов
  for (auto& o : orders_) {
    if (o && o->GetPerformer() == id && o->GetStatus() == OrderStatus::WORK)
      o->ChangePerformer(0);
  }
}

void Database::DeleteOrder(int id) {
  int idx = BinSearchDelete(id, orders_);
  if (idx != -1)
    orders_.erase(orders_.begin() + idx);
}

void Database::DeleteAdmin(int id) {
  int idx = BinSearchDelete(id, admins_);
  if (idx != -1)
    admins_.erase(admins_.begin() + idx);
}

void Database::DeleteReview(int id) {
  int idx = BinSearchDelete(id, reviews_);
  if (idx != -1) {
    reviews_.erase(reviews_.begin() + idx);
  }
}


// ====== JSON методы ======
json Database::ToJsonCustomer() {
  json j;
  json arr = json::array();
  for (const auto& c : customers_) {
    if (c) {
      json k;
      arr.push_back(ToJsonSinglePerformerCustomer(k, *c));
    }
  }
  if (arr.empty() || arr.is_null()) {
    return j;
  }
  j["type"] = "customer";
  j["customers"] = arr;
  return j;
}

json Database::ToJsonPerformer() {
  json j;
  json arr = json::array();
  for (const auto& p : performers_) {
    if (p) {
      json k;
      arr.push_back(ToJsonSinglePerformerCustomer(k, *p));
    }
  }
  if (arr.empty() || arr.is_null()) {
    return j;
  }
  j["type"] = "performer";
  j["performers"] = arr;
  return j;
}

json Database::ToJsonAdmin() {
  json j;
  json arr = json::array();
  for (const auto& a : admins_) {
    if (a)
      arr.push_back(Admin::ToJson(*a));
  }
  if (arr.empty() || arr.is_null()) {
    return j;
  }
  j["type"] = "admin";
  j["admins"] = arr;
  return j;
}

json Database::ToJsonReview() {
  json j;
  json arr = json::array();
  for (const auto& r : reviews_) {
    if (r)
      arr.push_back(Review::ToJson(*r));  // передаём объект
  }
  if (arr.empty() || arr.is_null()) {
    return j;
  }
  j["type"] = "review";
  j["reviews"] = arr;
  return j;
}

json Database::ToJsonOrder() {
  json j;
  json arr = json::array();
  for (const auto& o : orders_) {
    if (o)
      arr.push_back(Order::ToJson(*o));
  }
  if (arr.empty() || arr.is_null()) {
    return j;
  }
  j["type"] = "order";
  j["orders"] = arr;
  return j;
}

// ====== Методы JSON загрузки ======
std::unique_ptr<Admin> Database::FromSingleJsonAdmin(const json& j) {
  if (j.is_null() || j.empty()) {
    return nullptr;
  }

  if (!j.contains("id") || !j.contains("login") || !j.contains("password") || !j.contains("salt")) {
    throw std::invalid_argument("Missing required fields in JSON");
  }

  return std::make_unique<Admin>(j["id"].get<int>(), j["login"].get<std::string>(), j["password"].get<std::string>(), j["salt"].get<std::string>());
}


// Общая загрузка Admin/Performer/Customer
void Database::FromJsonAdminPerformerCustomer(const json& j) {
  if (j.is_null() || j.empty()) {
    return;
  }
  if (!j.contains("type"))
    throw std::invalid_argument("Missing 'type' field");

  if (j.size() == 1) {
    return;
  }
  const std::string type = j["type"].get<std::string>();

  if (type == "admin" && j.contains("admins") && j["admins"].is_array()) {
    for (const auto& item : j["admins"]) {
      auto admin = FromSingleJsonAdmin(item);
      if (admin) {
        CreateAdmin(std::move(admin));
      }
    }
  }
    else if (type == "performer" && j.contains("performers") && j["performers"].is_array()) {
      for (const auto& item : j["performers"]) {
        auto perf = FromSingleJsonPerformerCustomer<Performer>(item);
        if (perf) {
          CreatePerformer(std::move(perf));
        }
      }
    }
    else if (type == "customer" && j.contains("customers") && j["customers"].is_array()) {
      for (const auto& item : j["customers"]) {
        auto cust = FromSingleJsonPerformerCustomer<Customer>(item);
        if (cust) {
          CreateCustomer(std::move(cust));
        }
      }
    }
    else {
      throw std::invalid_argument("Unknown type or missing array for type: " + type);
    }
  }

  User* Database::FindUserByLogin(std::string& login) {
    for (const auto& customer : customers_) {
      if (customer->GetLogin() == login) {
        return customer.get();
      }
    }
    for (const auto& performer : performers_) {
      if (performer->GetLogin() == login) {
        return performer.get();
      }
    }
    for (const auto& admin : admins_) {
      if (admin->GetLogin() == login) {
        return admin.get();
      }
    }
    return nullptr;
  }

  void Database::initialize() {
    Database& db = Database::getInstance();
    JsonStruct& js = JsonStruct::getInstance();
    js.initialize();
    db.FromJsonAdminPerformerCustomer(js.getAdmin());
    db.FromJsonAdminPerformerCustomer(js.getPerformer());
    db.FromJsonAdminPerformerCustomer(js.getCustomer());
    db.FromJsonId(js.GetId());
    // FromJsonReview
    // FromJsonOrder
  }

  void Database::FromJsonId(const json& j) {
    if (j.is_null() || j.empty() || !j.contains("idorder") || !j.contains("iduser") || !j.contains("idreview")) {
      return;
    }
    Database::GetMaxIdOrder() = j["idorder"];
    Database::GetMaxIdReview() = j["idreview"];
    Database::GetMaxIdUser() = j["iduser"];
  }

  void Database::destroy() {
    Database& db = Database::getInstance();
    JsonStruct& js = JsonStruct::getInstance();
    json admin = db.ToJsonAdmin();
    json performer = db.ToJsonPerformer();
    json customer = db.ToJsonCustomer();
    json review = db.ToJsonReview();
    json order = db.ToJsonOrder();
    js.setAdmin(admin);
    js.setPerformer(performer);
    js.setCustomer(customer);
    js.setReview(review);
    js.setOrder(order);
    js.setId(db.GetMaxIdOrder(), db.GetMaxIdUser(), db.GetMaxIdReview());
    js.saveAllToData();
  }

  Order* Database::FindOrder(int id_customer, int id_performer) {
    Database& db = Database::getInstance();
    std::vector<std::unique_ptr<Order>>& orders = db.GetOrderArr();
    auto it = std::find_if(orders.begin(), orders.end(), 
          [id_customer, id_performer](const std::unique_ptr<Order>& o) {
            return (o->GetCustomer() == id_customer && o->GetPerformer() == id_performer);
    });
    if (it != orders.end()) {
      Order* found_order = it->get();
      return found_order;
    }
    return nullptr;
  }
}  // namespace classes
