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
  void show_help_customer();
  void customercli(Customer* c);
  bool customerOrders(Customer* c);
  bool createOrderCustomerCli(Customer* c);
  bool createReviewCustomerCli(Customer* c, int order_id);
  void AllPerformersCustomerCli();
  void AccountCustomerCli(Customer* c);
  bool ReviewCustomerCli(Customer* c);
  bool ChoisePerformertoOrder(int id_order, int id_performer, int cust_id);
  bool HandleOrderCustomerCli(Customer* c);
  void WorkOrderCustomerCli(Customer* c);
  void AllReviewCustomerCli(Customer* c);
  void WaitOrderCustomerCli(Customer* c);
  void DoneOrderCustomerCli(Customer* c);
  void CompeteOrderCustomerCli(Customer* c, int id_order);
  void PotentialPerformersCustomerCli(Customer* c, int order_id);
  bool HandleReviewCustomerCli(Customer* c);
}