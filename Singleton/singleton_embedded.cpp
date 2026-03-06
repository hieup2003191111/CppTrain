/**
 * @file singleton_embedded.cpp
 * @brief Ví dụ Singleton Pattern cho Embedded Systems / AUTOSAR
 * 
 * Các ví dụ thực tế áp dụng trong hệ thống nhúng và AUTOSAR
 */

#include <iostream>
#include <cstdint>
#include <array>
#include <functional>
#include <memory>

// ============================================================================
// VÍ DỤ 1: UART DRIVER SINGLETON
// ============================================================================
/**
 * @class UartDriver
 * @brief Singleton quản lý giao tiếp UART
 * 
 * Trong embedded, thường chỉ có một instance quản lý mỗi peripheral
 */
class UartDriver {
public:
    // Cấu hình UART
    struct Config {
        uint32_t baudRate;
        uint8_t dataBits;
        uint8_t stopBits;
        char parity;  // 'N', 'E', 'O'
    };

    static UartDriver& getInstance() {
        static UartDriver instance;
        return instance;
    }

    bool init(const Config& config) {
        if (isInitialized_) {
            std::cout << "[UART] Đã được khởi tạo trước đó!" << std::endl;
            return false;
        }

        config_ = config;
        isInitialized_ = true;
        
        std::cout << "[UART] Khởi tạo thành công:" << std::endl;
        std::cout << "  - Baud rate: " << config_.baudRate << std::endl;
        std::cout << "  - Data bits: " << (int)config_.dataBits << std::endl;
        std::cout << "  - Stop bits: " << (int)config_.stopBits << std::endl;
        std::cout << "  - Parity: " << config_.parity << std::endl;
        
        return true;
    }

    bool transmit(const uint8_t* data, size_t length) {
        if (!isInitialized_) {
            std::cout << "[UART] Lỗi: Chưa khởi tạo!" << std::endl;
            return false;
        }

        std::cout << "[UART] Truyền " << length << " bytes: ";
        for (size_t i = 0; i < length; ++i) {
            std::cout << static_cast<char>(data[i]);
        }
        std::cout << std::endl;
        
        return true;
    }

    bool receive(uint8_t* buffer, size_t maxLength, size_t& receivedLength) {
        if (!isInitialized_) {
            std::cout << "[UART] Lỗi: Chưa khởi tạo!" << std::endl;
            return false;
        }

        // Giả lập nhận dữ liệu
        const char* mockData = "ACK";
        receivedLength = 3;
        for (size_t i = 0; i < receivedLength && i < maxLength; ++i) {
            buffer[i] = mockData[i];
        }
        
        std::cout << "[UART] Nhận " << receivedLength << " bytes" << std::endl;
        return true;
    }

    bool isInitialized() const { return isInitialized_; }

    UartDriver(const UartDriver&) = delete;
    UartDriver& operator=(const UartDriver&) = delete;

private:
    UartDriver() : isInitialized_(false) {
        std::cout << "[UART] Driver instance được tạo" << std::endl;
    }

    Config config_;
    bool isInitialized_;
};

// ============================================================================
// VÍ DỤ 2: ECU STATE MANAGER (AUTOSAR Style)
// ============================================================================
/**
 * @class EcuStateManager
 * @brief Quản lý trạng thái ECU theo phong cách AUTOSAR
 * 
 * Tương tự EcuM module trong AUTOSAR
 */
class EcuStateManager {
public:
    // Các trạng thái ECU
    enum class State : uint8_t {
        OFF,
        STARTUP,
        RUN,
        SLEEP,
        SHUTDOWN
    };

    // Callback type cho state change
    using StateChangeCallback = std::function<void(State oldState, State newState)>;

    static EcuStateManager& getInstance() {
        static EcuStateManager instance;
        return instance;
    }

    void init() {
        std::cout << "[ECU] Khởi tạo EcuStateManager" << std::endl;
        transitionTo(State::STARTUP);
    }

    void run() {
        if (currentState_ == State::STARTUP) {
            transitionTo(State::RUN);
        }
    }

    void sleep() {
        if (currentState_ == State::RUN) {
            transitionTo(State::SLEEP);
        }
    }

    void wakeup() {
        if (currentState_ == State::SLEEP) {
            transitionTo(State::RUN);
        }
    }

    void shutdown() {
        transitionTo(State::SHUTDOWN);
    }

    State getCurrentState() const { return currentState_; }

    std::string getStateString() const {
        switch (currentState_) {
            case State::OFF: return "OFF";
            case State::STARTUP: return "STARTUP";
            case State::RUN: return "RUN";
            case State::SLEEP: return "SLEEP";
            case State::SHUTDOWN: return "SHUTDOWN";
            default: return "UNKNOWN";
        }
    }

    void registerStateChangeCallback(StateChangeCallback callback) {
        callback_ = callback;
    }

    EcuStateManager(const EcuStateManager&) = delete;
    EcuStateManager& operator=(const EcuStateManager&) = delete;

private:
    EcuStateManager() : currentState_(State::OFF), callback_(nullptr) {}

    void transitionTo(State newState) {
        State oldState = currentState_;
        currentState_ = newState;
        
        std::cout << "[ECU] Chuyển trạng thái: " << stateToString(oldState) 
                  << " -> " << stateToString(newState) << std::endl;
        
        if (callback_) {
            callback_(oldState, newState);
        }
    }

    std::string stateToString(State state) const {
        switch (state) {
            case State::OFF: return "OFF";
            case State::STARTUP: return "STARTUP";
            case State::RUN: return "RUN";
            case State::SLEEP: return "SLEEP";
            case State::SHUTDOWN: return "SHUTDOWN";
            default: return "UNKNOWN";
        }
    }

    State currentState_;
    StateChangeCallback callback_;
};

// ============================================================================
// VÍ DỤ 3: DIAGNOSTIC EVENT MANAGER (DEM)
// ============================================================================
/**
 * @class DiagnosticEventManager
 * @brief Quản lý sự kiện chẩn đoán (DTC - Diagnostic Trouble Codes)
 * 
 * Tương tự Dem module trong AUTOSAR
 */
class DiagnosticEventManager {
public:
    static constexpr size_t MAX_EVENTS = 32;

    // Trạng thái DTC
    enum class DtcStatus : uint8_t {
        PASSED = 0x00,
        FAILED = 0x01,
        PENDING = 0x02,
        CONFIRMED = 0x04
    };

    struct DiagnosticEvent {
        uint32_t dtcCode;
        DtcStatus status;
        uint32_t occurrenceCount;
        bool isActive;
    };

    static DiagnosticEventManager& getInstance() {
        static DiagnosticEventManager instance;
        return instance;
    }

    void init() {
        std::cout << "[DEM] Khởi tạo Diagnostic Event Manager" << std::endl;
        for (auto& event : events_) {
            event = {0, DtcStatus::PASSED, 0, false};
        }
        eventCount_ = 0;
    }

    bool reportEvent(uint32_t dtcCode, DtcStatus status) {
        // Tìm event đã tồn tại
        for (size_t i = 0; i < eventCount_; ++i) {
            if (events_[i].dtcCode == dtcCode) {
                events_[i].status = status;
                events_[i].occurrenceCount++;
                events_[i].isActive = (status == DtcStatus::FAILED || 
                                       status == DtcStatus::CONFIRMED);
                std::cout << "[DEM] Cập nhật DTC 0x" << std::hex << dtcCode 
                          << std::dec << std::endl;
                return true;
            }
        }

        // Thêm event mới
        if (eventCount_ < MAX_EVENTS) {
            events_[eventCount_] = {dtcCode, status, 1, 
                                    (status == DtcStatus::FAILED)};
            eventCount_++;
            std::cout << "[DEM] Thêm DTC mới 0x" << std::hex << dtcCode 
                      << std::dec << std::endl;
            return true;
        }

        std::cout << "[DEM] Lỗi: Đầy bộ nhớ DTC!" << std::endl;
        return false;
    }

    void clearAllDtc() {
        for (size_t i = 0; i < eventCount_; ++i) {
            events_[i].status = DtcStatus::PASSED;
            events_[i].isActive = false;
        }
        std::cout << "[DEM] Đã xóa tất cả DTC" << std::endl;
    }

    size_t getActiveDtcCount() const {
        size_t count = 0;
        for (size_t i = 0; i < eventCount_; ++i) {
            if (events_[i].isActive) count++;
        }
        return count;
    }

    void printAllDtc() const {
        std::cout << "[DEM] Danh sách DTC (" << eventCount_ << " mục):" << std::endl;
        for (size_t i = 0; i < eventCount_; ++i) {
            std::cout << "  - DTC 0x" << std::hex << events_[i].dtcCode 
                      << std::dec << ": " << statusToString(events_[i].status)
                      << " (count: " << events_[i].occurrenceCount << ")"
                      << std::endl;
        }
    }

    DiagnosticEventManager(const DiagnosticEventManager&) = delete;
    DiagnosticEventManager& operator=(const DiagnosticEventManager&) = delete;

private:
    DiagnosticEventManager() : eventCount_(0) {}

    std::string statusToString(DtcStatus status) const {
        switch (status) {
            case DtcStatus::PASSED: return "PASSED";
            case DtcStatus::FAILED: return "FAILED";
            case DtcStatus::PENDING: return "PENDING";
            case DtcStatus::CONFIRMED: return "CONFIRMED";
            default: return "UNKNOWN";
        }
    }

    std::array<DiagnosticEvent, MAX_EVENTS> events_;
    size_t eventCount_;
};

// ============================================================================
// VÍ DỤ 4: CAN COMMUNICATION MANAGER
// ============================================================================
/**
 * @class CanManager
 * @brief Quản lý giao tiếp CAN bus
 */
class CanManager {
public:
    struct CanMessage {
        uint32_t id;
        uint8_t data[8];
        uint8_t dlc;  // Data Length Code
    };

    static CanManager& getInstance() {
        static CanManager instance;
        return instance;
    }

    bool init(uint32_t baudRate) {
        baudRate_ = baudRate;
        isInitialized_ = true;
        std::cout << "[CAN] Khởi tạo với baud rate: " << baudRate << " bps" << std::endl;
        return true;
    }

    bool transmit(const CanMessage& msg) {
        if (!isInitialized_) {
            std::cout << "[CAN] Lỗi: Chưa khởi tạo!" << std::endl;
            return false;
        }

        std::cout << "[CAN] TX ID=0x" << std::hex << msg.id << std::dec 
                  << " DLC=" << (int)msg.dlc << " Data=[";
        for (int i = 0; i < msg.dlc; ++i) {
            std::cout << std::hex << (int)msg.data[i];
            if (i < msg.dlc - 1) std::cout << " ";
        }
        std::cout << std::dec << "]" << std::endl;

        txCount_++;
        return true;
    }

    uint32_t getTxCount() const { return txCount_; }
    uint32_t getRxCount() const { return rxCount_; }

    CanManager(const CanManager&) = delete;
    CanManager& operator=(const CanManager&) = delete;

private:
    CanManager() : isInitialized_(false), baudRate_(0), txCount_(0), rxCount_(0) {}

    bool isInitialized_;
    uint32_t baudRate_;
    uint32_t txCount_;
    uint32_t rxCount_;
};

// ============================================================================
// HÀM MAIN - DEMO EMBEDDED SINGLETONS
// ============================================================================
int main() {
    std::cout << "================================================" << std::endl;
    std::cout << "DEMO SINGLETON TRONG EMBEDDED SYSTEMS / AUTOSAR" << std::endl;
    std::cout << "================================================" << std::endl;

    // --- Demo 1: UART Driver ---
    std::cout << "\n--- Demo 1: UART Driver ---" << std::endl;
    
    UartDriver::Config uartConfig = {115200, 8, 1, 'N'};
    UartDriver::getInstance().init(uartConfig);
    
    const uint8_t txData[] = "Hello UART!";
    UartDriver::getInstance().transmit(txData, sizeof(txData) - 1);

    uint8_t rxBuffer[64];
    size_t rxLen;
    UartDriver::getInstance().receive(rxBuffer, sizeof(rxBuffer), rxLen);

    // --- Demo 2: ECU State Manager ---
    std::cout << "\n--- Demo 2: ECU State Manager ---" << std::endl;
    
    auto& ecuMgr = EcuStateManager::getInstance();
    
    // Đăng ký callback
    ecuMgr.registerStateChangeCallback([](EcuStateManager::State oldState, 
                                          EcuStateManager::State newState) {
        std::cout << "  [Callback] Trạng thái thay đổi!" << std::endl;
    });

    ecuMgr.init();
    ecuMgr.run();
    std::cout << "Trạng thái hiện tại: " << ecuMgr.getStateString() << std::endl;
    
    ecuMgr.sleep();
    ecuMgr.wakeup();
    ecuMgr.shutdown();

    // --- Demo 3: Diagnostic Event Manager ---
    std::cout << "\n--- Demo 3: Diagnostic Event Manager ---" << std::endl;
    
    auto& dem = DiagnosticEventManager::getInstance();
    dem.init();
    
    // Báo cáo một số DTC
    dem.reportEvent(0xC0110, DiagnosticEventManager::DtcStatus::FAILED);   // Sensor lỗi
    dem.reportEvent(0xC0120, DiagnosticEventManager::DtcStatus::PENDING);  // Đang kiểm tra
    dem.reportEvent(0xC0130, DiagnosticEventManager::DtcStatus::CONFIRMED);// Lỗi xác nhận
    dem.reportEvent(0xC0110, DiagnosticEventManager::DtcStatus::FAILED);   // Lỗi lặp lại
    
    dem.printAllDtc();
    std::cout << "Số DTC active: " << dem.getActiveDtcCount() << std::endl;

    // --- Demo 4: CAN Manager ---
    std::cout << "\n--- Demo 4: CAN Manager ---" << std::endl;
    
    auto& can = CanManager::getInstance();
    can.init(500000);  // 500 kbps
    
    CanManager::CanMessage msg1 = {0x123, {0x11, 0x22, 0x33, 0x44}, 4};
    CanManager::CanMessage msg2 = {0x456, {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}, 6};
    
    can.transmit(msg1);
    can.transmit(msg2);
    
    std::cout << "Tổng số message đã gửi: " << can.getTxCount() << std::endl;

    std::cout << "\n================================================" << std::endl;
    std::cout << "KẾT THÚC DEMO" << std::endl;
    std::cout << "================================================" << std::endl;

    return 0;
}
