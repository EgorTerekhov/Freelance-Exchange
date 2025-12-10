#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "user.hpp"
#include "review.hpp"
#include "order.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class Customer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  std::vector<double> rate_;

 public:
  Customer(int id, std::string login, std::string password, std::string salt, std::string name, std::string email,
           std::string phone, double rate = 0.0);
  void CompleteOrder(int id);
  void WorkOrder(int id);

  int GetId() const {
    return this->id_;
  };

  void ChangeId(int id) {
    id_ = id;
  }

  const std::string& GetLogin() const {
    return this->login_;
  };
  const std::string& GetPass() const {
    return this->password_;
  };
  const std::string& GetName() const {
    return this->name_;
  };
  const std::string& GetEmail() const {
    return this->email_;
  };
  const std::string& GetPhone() const {
    return this->phone_;
  };
  void HandleReview(int id) override;

  bool HandleOrder(int id);

  void SetPerformerRate(int id, int rate);
  
  double GetRate();

  void AddRate(double rate) {
    rate_.emplace_back(rate);
  }

  double FindAvgRate();
};
}  // namespace classes