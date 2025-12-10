#include "../../include/cli/admincli.hpp"

namespace classes {

    void ShowHelpAdminCli() {
        std::cout << "Freelance exchange CLI for admin" << std::endl;
        std::cout << "Available commands:" << std::endl;
        std::cout << "help - show this help" << std::endl;
        std::cout << "allcustomers - show all customers" << std::endl;
        std::cout << "allperformers - show all performers" << std::endl;
        std::cout << "allorders - show all orders" << std::endl;
        std::cout << "delete customer \"id\" - delete customer by id" << std::endl;
        std::cout << "delete performer \"id\" - delete performer by id" << std::endl;
        std::cout << "handle review \"id\" - handle review by id" << std::endl;
        std::cout << "exit - exit the program" << std::endl;
    }

    void ShowAllCustomersCli() {
        Database& db = Database::getInstance();
        auto& customers = db.GetCustomerArr();
        for (const auto& c : customers) {
            std::cout << "ID: " << c->GetId() << ", Login: " << c->GetLogin()
                      << ", Name: " << c->GetName() << ", Email: " << c->GetEmail() << std::endl;
        }
    }

    void ShowAllPerformersCli() {
        Database& db = Database::getInstance();
        auto& performers = db.GetPerformerArr();
        for (const auto& p : performers) {
            std::cout << "ID: " << p->GetId() << ", Login: " << p->GetLogin()
                      << ", Name: " << p->GetName() << ", Email: " << p->GetEmail() << std::endl;
        }
    }

    void ShowAllOrdersCli() {
        Database& db = Database::getInstance();
        auto& orders = db.GetOrderArr();
        for (const auto& o : orders) {
            std::cout << "ID: " << o->GetId() << ", Name: " << o->GetName()
                      << ", Customer ID: " << o->GetCustomerId() 
                      << ", Performer ID: " << o->GetPerformerId() 
                      << ", Status: " << static_cast<int>(o->GetStatus()) 
                      << ", Price: " << o->GetPrice() << std::endl;
        }
    }

    void DeleteCustomerCli(int id) {
        Database& db = Database::getInstance();
        db.DeleteCustomer(id);
        std::cout << "Customer with ID " << id << " deleted successfully." << std::endl;
    }

    void DeletePerformerCli(int id) {
        Database& db = Database::getInstance();
        db.DeletePerformer(id);
        std::cout << "Performer with ID " << id << " deleted successfully." << std::endl;
    }

    void HandleReviewCli(int id) {
        Database& db = Database::getInstance();
        db.DeleteReview(id);
        std::cout << "Review with ID " << id << " deleted successfully." << std::endl;
    }

    void AdminCli(Admin* a) {
        std::cout << "Welcome, Admin! Type 'help' to see available commands." << std::endl;
        std::string input;
        while (true) {
            std::cout << "Enter command: ";
            std::getline(std::cin, input);

            if (input == "exit") break;

            if (input == "help") {
                ShowHelpAdminCli();
            } else if (input == "all customers") {
                ShowAllCustomersCli();
            } else if (input == "all performers") {
                ShowAllPerformersCli();
            } else if (input == "all orders") {
                ShowAllOrdersCli();
            } else if (std::regex_match(input, std::regex(R"(delete customer \d+)"))) {
                std::regex pattern(R"(delete customer (\d+))");
                std::smatch matches;
                if (std::regex_search(input, matches, pattern) && matches.size() == 2) {
                    int id = std::stoi(matches[1].str());
                    DeleteCustomerCli(id);
                }
            } else if (std::regex_match(input, std::regex(R"(delete performer \d+)"))) {
                std::regex pattern(R"(delete performer (\d+))");
                std::smatch matches;
                if (std::regex_search(input, matches, pattern) && matches.size() == 2) {
                    int id = std::stoi(matches[1].str());
                    DeletePerformerCli(id);
                }
            } else if (std::regex_match(input, std::regex(R"(handle review \d+)"))) {
                std::regex pattern(R"(handle review (\d+))");
                std::smatch matches;
                if (std::regex_search(input, matches, pattern) && matches.size() == 2) {
                    int id = std::stoi(matches[1].str());
                    HandleReviewCli(id);
                }
            } else {
                std::cout << "Unknown command, try again." << std::endl;
            }
        }
    }

}
