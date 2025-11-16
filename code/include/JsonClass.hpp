#pragma once
#include "./nlohmann/json.hpp"

using json = nlohmann::json;
namespace classes {
class JsonStruct {
 private:
  JsonStruct() = default;
  JsonStruct(const JsonStruct&) = delete;
  JsonStruct& operator=(const JsonStruct&) = delete;
  JsonStruct(JsonStruct&&) = delete;
  JsonStruct operator=(JsonStruct&&) = delete;
  static json admin;
  static json customer;
  static json order;
  static json review;
  static json performer;
  static std::unique_ptr<JsonStruct> instance;

 public:
  static JsonStruct& getInstance();
  static void initialize();
  static void destroy();

  static void LoadFromAllFiles();
  static void loadAdmin(const std::string& filename = "../data/admin.json");
  static void loadCustomer(const std::string& filename = "../data/customer.json");
  static void loadOrder(const std::string& filename = "../data/order.json");
  static void loadReview(const std::string& filename = "../data/review.json");
  static void loadPerformer(const std::string& filename = "../data/performer.json");

  static json& getAdmin();
  static json& getCustomer();
  static json& getOrder();
  static json& getReview();
  static json& getPerformer();

  static void setAdmin(const json& data) { admin = data; }
  static void setCustomer(const json& data) { customer = data; }
  static void setOrder(const json& data) { order = data; }
  static void setReview(const json& data) { review = data; }
  static void setPerformer(const json& data) { performer = data; }

  ~JsonStruct() = default;

  static void saveAllToData();
  static void saveAdmin(const std::string& filename = "../data/admin.json");
  static void saveCustomer(const std::string& filename = "../data/customer.json");
  static void saveOrder(const std::string& filename = "../data/order.json");
  static void saveReview(const std::string& filename = "../data/review.json");
  static void savePerformer(const std::string& filename = "../data/performer.json");
};
}