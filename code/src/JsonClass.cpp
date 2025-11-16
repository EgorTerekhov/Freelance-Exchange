#include "../include/JsonClass.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

namespace classes {
std::unique_ptr<JsonStruct> JsonStruct::instance = nullptr;

json JsonStruct::admin = json::object();
json JsonStruct::customer = json::object();
json JsonStruct::order = json::object();
json JsonStruct::review = json::object();
json JsonStruct::performer = json::object();

JsonStruct& JsonStruct::getInstance() {
  if (!instance) {
    instance.reset(new JsonStruct());
  }
  return *instance;
}

void JsonStruct::initialize() {
  JsonStruct::getInstance();
  JsonStruct::LoadFromAllFiles();
}

void JsonStruct::destroy() {
  JsonStruct::saveAllToData();
  JsonStruct::instance.reset();
}

void JsonStruct::LoadFromAllFiles() {
  JsonStruct::loadAdmin();
  JsonStruct::loadCustomer();
  JsonStruct::loadOrder();
  JsonStruct::loadReview();
  JsonStruct::loadPerformer();
}

void JsonStruct::loadAdmin(const std::string& filename) {
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> admin;
}

void JsonStruct::loadCustomer(const std::string& filename) {
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> customer;
}

void JsonStruct::loadOrder(const std::string& filename) {
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> admin;
}

void JsonStruct::loadReview(const std::string& filename) {
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> admin;
}

void JsonStruct::loadPerformer(const std::string& filename) {
  std::ifstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file >> admin;
}

json& JsonStruct::getAdmin() { return admin; }
json& JsonStruct::getCustomer() { return customer; }
json& JsonStruct::getOrder() { return order; }
json& JsonStruct::getReview() { return review; }
json& JsonStruct::getPerformer() { return performer; }

void JsonStruct::saveAllToData() {
  JsonStruct::saveAdmin();
  JsonStruct::saveCustomer();
  JsonStruct::saveOrder();
  JsonStruct::savePerformer();
  JsonStruct::saveReview();
}

void JsonStruct::saveAdmin(const std::string& filename) {
  std::ofstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file << admin;
}

void JsonStruct::saveCustomer(const std::string& filename) {
  std::ofstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file << customer;
}

void JsonStruct::savePerformer(const std::string& filename) {
  std::ofstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file << performer;
}

void JsonStruct::saveReview(const std::string& filename) {
  std::ofstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file << review;
}

void JsonStruct::saveOrder(const std::string& filename) {
  std::ofstream file(filename);
  if (file.peek() == std::ifstream::traits_type::eof()) {
    return;
  }
  file << order;
}
}