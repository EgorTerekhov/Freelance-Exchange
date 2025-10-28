#pragma once
#include <string>
#include <memory>

#include "user.hpp"
#include "review.hpp"

namespace nlohmann {
  class json;
}

namespace classes {
  class Admin : public User {
  public:
    Admin(int id, const std::string& login, const std::string& password);
    Admin(const User& u);

    // void DeleteCustomer(const Customer* c);
    // void DeletePerformer(const Performer* p);
    // void DeleteOrder(const Order* o);
    
    // void HandleReview(Review* review) override; //для админа это delete review
    // std::vector<std::string> GetOptions() override;

    // int GetId() const { return this->id_; };
    // const std::string& GetLogin() const { return this->login_; };
    // const std::string& GetPass() const { return this->password_; };

    static std::unique_ptr<Admin> CreateFromJson(const nlohmann::json& j);
    // void LoadFromJson(const nlohmann::json& j);
    // nlohmann::json ToJson() const;
    
    // static Admin* CreateFromJsonRaw(const nlohmann::json& j);

    //деструктор не переопределял тк нет доп. полей

    int GetId() { return id_};
    void ChangeId(int id);
    static json& ToJson(const Admin& a);
    const std::string& GetLogin() const { return this->login_; };
    const std::string& GetPass() const { return this->password_; };
  };
}  // namespace classes