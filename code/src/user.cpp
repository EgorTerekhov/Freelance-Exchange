#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/database.hpp"
#include "../include/review.hpp"
#include <algorithm>
#include <stdexcept>

using namespace classes;

User::User(int id, std::string login, std::string password, std::string salt)
    : id_(id), login_(std::move(login)), password_(std::move(password)), salt_(std::move(salt)) {
}