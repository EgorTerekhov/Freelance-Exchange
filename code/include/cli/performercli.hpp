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
  bool performercli(Perfomer* p);
  bool PerformerOrders(Perfomer* p);
  void WorkOrdersPerformerCli(Perfomer* p);
  void AllOrdersPerformerCli();
  void workOnOrder(int id_order, int id_performer);
  void AllCustomersPerformerCli();
  void AccountPerformerCli(Performer* p);
  bool RatePerformerCli(Performer* p);
  bool ReviewPerfomerCli(Perfomer* p);
}