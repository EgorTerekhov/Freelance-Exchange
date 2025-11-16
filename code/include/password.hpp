#pragma once
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>

namespace classes {
class PasswordAuth {
 private:

  static std::string hashPassword(const std::string& password, const std::string& salt);
  
  static std::string generateSalt();
  
  static bool checkPassword(const std::string& password, const std::string& salt, const std::string& stored_hash);

 public:
  PasswordAuth() = default;
  ~PasswordAuth() = default;
  
  static std::pair<std::string, std::string> RegUser(std::string& login, std::string& password);
  static bool SignInUser(std::string& login, std::string& password);
};
}
