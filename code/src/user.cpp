#include "../include/user.hpp"
#include "../include/order.hpp"
#include "../include/database.hpp"
#include "../include/review.hpp"
#include <algorithm>
#include <stdexcept>

using namespace classes;

User::User(int id, std::string login, std::string password)
    : id_(id), login_(std::move(login)), password_(std::move(password)) {
}
//delete review тут не нужно тк его унаследуют все классы, а этот метод должен быть только у админа