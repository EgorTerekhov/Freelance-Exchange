#include "../include/database.hpp"
#include "/usr/include/nlohmann/json.hpp"
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

namespace classes {

// ====== Статические члены ======
std::vector<std::unique_ptr<Customer>> Database::customers_;
std::vector<std::unique_ptr<Performer>> Database::performers_;
std::vector<std::unique_ptr<Order>> Database::orders_;
std::vector<std::unique_ptr<Review>> Database::reviews_;
std::vector<std::unique_ptr<Admin>> Database::admins_;
std::unique_ptr<Database> Database::instance_ = nullptr;
int Database::customer_id_ = 0;
int Database::performer_id_ = 0;
int Database::order_id_ = 0;
int Database::review_id_ = 0;
int Database::admin_id_ = 0;

// ====== Singleton ======
Database& Database::getInstance() {
    if (!instance_) {
        instance_ = std::make_unique<Database>();
    }
    return *instance_;
}

// ====== Шаблонный бинарный поиск для удаления ======
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

// ====== Сортировка по ID ======
template<class T>
void Database::SortById(std::vector<std::unique_ptr<T>>& vec) {
    std::sort(vec.begin(), vec.end(),
              [](const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) {
                  if (!a || !b) return false;
                  return a->GetId() < b->GetId();
              });
}

// ====== Методы создания сущностей ======
void Database::CreateCustomer(std::unique_ptr<Customer> c) {
    c->ChangeId(++customer_id_);
    customers_.push_back(std::move(c));
    SortById(customers_);
}

void Database::CreatePerformer(std::unique_ptr<Performer> p) {
    p->ChangeId(++performer_id_);
    performers_.push_back(std::move(p));
    SortById(performers_);
}

void Database::CreateOrder(std::unique_ptr<Order> o) {
    o->ChangeId(++order_id_);
    orders_.push_back(std::move(o));
    SortById(orders_);
}

void Database::CreateReview(std::unique_ptr<Review> r) {
    r->ChangeId(++review_id_);
    reviews_.push_back(std::move(r));
    SortById(reviews_);
}

void Database::CreateAdmin(std::unique_ptr<Admin> a) {
    a->ChangeId(++admin_id_);
    admins_.push_back(std::move(a));
    SortById(admins_);
}

// ====== Методы удаления ======
void Database::DeleteCustomer(int id) {
    int idx = BinSearchDelete(id, customers_);
    if (idx != -1) customers_.erase(customers_.begin() + idx);

    // Удаляем заказы этого клиента с WORK или REJECTED
    orders_.erase(std::remove_if(orders_.begin(), orders_.end(),
                                 [id](const std::unique_ptr<Order>& o) {
                                     return o && o->GetCustomer() == id &&
                                            (o->GetStatus() == OrderStatus::WORK ||
                                             o->GetStatus() == OrderStatus::REJECTED);
                                 }),
                  orders_.end());
}

void Database::DeletePerformer(int id) {
    int idx = BinSearchDelete(id, performers_);
    if (idx != -1) performers_.erase(performers_.begin() + idx);

    // Обнуляем performer у активных заказов
    for (auto& o : orders_) {
        if (o && o->GetPerformer() == id && o->GetStatus() == OrderStatus::WORK)
            o->ChangePerformer(0);
    }
}

void Database::DeleteOrder(int id) {
    int idx = BinSearchDelete(id, orders_);
    if (idx != -1) orders_.erase(orders_.begin() + idx);
}

void Database::DeleteAdmin(int id) {
    int idx = BinSearchDelete(id, admins_);
    if (idx != -1) admins_.erase(admins_.begin() + idx);
}

void Database::DeleteReview(int id) {
    int idx = BinSearchDelete(id, reviews_);
    if (idx != -1) reviews_.erase(reviews_.begin() + idx);
}

// ====== JSON методы ======
json Database::ToJsonCustomer() const {
    json j;
    json arr = json::array();
    for (const auto& c : customers_) {
        if (c) {
            json k;
            arr.push_back(ToJsonPerformerCustomer(k, c));
        }
    }
    j["customers"] = arr;
    return j;
}

json Database::ToJsonPerformer() const {
    json j;
    json arr = json::array();
    for (const auto& p : performers_) {
        if (p) {
            json k;
            arr.push_back(ToJsonPerformerCustomer(k, p));
        }
    }
    j["performers"] = arr;
    return j;
}

json Database::ToJsonAdmin() const {
    json j;
    json arr = json::array();
    for (const auto& a : admins_) {
        if (a) arr.push_back(Admin::ToJson(*a));
    }
    j["admins"] = arr;
    return j;
}

json Database::ToJsonReview() const {
    json j;
    json arr = json::array();
    for (const auto& r : reviews_) {
        if (r) arr.push_back(Review::ToJson(*r)); // передаём объект
    }
    j["reviews"] = arr;
    return j;
}


json Database::ToJsonOrder() const {
    json j;
    json arr = json::array();
    for (const auto& o : orders_) {
        if (o) arr.push_back(Order::ToJson(*o));
    }
    j["orders"] = arr;
    return j;
}

// ====== Методы JSON загрузки ======
std::unique_ptr<Admin> Database::FromSingleJsonAdmin(const json& j) {
    if (j.is_null()) return nullptr;
    return std::make_unique<Admin>(
        j["id"].get<int>(),
        j["login"].get<std::string>(),
        j["password"].get<std::string>()
    );
}

std::unique_ptr<Admin> Database::FromSingleJsonPerformerCustomer(const json& j) {
    if (j.is_null()) return nullptr;
    return std::make_unique<Admin>(
        j["id"].get<int>(),
        j["login"].get<std::string>(),
        j["password"].get<std::string>(),
        j["name"].get<std::string>(),
        j["email"].get<std::string>(),
        j["phone"].get<std::string>()
    );
}

// Общая загрузка Admin/Performer/Customer
void Database::FromJsonAdminPerformerCustomer(const json& j) {  
    if (!j.contains("type")) throw std::invalid_argument("Missing 'type' field");

    std::string type = j["type"].get<std::string>();

    if (type == "admin" && j.contains("admins") && j["admins"].is_array()) {
        for (const auto& item : j["admins"]) {
            auto admin = FromSingleJsonAdmin(item);
            if (admin) CreateAdmin(std::move(admin));
        }
    } else if (type == "performer" && j.contains("performers") && j["performers"].is_array()) {
        for (const auto& item : j["performers"]) {
            auto perf = FromSingleJsonPerformerCustomer(item);
            if (perf) CreatePerformer(std::move(perf));
        }
    } else if (type == "customer" && j.contains("customers") && j["customers"].is_array()) {
        for (const auto& item : j["customers"]) {
            auto cust = FromSingleJsonPerformerCustomer(item);   // это же std::unique_ptr<Admin>, от него Customer не создать
            if (cust) CreateCustomer(std::move(cust));
        }
    } else {
        throw std::invalid_argument("Unknown type or missing array for type: " + type);
    }
}

} // namespace classes
