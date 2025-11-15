#include "../include/password.hpp"
#include "../include/database.hpp"

std::string PasswordAuth::hashPassword(const std::string& password, const std::string& salt) {
  std::string data = salt + password;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  
  SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
  
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}

std::string PasswordAuth::generateSalt() {
  unsigned char salt[16];
  RAND_bytes(salt, 16);
  
  std::stringstream ss;
  for (int i = 0; i < 16; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)salt[i];
  }
  return ss.str();
}

bool PasswordAuth::checkPassword(const std::string& password, const std::string& salt, const std::string& stored_hash) {
  std::string computed_hash = hashPassword(password, salt);
  return computed_hash == stored_hash;
}

std::vector<std::string> PasswordAuth::RegUser(std::string& login, std::string& password) {
  Database& db = Database::getInstance();
  std::vector<std::string> vec;
  if (db.FindUserByLoginAs(login)) {
    return vec;
  }
  std::string salt = PasswordAuth::generateSalt();
  std::string hash = PasswordAuth::hashPassword();
  vec.push_back(login);
  vec.push_back(hash);
  vec.push_back(salt);
  return vec;
}

bool PasswordAuth::SignInUser(std::string& login, std::string& password) {
  Database& db = Database::getInstance();
  auto* ptr = db.FindUserByLoginAs(login);
  if (ptr) {
    return PasswordAuth::checkPassword(password, ptr->GetSalt(), ptr->GetHash());
  }
  return false;
}