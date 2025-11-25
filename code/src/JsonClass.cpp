#include "../include/JsonClass.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <iomanip>

namespace classes {


void JsonStruct::initialize() {
  JsonStruct& j = JsonStruct::getInstance();
  j.LoadFromAllFiles();
}

// void JsonStruct::destroy() {
//   JsonStruct::saveAllToData();
//   JsonStruct::instance.reset();
// }

void JsonStruct::LoadFromAllFiles() {
  JsonStruct& j = JsonStruct::getInstance();
  j.LoadMaxId();
  j.loadAdmin();
  j.loadCustomer();
  j.loadOrder();
  j.loadReview();
  j.loadPerformer();
}

void JsonStruct::LoadMaxId(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.idjs;
}

void JsonStruct::loadAdmin(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.admin;
}

void JsonStruct::loadCustomer(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.customer;
}

void JsonStruct::loadOrder(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.order;
}

void JsonStruct::loadReview(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.review;
}

void JsonStruct::loadPerformer(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> j.performer;
}

json& JsonStruct::getAdmin() { 
  JsonStruct& j = JsonStruct::getInstance();
  return j.admin; 
}
json& JsonStruct::getCustomer() {
  JsonStruct& j = JsonStruct::getInstance();
  return j.customer; 
}
json& JsonStruct::getOrder() {
  JsonStruct& j = JsonStruct::getInstance();
  return j.order;
}
json& JsonStruct::getReview() {
  JsonStruct& j = JsonStruct::getInstance();
  return j.review; 
}
json& JsonStruct::getPerformer() {
  JsonStruct& j = JsonStruct::getInstance();
  return j.performer;
}
json& JsonStruct::GetId() {
  JsonStruct& j = JsonStruct::getInstance();
  return j.idjs;
}

void JsonStruct::saveAllToData() {
  JsonStruct& j = JsonStruct::getInstance();
  j.JsonStruct::saveAdmin("./code/data/admin.json");
  j.JsonStruct::saveCustomer("./code/data/customer.json");
  j.JsonStruct::saveOrder("./code/data/order.json");
  j.JsonStruct::savePerformer("./code/data/performer.json");
  j.JsonStruct::saveReview("./code/data/review.json");
  j.JsonStruct::saveId("./code/data/idjs.json");
}

void JsonStruct::setId(int order_id, int user_id, int review_id) {
  JsonStruct& j = JsonStruct::getInstance();
  j.idjs = {
    {"iduser", user_id},
    {"idorder", order_id},
    {"idreview", review_id}
  };
}

void JsonStruct::saveId(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.idjs;
}
void JsonStruct::saveAdmin(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.admin;
}

void JsonStruct::saveCustomer(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.customer;
}

void JsonStruct::savePerformer(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.performer;
}

void JsonStruct::saveReview(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.review;
}

void JsonStruct::saveOrder(const std::string& filename) {
  JsonStruct& j = JsonStruct::getInstance();
  std::ofstream file(filename);
  file << std::setw(4) << j.order;
}
}