#include "../include/review.hpp"
#include "../include/user.hpp"
#include "../include/order.hpp"
#include "/usr/include/nlohmann/json.hpp"

using json = nlohmann::json;

namespace classes {

Review::Review(int id, int u_from, int u_to, int order_id, std::string& d, int grade)
    : id_(id), u_to_(u_to), u_from_(u_from), order_id_(order_id), description_(d), grade_(grade) {
}

json& Review::ToJson(const Review& r) {
  static json j;  // статический, т.к. функция возвращает ссылку

  j = {{"id", r.id_},
       {"u_to", r.u_to_},
       {"u_from", r.u_from_},
       {"order_id", r.order_id_},
       {"description", r.description_},
       {"grade", r.grade_}};

  return j;
}

bool Review::operator==(const Review* other) {
  if (!other)
    return false;
  return this->id_ == other->id_;
}

}  // namespace classes
