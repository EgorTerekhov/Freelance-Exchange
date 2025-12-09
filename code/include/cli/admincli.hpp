#pragma once
#include "../database.hpp"
#include "../order.hpp"
#include "../customer.hpp"
#include "../performer.hpp"
#include "../admin.hpp"
#include <iostream>
#include "algorithm"
#include <string>
#include <regex>

namespace classes {
  void ShowHelpAdminCli(Admin& a);
  void DeleteCustomerCli(int id);
  void DeletePerformerCli(int id);
  void HandleReviewCli(int id);
  void AdminCli(Admin* a);
  void ShowAllCustomersCli(Admin& a);
  void ShowAllPerformersCli(Admin& a);
  void ShowAllOrdersCli(Admin& a);
}