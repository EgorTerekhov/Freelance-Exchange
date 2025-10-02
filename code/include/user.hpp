#pragma once 

#include <string>


class User {
 protected:
	std::string name;
 	std::string login;
 	std::string password;

 public:

	User(const std::string& name_, const std::string& login_, const std::string& password_) : name(name_), login(login_), password(password_) {
	}

	virtual std::string GetClass() const {
	}

	virtual ~User() = default;
};