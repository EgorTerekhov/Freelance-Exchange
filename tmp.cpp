#include <iostream>
#include <string>
#include <limits>

void Performer::HandleReview(Review* review) {
    if (!review) {
        return;
    }

    std::string input;

    // Очистка буфера ввода перед началом
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Поле id_
    std::cout << "Current id: " << review->id_ << " | Enter new id (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->id_ = std::stoi(input);
        } catch (const std::exception& e) {
            std::cout << "Invalid input for id. Keeping current value." << std::endl;
        }
    }

    // Поле u_to_
    std::cout << "Current u_to: " << review->u_to_ << " | Enter new u_to (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->u_to_ = std::stoi(input);
        } catch (const std::exception& e) {
            std::cout << "Invalid input for u_to. Keeping current value." << std::endl;
        }
    }

    // Поле order_id
    std::cout << "Current order_id: " << review->order_id << " | Enter new order_id (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->order_id = std::stoi(input);
        } catch (const std::exception& e) {
            std::cout << "Invalid input for order_id. Keeping current value." << std::endl;
        }
    }

    // Поле description_
    std::cout << "Current description: " << review->description_ << " | Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        review->description_ = input;
    }

    // Поле grade_
    std::cout << "Current grade: " << review->grade_ << " | Enter new grade (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            review->grade_ = std::stoi(input);
        } catch (const std::exception& e) {
            std::cout << "Invalid input for grade. Keeping current value." << std::endl;
        }
    }

    std::cout << "Review updated successfully!" << std::endl;
}