#include "../include/password.hpp"
#include "../include/database.hpp"

namespace classes {
  std::string PasswordAuth::hashPassword(const std::string& password, const std::string& salt) {
  std::string data = salt + password;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  
  SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
  
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return ss.str();
}

std::string PasswordAuth::generateSalt() {
  unsigned char salt[16];
  RAND_bytes(salt, 16);
  
  std::stringstream ss;
  for (int i = 0; i < 16; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(salt[i]);
  }
  return ss.str();
}

bool PasswordAuth::checkPassword(const std::string& password, const std::string& salt, const std::string& stored_hash) {
  std::string computed_hash = hashPassword(password, salt);
  return computed_hash == stored_hash;
}

std::pair<std::string, std::string> PasswordAuth::RegUser(std::string& login, std::string& password) {
  Database& db = Database::getInstance();
  std::pair<std::string, std::string> vec("", "");
  Admin* ptr_1 = db.FindUserByLoginAs<Admin>(login);
  if (ptr_1) {
    return vec;
  }
  Performer* ptr_2 = Database::FindUserByLoginAs<Performer>(login);
  if (ptr_2) {
    return vec;
  }
  Customer* ptr_3 = Database::FindUserByLoginAs<Customer>(login);
  if (ptr_3) {
    return vec;
  }
  std::string salt = PasswordAuth::generateSalt();
  std::string hash = PasswordAuth::hashPassword(password, salt);
  vec.first = hash;
  vec.second = salt;
  return vec;
}

bool PasswordAuth::SignInUser(std::string& login, std::string& password) {
  Admin* ptr_1 = Database::FindUserByLoginAs<Admin>(login);
  if (ptr_1) {
    return PasswordAuth::checkPassword(password, ptr_1->GetSalt(), ptr_1->GetHash());
  }
  Performer* ptr_2 = Database::FindUserByLoginAs<Performer>(login);
  if (ptr_2) {
    return PasswordAuth::checkPassword(password, ptr_1->GetSalt(), ptr_2->GetHash());
  }
  Customer* ptr_3 = Database::FindUserByLoginAs<Customer>(login);
  if (ptr_3) {
    return PasswordAuth::checkPassword(password, ptr_3->GetSalt(), ptr_3->GetHash());
  }
  return false;
}
}
