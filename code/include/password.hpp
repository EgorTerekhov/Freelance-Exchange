#pragma once
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <string>
#include <sstream>
#include <iomanip>

class PasswordAuth {
 private:

  static std::string hashPassword(const std::string& password, const std::string& salt);
  
  static std::string generateSalt();
  
  static bool checkPassword(const std::string& password, const std::string& salt, const std::string& stored_hash) {
    std::string computed_hash = hashPassword(password, salt);
    return computed_hash == stored_hash;
  }

 public:
  
 static std::vector<std::string> RegUser(std::string& login, std::string& password);
 static bool SignInUser(std::string& login, std::string& password);
};