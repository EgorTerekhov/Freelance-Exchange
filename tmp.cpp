class Database {
private:
    std::vector<std::pair<int, std::unique_ptr<Customer>>> customers_;
    std::vector<std::pair<int, std::unique_ptr<Performer>>> performers_;
    // ...

public:
    json to_json() const {
        json j;
        
        // Customers
        json customers_array = json::array();
        for (const auto& [id, customer] : customers_) {
            if (customer) {
                customers_array.push_back(customer->to_json());
            }
        }
        j["customers"] = customers_array;
        
        // Performers
        json performers_array = json::array();
        for (const auto& [id, performer] : performers_) {
            if (performer) {
                performers_array.push_back(performer->to_json());
            }
        }
        j["performers"] = performers_array;
        
        // Orders, Reviews, Admins аналогично...
        
        return j;
    }
    
    void ToJson() const {
        json j = to_json();
        
        // Сохранение в файл
        std::ofstream file("database.json");
        file << j.dump(4); // dump(4) для красивого форматирования
        file.close();
        
        std::cout << "Database saved to database.json" << std::endl;
    }
};