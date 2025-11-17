#pragma once
#include <string>
#include <memory>
#include <vector>

#include "user.hpp"
#include "order.hpp"
#include "review.hpp"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

namespace classes {
class Performer : public User {
 private:
  std::string name_;
  std::string email_;
  std::string phone_;
  std::vector<int> rate_;

 public:
  Performer(int id, std::string login, std::string password, std::string salt, std::string name, std::string email,
            std::string phone, double rate = 0.0);

  Performer(User&& u, std::string name, std::string email, std::string phone, double rate = 0.0);

  void ChangeId(int id) {
    id_ = id;
  }

  void HandleReview(int id) override;

  std::vector<std::string> GetOptions() override {
    std::vector<std::string> a;
    a.push_back("");
    return a;
  }

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

  void SetCustomerRate(int id, int rate);
  double GetPerformerRate(int id);
  
  void AddRate(int rate) {
    rate_.emplace_back(rate);
  }

  double GetRate(int id);

  double FindAvgRate();
};
}  // namespace classes