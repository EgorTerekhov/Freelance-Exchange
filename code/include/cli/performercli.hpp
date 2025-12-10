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
  void show_help_performer();
  void help_order_perf();
  void performercli(Performer* p);
  bool PerformerOrders(Performer* p);
  void WorkOrdersPerformerCli(Performer* p);
  void AllOrdersPerformerCli();
  void workOnOrder(int id_order, int id_performer);
  void AllCustomersPerformerCli();
  void AccountPerformerCli(Performer* p);
  bool RatePerformerCli(Performer* p);
  bool ReviewPerfomerCli();
}