#pragma once
#include <string>
#include <memory>
#include <vector>

#include "user.hpp"
#include "order.hpp"
#include "review.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class Performer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  std::vector<double> rate_; // нужно сделать реализацию выгрузки.

 public:
  Performer(int id, std::string login, std::string password, std::string salt, std::string name, std::string email,
            std::string phone, double rate = 0.0);

  void ChangeId(int id) {
    id_ = id;
  }

  void HandleReview(int id) override;

  int GetId() const {
    return id_;
  };
  const std::string& GetLogin() const {
    return this->login_;
  };
  // const std::string& GetClass() const {
  //   std::string a = "Performer";
  //   r  double FindAvgRate();eturn a;
  // };
  const std::string& GetPass() const {  // нахай баааля
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

  json& ToJson(json& j, const Performer& p);

  void AddRate(double rate) {
    rate_.emplace_back(rate);
  }

  void DeleteRate(double rate) {
    auto it = std::find_if(rate_.begin(), rate_.end(),
          [rate](double& r) {
            return rate == r;
          });
    if (it != rate_.end()) {
      rate_.erase(it);
    }
  }
  double GetRate();

  double FindAvgRate();
};
}  // namespace classes