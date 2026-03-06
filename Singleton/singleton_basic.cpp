/**
 * @file singleton_basic.cpp
 * @brief Ví dụ cơ bản về Singleton Pattern trong C++
 * 
 * File này minh họa các cách implement Singleton từ đơn giản đến nâng cao
 */

#include <iostream>
#include <string>
#include <mutex>
#include<memory>

// ============================================================================
// VÍ DỤ 1: MEYERS' SINGLETON (Được khuyến nghị - C++11 trở lên)
// ============================================================================
/**
 * @class Logger
 * @brief Singleton Logger sử dụng Meyers' Singleton pattern
 * 
 * Đây là cách implement đơn giản và an toàn nhất từ C++11
 * - Thread-safe: Có (theo chuẩn C++11)
 * - Lazy initialization: Có
 */
class Logger {
public:
    // Điểm truy cập duy nhất đến instance
    static Logger& getInstance() {
        // Static local variable - chỉ được khởi tạo một lần
        // Thread-safe theo chuẩn C++11 (§6.7 [stmt.dcl] p4)
        static Logger instance;
        return instance;
    }

    // Các phương thức nghiệp vụ
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
        logCount_++;
    }

    void error(const std::string& message) {
        std::cout << "[ERROR] " << message << std::endl;
        logCount_++;
    }

    int getLogCount() const { return logCount_; }

    // Xóa copy constructor và assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    // Constructor PRIVATE - ngăn tạo instance từ bên ngoài
    Logger() : logCount_(0) {
        std::cout << "Logger được khởi tạo!" << std::endl;
    }

    // Destructor có thể private hoặc public
    ~Logger() {
        std::cout << "Logger bị hủy!" << std::endl;
    }

    int logCount_;
};

// ============================================================================
// VÍ DỤ 2: SINGLETON VỚI POINTER (Lazy Initialization cổ điển)
// ============================================================================
/**
 * @class DatabaseConnection
 * @brief Singleton quản lý kết nối database
 * 
 * Sử dụng pointer để lưu instance
 * - Cần xử lý thread-safety thủ công
 * - Cần quản lý memory
 */
class DatabaseConnection {
public:
    static DatabaseConnection* getInstance() {
        if (instance_ == nullptr) {
            instance_ = new DatabaseConnection();
        }
        return instance_;
    }

    // Phương thức hủy singleton (nếu cần)
    static void destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    void connect(const std::string& connectionString) {
        connectionString_ = connectionString;
        isConnected_ = true;
        std::cout << "Đã kết nối đến: " << connectionString_ << std::endl;
    }

    void disconnect() {
        isConnected_ = false;
        std::cout << "Đã ngắt kết nối!" << std::endl;
    }

    bool isConnected() const { return isConnected_; }

    // Xóa copy operations
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

private:
    DatabaseConnection() : isConnected_(false) {
        std::cout << "DatabaseConnection được khởi tạo!" << std::endl;
    }

    ~DatabaseConnection() {
        std::cout << "DatabaseConnection bị hủy!" << std::endl;
    }

    static DatabaseConnection* instance_;
    std::string connectionString_;
    bool isConnected_;
};

// Khởi tạo static member bên ngoài class
DatabaseConnection* DatabaseConnection::instance_ = nullptr;

// ============================================================================
// VÍ DỤ 3: THREAD-SAFE SINGLETON VỚI DOUBLE-CHECKED LOCKING
// ============================================================================
/**
 * @class ConfigManager
 * @brief Singleton thread-safe sử dụng Double-Checked Locking Pattern
 * 
 * Phù hợp khi cần kiểm soát chặt chẽ việc khởi tạo trong môi trường đa luồng
 */
class ConfigManager {
public:
    static ConfigManager* getInstance() {
        // Kiểm tra lần 1 (không cần lock) - tối ưu performance
        if (instance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            // Kiểm tra lần 2 (có lock) - đảm bảo thread-safety
            if (instance_ == nullptr) {
                instance_ = new ConfigManager();
            }
        }
        return instance_;
    }

    void setConfig(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        // Giả lập lưu config
        std::cout << "Config: " << key << " = " << value << std::endl;
    }

    std::string getConfig(const std::string& key) {
        std::lock_guard<std::mutex> lock(mutex_);
        // Giả lập đọc config
        return "value_of_" + key;
    }

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

private:
    ConfigManager() {
        std::cout << "ConfigManager được khởi tạo!" << std::endl;
    }

    static ConfigManager* instance_;
    static std::mutex mutex_;
};

ConfigManager* ConfigManager::instance_ = nullptr;
std::mutex ConfigManager::mutex_;

// ============================================================================
// VÍ DỤ 4: SINGLETON VỚI std::call_once (C++11)
// ============================================================================
/**
 * @class CacheManager
 * @brief Singleton sử dụng std::call_once cho thread-safety
 * 
 * std::call_once đảm bảo hàm chỉ được gọi một lần dù có nhiều thread
 */
class CacheManager {
public:
    static CacheManager& getInstance() {
        std::call_once(initFlag_, []() {
            instance_.reset(new CacheManager());
        });
        return *instance_;
    }

    void put(const std::string& key, const std::string& value) {
        std::cout << "Cache PUT: " << key << " -> " << value << std::endl;
    }

    std::string get(const std::string& key) {
        std::cout << "Cache GET: " << key << std::endl;
        return "cached_" + key;
    }

    CacheManager(const CacheManager&) = delete;
    CacheManager& operator=(const CacheManager&) = delete;

private:
    CacheManager() {
        std::cout << "CacheManager được khởi tạo!" << std::endl;
    }

    static std::unique_ptr<CacheManager> instance_;
    static std::once_flag initFlag_;
};

std::unique_ptr<CacheManager> CacheManager::instance_;
std::once_flag CacheManager::initFlag_;

// ============================================================================
// HÀM MAIN - DEMO
// ============================================================================
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "DEMO SINGLETON PATTERN" << std::endl;
    std::cout << "========================================" << std::endl;

    // --- Demo 1: Meyers' Singleton (Logger) ---
    std::cout << "\n--- Demo 1: Logger (Meyers' Singleton) ---" << std::endl;
    
    // Lần gọi đầu tiên - instance được tạo
    Logger& logger1 = Logger::getInstance();
    logger1.log("Đây là log đầu tiên");

    // Lần gọi thứ hai - trả về cùng instance
    Logger& logger2 = Logger::getInstance();
    logger2.log("Đây là log thứ hai");

    // Kiểm tra cùng một instance
    std::cout << "logger1 và logger2 cùng địa chỉ? " 
              << (&logger1 == &logger2 ? "CÓ" : "KHÔNG") << std::endl;
    std::cout << "Tổng số log: " << logger1.getLogCount() << std::endl;

    // --- Demo 2: DatabaseConnection ---
    std::cout << "\n--- Demo 2: DatabaseConnection ---" << std::endl;
    
    DatabaseConnection* db1 = DatabaseConnection::getInstance();
    db1->connect("mysql://localhost:3306/mydb");
    
    DatabaseConnection* db2 = DatabaseConnection::getInstance();
    std::cout << "db2 đã kết nối? " << (db2->isConnected() ? "CÓ" : "KHÔNG") << std::endl;
    std::cout << "db1 và db2 cùng địa chỉ? " 
              << (db1 == db2 ? "CÓ" : "KHÔNG") << std::endl;

    // --- Demo 3: ConfigManager ---
    std::cout << "\n--- Demo 3: ConfigManager (Thread-safe) ---" << std::endl;
    
    ConfigManager* config = ConfigManager::getInstance();
    config->setConfig("app.name", "MySingletonApp");
    config->setConfig("app.version", "1.0.0");

    // --- Demo 4: CacheManager ---
    std::cout << "\n--- Demo 4: CacheManager (std::call_once) ---" << std::endl;
    
    CacheManager& cache = CacheManager::getInstance();
    cache.put("user:1", "John Doe");
    cache.get("user:1");

    std::cout << "\n========================================" << std::endl;
    std::cout << "KẾT THÚC DEMO" << std::endl;
    std::cout << "========================================" << std::endl;

    // Cleanup (cho pointer-based singletons)
    DatabaseConnection::destroyInstance();

    return 0;
}
