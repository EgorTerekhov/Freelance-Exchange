#pragma once
#include "../database.hpp"
#include "../order.hpp"
#include "../customer.hpp"
#include "../performer.hpp"
#include <iostream>
#include "algorithm"
#include <string>
#include <regex>

namespace classes {
  void show_help();
  bool customercli(Customer* c);
  bool customerOrders(Customer* c);
  bool createOrderCustomerCli(Customer* c);
  void AllOrdersCustomerCli();
  void AllPerformersCustomerCli();
  void AccountCustomerCli();
  bool RateCustomerCli(Customer* c);
  void ReviewCustomerCli(Customer* c);
}