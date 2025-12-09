#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace classes {
class JsonStruct {
 private:
  JsonStruct() = default;
  JsonStruct(const JsonStruct&) = delete;
  JsonStruct& operator=(const JsonStruct&) = delete;
  JsonStruct(JsonStruct&&) = delete;
  JsonStruct operator=(JsonStruct&&) = delete;
  json admin;
  json customer;
  json order;
  json review;
  json performer;
  json idjs;

 public:
  static void initialize();

  static JsonStruct& getInstance() {
    static JsonStruct instance;
    return instance;
  }

  void LoadFromAllFiles();
  void loadAdmin(const std::string& filename = "./code/data/admin.json");
  void loadCustomer(const std::string& filename = "./code/data/customer.json");
  void loadOrder(const std::string& filename = "./code/data/order.json");
  void loadReview(const std::string& filename = "./code/data/review.json");
  void loadPerformer(const std::string& filename = "./code/data/performer.json");
  void LoadMaxId(const std::string& filename = "./code/data/idjs.json");

  json& getAdmin();
  json& getCustomer();
  json& getOrder();
  json& getReview();
  json& getPerformer();
  json& GetId();

  void setAdmin(const json& data) { admin = data; }
  void setCustomer(const json& data) { customer = data; }
  void setOrder(const json& data) { order = data; }
  void setReview(const json& data) { review = data; }
  void setPerformer(const json& data) { performer = data; }
  void setId(int order_id, int user_id, int review_id);
  ~JsonStruct() = default;

  void saveAllToData();
  void saveAdmin(const std::string& filename = "./code/data/admin.json");
  void saveCustomer(const std::string& filename = "./code/data/customer.json");
  void saveOrder(const std::string& filename = "./code/data/order.json");
  void saveReview(const std::string& filename = "./code/data/review.json");
  void savePerformer(const std::string& filename = "./code/data/performer.json");
  void saveId(const std::string& filename = "./code/data/idjs.json");
};
}