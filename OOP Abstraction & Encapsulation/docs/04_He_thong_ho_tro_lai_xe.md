# Hệ thống hỗ trợ lái xe (ADAS) sử dụng Abstraction và Encapsulation

Hệ thống Hỗ trợ Lái xe Nâng cao (Advanced Driver-Assistance Systems - ADAS) là một phần quan trọng trong ô tô hiện đại, giúp tăng cường an toàn và tiện nghi cho người lái. Áp dụng các nguyên tắc Abstraction và Encapsulation trong thiết kế phần mềm ADAS mang lại nhiều lợi ích quan trọng về tính mô-đun, khả năng mở rộng và độ tin cậy.

## 1. Kiến trúc phần mềm ADAS

### Các thành phần chính
- **Hệ thống cảm biến (Sensor Systems)**
- **Xử lý hình ảnh (Image Processing)**
- **Phát hiện vật thể (Object Detection)**
- **Kiểm soát hành trình (Cruise Control)**
- **Hỗ trợ giữ làn đường (Lane Keeping)**
- **Cảnh báo va chạm (Collision Warning)**

### Mô hình lớp trừu tượng

```
        ┌───────────────┐
        │ADASController │
        │  (Abstract)   │
        └───────┬───────┘
                │
    ┌───────────┼───────────┐
    │           │           │
┌───▼───┐   ┌───▼────┐  ┌──▼───┐
│LaneKeep│   │Adaptive│  │Parking│
│Assist  │   │Cruise  │  │Assist │
└───────┘   └────────┘  └───────┘
```

## 2. Ứng dụng Abstraction

### Ví dụ: Hệ thống cảm biến trừu tượng

```cpp
// Lớp trừu tượng cho cảm biến
class Sensor {
public:
    // Phương thức thuần ảo
    virtual bool initialize() = 0;
    virtual bool selfTest() = 0;
    virtual void calibrate() = 0;
    virtual SensorData acquireData() = 0;
    virtual SensorStatus getStatus() const = 0;
    virtual void shutdown() = 0;
    
    // Destructor ảo
    virtual ~Sensor() {}
    
protected:
    // Các phương thức và thuộc tính chung
    SensorStatus status;
    
    void updateStatus(SensorStatus newStatus) {
        status = newStatus;
        notifyStatusChange();
    }
    
    virtual void notifyStatusChange() {
        // Thông báo sự thay đổi trạng thái
    }
};

// Lớp cụ thể: Camera
class Camera : public Sensor {
public:
    Camera(int resolution, double focalLength)
        : resolution(resolution), focalLength(focalLength) {}
    
    bool initialize() override {
        // Khởi tạo phần cứng camera
        if (initializeHardware()) {
            updateStatus(SensorStatus::Initialized);
            return true;
        }
        return false;
    }
    
    bool selfTest() override {
        // Kiểm tra chức năng
        if (testImageCapture()) {
            updateStatus(SensorStatus::Operational);
            return true;
        } else {
            updateStatus(SensorStatus::Error);
            return false;
        }
    }
    
    void calibrate() override {
        // Hiệu chuẩn camera
        adjustExposure();
        adjustFocus();
        updateStatus(SensorStatus::Calibrated);
    }
    
    SensorData acquireData() override {
        if (status != SensorStatus::Operational && 
            status != SensorStatus::Calibrated) {
            return SensorData(); // Dữ liệu rỗng
        }
        
        // Chụp ảnh từ camera
        Image rawImage = captureRawImage();
        
        // Xử lý ảnh
        Image processedImage = preprocessImage(rawImage);
        
        // Tạo đối tượng dữ liệu cảm biến
        SensorData data;
        data.timestamp = getCurrentTimestamp();
        data.type = SensorType::Camera;
        data.reliability = calculateReliability();
        data.rawData = serializeImage(processedImage);
        
        return data;
    }
    
    SensorStatus getStatus() const override {
        return status;
    }
    
    void shutdown() override {
        // Tắt camera an toàn
        powerDown();
        updateStatus(SensorStatus::PowerOff);
    }
    
    // Phương thức đặc thù cho camera
    void setResolution(int newResolution) {
        resolution = newResolution;
    }
    
    void setExposure(double exposureValue) {
        if (exposureValue >= 0.0 && exposureValue <= 1.0) {
            exposure = exposureValue;
            if (status == SensorStatus::Operational) {
                adjustExposure();
            }
        }
    }

private:
    int resolution; // độ phân giải theo megapixel
    double focalLength; // tiêu cự ống kính
    double exposure = 0.5; // giá trị phơi sáng (0.0 - 1.0)
    double focus = 1.0; // giá trị lấy nét (0.0 - 1.0)
    
    bool initializeHardware() {
        // Khởi tạo phần cứng camera
        return true;
    }
    
    bool testImageCapture() {
        // Thử chụp ảnh để kiểm tra chức năng
        return true;
    }
    
    void adjustExposure() {
        // Điều chỉnh độ phơi sáng
    }
    
    void adjustFocus() {
        // Điều chỉnh lấy nét tự động
    }
    
    Image captureRawImage() {
        // Chụp ảnh thô từ cảm biến
        Image img;
        // ...
        return img;
    }
    
    Image preprocessImage(const Image& rawImage) {
        // Xử lý sơ bộ ảnh (giảm nhiễu, cân bằng màu, v.v.)
        Image processed = rawImage;
        // ...
        return processed;
    }
    
    double calculateReliability() {
        // Tính toán độ tin cậy của dữ liệu dựa trên điều kiện
        double reliabilityScore = 1.0;
        
        // Kiểm tra điều kiện ánh sáng
        if (exposure < 0.2 || exposure > 0.8) {
            reliabilityScore *= 0.8; // Giảm độ tin cậy trong điều kiện ánh sáng kém
        }
        
        // Các yếu tố khác ảnh hưởng đến độ tin cậy
        // ...
        
        return reliabilityScore;
    }
    
    void powerDown() {
        // Tắt phần cứng camera
    }
    
    uint64_t getCurrentTimestamp() {
        // Lấy thời gian hiện tại theo microseconds
        return 0; // Placeholder
    }
    
    std::vector<uint8_t> serializeImage(const Image& image) {
        // Chuyển đổi ảnh thành dữ liệu nhị phân
        std::vector<uint8_t> data;
        // ...
        return data;
    }
};

// Lớp cụ thể: Radar
class Radar : public Sensor {
public:
    Radar(double range, double angularResolution) 
        : range(range), angularResolution(angularResolution) {}
    
    bool initialize() override {
        // Khởi tạo phần cứng radar
        if (initializeHardware()) {
            updateStatus(SensorStatus::Initialized);
            return true;
        }
        return false;
    }
    
    bool selfTest() override {
        // Kiểm tra chức năng radar
        if (testRadarEmission() && testSignalProcessing()) {
            updateStatus(SensorStatus::Operational);
            return true;
        } else {
            updateStatus(SensorStatus::Error);
            return false;
        }
    }
    
    void calibrate() override {
        // Hiệu chuẩn radar
        adjustFrequency();
        updateStatus(SensorStatus::Calibrated);
    }
    
    SensorData acquireData() override {
        if (status != SensorStatus::Operational && 
            status != SensorStatus::Calibrated) {
            return SensorData(); // Dữ liệu rỗng
        }
        
        // Thu tín hiệu radar
        RadarSignal rawSignal = emitAndReceive();
        
        // Xử lý tín hiệu
        RadarData processedData = processRadarSignal(rawSignal);
        
        // Tạo đối tượng dữ liệu cảm biến
        SensorData data;
        data.timestamp = getCurrentTimestamp();
        data.type = SensorType::Radar;
        data.reliability = calculateReliability();
        data.rawData = serializeRadarData(processedData);
        
        return data;
    }
    
    SensorStatus getStatus() const override {
        return status;
    }
    
    void shutdown() override {
        // Tắt radar an toàn
        stopEmission();
        powerDown();
        updateStatus(SensorStatus::PowerOff);
    }
    
    // Phương thức đặc thù cho radar
    void setRange(double newRange) {
        if (newRange > 0) {
            range = newRange;
        }
    }

private:
    double range; // Phạm vi phát hiện (mét)
    double angularResolution; // Độ phân giải góc (độ)
    double frequency = 77.0; // GHz
    
    // Các phương thức private tương tự như Camera
    // ...
};
```

### Lợi ích của Abstraction trong ADAS
1. **Khả năng thay thế cảm biến**: Hệ thống có thể hoạt động với nhiều loại cảm biến khác nhau
2. **Mở rộng dễ dàng**: Dễ dàng thêm các loại cảm biến mới (LiDAR, siêu âm...)
3. **Đơn giản hóa phát triển**: Lớp trừu tượng cho phép các đội phát triển làm việc độc lập

## 3. Ứng dụng Encapsulation

### Ví dụ: Bộ phát hiện vật thể

```cpp
class ObjectDetector {
private:
    // Dữ liệu được bảo vệ
    std::vector<SensorData> sensorInputs;
    std::vector<DetectedObject> detectedObjects;
    DetectionAlgorithm algorithm;
    double confidenceThreshold;
    bool isInitialized;
    
    // Thuật toán nội bộ
    std::vector<DetectedObject> detectObjectsFromCamera(const SensorData& cameraData) {
        std::vector<DetectedObject> objects;
        
        // Giải nén dữ liệu hình ảnh
        Image image = deserializeImage(cameraData.rawData);
        
        // Áp dụng thuật toán phát hiện đối tượng (như YOLO, SSD, v.v.)
        if (algorithm == DetectionAlgorithm::YOLO) {
            objects = applyYOLO(image);
        } 
        else if (algorithm == DetectionAlgorithm::SSD) {
            objects = applySSD(image);
        }
        
        // Lọc các đối tượng dựa trên ngưỡng tin cậy
        std::vector<DetectedObject> filteredObjects;
        for (const auto& obj : objects) {
            if (obj.confidence >= confidenceThreshold) {
                filteredObjects.push_back(obj);
            }
        }
        
        return filteredObjects;
    }
    
    std::vector<DetectedObject> detectObjectsFromRadar(const SensorData& radarData) {
        std::vector<DetectedObject> objects;
        
        // Giải nén dữ liệu radar
        RadarData radar = deserializeRadarData(radarData.rawData);
        
        // Phát hiện đối tượng từ dữ liệu radar
        for (const auto& point : radar.reflectionPoints) {
            if (point.signalStrength > radarSignalThreshold) {
                DetectedObject obj;
                obj.id = generateUniqueId();
                obj.type = ObjectType::Unknown; // Radar không phân loại được đối tượng
                obj.position = point.position;
                obj.velocity = point.velocity;
                obj.size = estimateObjectSize(point);
                obj.confidence = calculateConfidence(point);
                
                objects.push_back(obj);
            }
        }
        
        return objects;
    }
    
    std::vector<DetectedObject> fuseSensorData() {
        // Hợp nhất các đối tượng được phát hiện từ nhiều cảm biến
        // Thuật toán hợp nhất phức tạp (data fusion)
        
        std::map<int, DetectedObject> objectMap;
        
        // Xử lý dữ liệu từ từng cảm biến
        for (const auto& sensorData : sensorInputs) {
            std::vector<DetectedObject> sensorObjects;
            
            if (sensorData.type == SensorType::Camera) {
                sensorObjects = detectObjectsFromCamera(sensorData);
            } 
            else if (sensorData.type == SensorType::Radar) {
                sensorObjects = detectObjectsFromRadar(sensorData);
            }
            else if (sensorData.type == SensorType::Lidar) {
                sensorObjects = detectObjectsFromLidar(sensorData);
            }
            
            // Gộp đối tượng vào bản đồ chung
            for (const auto& obj : sensorObjects) {
                // Kiểm tra xem đối tượng đã được phát hiện chưa
                auto existingObject = findMatchingObject(obj, objectMap);
                
                if (existingObject != objectMap.end()) {
                    // Cập nhật đối tượng hiện có với thông tin mới
                    updateExistingObject(existingObject->second, obj, sensorData.reliability);
                } else {
                    // Thêm đối tượng mới
                    objectMap[obj.id] = obj;
                }
            }
        }
        
        // Chuyển đổi từ bản đồ sang vector
        std::vector<DetectedObject> mergedObjects;
        for (const auto& pair : objectMap) {
            mergedObjects.push_back(pair.second);
        }
        
        return mergedObjects;
    }
    
    // Các phương thức trợ giúp
    auto findMatchingObject(const DetectedObject& obj, 
                           std::map<int, DetectedObject>& objectMap) {
        // Tìm đối tượng phù hợp dựa trên vị trí và kích thước
        for (auto it = objectMap.begin(); it != objectMap.end(); ++it) {
            if (isLikelySameObject(it->second, obj)) {
                return it;
            }
        }
        return objectMap.end();
    }
    
    bool isLikelySameObject(const DetectedObject& obj1, const DetectedObject& obj2) {
        // Kiểm tra xem hai phát hiện có thể là cùng một đối tượng
        double distanceThreshold = 2.0; // mét
        
        double distance = calculateDistance(obj1.position, obj2.position);
        return distance < distanceThreshold;
    }
    
    void updateExistingObject(DetectedObject& existing, 
                             const DetectedObject& newObj, 
                             double sensorReliability) {
        // Cập nhật đối tượng hiện có với dữ liệu mới
        // Sử dụng phương pháp kết hợp có trọng số
        double totalWeight = existing.confidence + sensorReliability;
        
        // Cập nhật vị trí
        existing.position.x = (existing.position.x * existing.confidence + 
                              newObj.position.x * sensorReliability) / totalWeight;
        existing.position.y = (existing.position.y * existing.confidence + 
                              newObj.position.y * sensorReliability) / totalWeight;
        existing.position.z = (existing.position.z * existing.confidence + 
                              newObj.position.z * sensorReliability) / totalWeight;
        
        // Cập nhật kích thước nếu newObj là từ camera
        if (newObj.type != ObjectType::Unknown) {
            existing.type = newObj.type;
        }
        
        // Cập nhật vận tốc nếu newObj là từ radar
        if (newObj.velocity.magnitude() > 0) {
            existing.velocity = newObj.velocity;
        }
        
        // Tăng độ tin cậy, nhưng giới hạn tối đa
        existing.confidence = std::min(1.0, existing.confidence + 0.1 * sensorReliability);
    }

public:
    // Constructor
    ObjectDetector()
        : confidenceThreshold(0.7), 
          algorithm(DetectionAlgorithm::YOLO),
          isInitialized(false) {}
    
    // Khởi tạo bộ dò
    bool initialize() {
        // Khởi tạo các tài nguyên cần thiết
        loadDetectionModels();
        isInitialized = true;
        return true;
    }
    
    // Đặt thuật toán phát hiện
    void setAlgorithm(DetectionAlgorithm algo) {
        algorithm = algo;
    }
    
    // Đặt ngưỡng tin cậy
    void setConfidenceThreshold(double threshold) {
        if (threshold >= 0.0 && threshold <= 1.0) {
            confidenceThreshold = threshold;
        }
    }
    
    // Thêm dữ liệu cảm biến đầu vào
    void addSensorData(const SensorData& data) {
        if (!isInitialized) {
            throw std::runtime_error("ObjectDetector not initialized");
        }
        
        // Thêm dữ liệu mới
        sensorInputs.push_back(data);
        
        // Xóa dữ liệu cũ nếu có quá nhiều
        if (sensorInputs.size() > maxSensorInputs) {
            sensorInputs.erase(sensorInputs.begin());
        }
    }
    
    // Thực hiện phát hiện
    void detect() {
        if (!isInitialized || sensorInputs.empty()) {
            return;
        }
        
        // Thực hiện fusion và phát hiện
        detectedObjects = fuseSensorData();
        
        // Theo dõi đối tượng qua thời gian
        trackObjects();
    }
    
    // Lấy các đối tượng được phát hiện
    std::vector<DetectedObject> getDetectedObjects() const {
        return detectedObjects;
    }
    
    // Lấy các đối tượng có khả năng gây va chạm
    std::vector<DetectedObject> getPotentialCollisions(
        const Vehicle& vehicle, double timeThreshold = 5.0) {
        
        std::vector<DetectedObject> potentialCollisions;
        
        for (const auto& obj : detectedObjects) {
            // Tính toán thời gian đến va chạm (TTC - Time-To-Collision)
            double ttc = calculateTimeToCollision(vehicle, obj);
            
            // Nếu TTC dưới ngưỡng, đánh dấu là va chạm tiềm năng
            if (ttc >= 0 && ttc < timeThreshold) {
                potentialCollisions.push_back(obj);
            }
        }
        
        return potentialCollisions;
    }

private:
    const size_t maxSensorInputs = 10; // Số lượng tối đa dữ liệu cảm biến lưu trữ
    const double radarSignalThreshold = 0.3; // Ngưỡng tín hiệu radar
    
    void loadDetectionModels() {
        // Tải các mô hình ML cho phát hiện đối tượng
    }
    
    void trackObjects() {
        // Theo dõi đối tượng qua thời gian (object tracking)
    }
    
    double calculateTimeToCollision(const Vehicle& vehicle, const DetectedObject& object) {
        // Tính toán thời gian đến va chạm
        // TTC = relative_distance / relative_velocity
        
        // Tính khoảng cách tương đối
        double distance = calculateDistance(vehicle.getPosition(), object.position);
        
        // Tính vận tốc tương đối theo hướng của khoảng cách
        Vector3D relativeVelocity = object.velocity - vehicle.getVelocity();
        
        // Chiếu vận tốc tương đối lên vector khoảng cách
        Vector3D directionToObject = normalizeVector(
            subtractVectors(object.position, vehicle.getPosition())
        );
        
        double velocityTowardsObject = dotProduct(relativeVelocity, directionToObject);
        
        // Nếu không di chuyển lại gần nhau, không có nguy cơ va chạm
        if (velocityTowardsObject <= 0) {
            return -1;
        }
        
        // TTC = distance / velocity
        return distance / velocityTowardsObject;
    }
    
    // Các phương thức trợ giúp toán học vector
    double calculateDistance(const Point3D& p1, const Point3D& p2) {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        double dz = p2.z - p1.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }
    
    Vector3D subtractVectors(const Point3D& p1, const Point3D& p2) {
        return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
    }
    
    Vector3D normalizeVector(const Vector3D& v) {
        double mag = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        if (mag > 0) {
            return {v.x / mag, v.y / mag, v.z / mag};
        }
        return v;
    }
    
    double dotProduct(const Vector3D& v1, const Vector3D& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
};
```

### Lợi ích của Encapsulation trong ADAS
1. **An toàn dữ liệu**: Bảo vệ các thuật toán phức tạp và dữ liệu quan trọng
2. **Quản lý độ phức tạp**: Ẩn đi logic phức tạp về xử lý dữ liệu từ nhiều cảm biến
3. **Tính nhất quán**: Đảm bảo dữ liệu và trạng thái luôn ở trạng thái hợp lệ
4. **Dễ dàng bảo trì**: Các phương thức công khai đơn giản che giấu triển khai phức tạp

## 4. Thiết kế hệ thống ADAS tích hợp

### Ví dụ: Adaptive Cruise Control

```cpp
// Lớp trừu tượng cho hệ thống ADAS
class ADASSystem {
public:
    virtual void initialize() = 0;
    virtual void update(const VehicleState& state) = 0;
    virtual bool isActive() const = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual SystemStatus getStatus() const = 0;
    virtual std::string getSystemName() const = 0;
    virtual ~ADASSystem() {}
    
protected:
    SystemStatus status = SystemStatus::Inactive;
};

// Triển khai cụ thể: Hệ thống điều khiển hành trình thích ứng
class AdaptiveCruiseControl : public ADASSystem {
private:
    // Các thành phần được đóng gói
    VehicleController* vehicleController;
    ObjectDetector* objectDetector;
    
    // Cài đặt và trạng thái
    double targetSpeed; // km/h
    double minFollowingDistance; // mét
    double maxFollowingDistance; // mét
    double timeGap; // giây
    bool isActiveState;
    
    // Trạng thái hiện tại
    VehicleState currentState;
    DetectedObject* leadVehicle; // Xe phía trước
    
    // Tính toán khoảng cách an toàn dựa trên vận tốc và timeGap
    double calculateSafeDistance() const {
        // Khoảng cách an toàn = vận tốc * thời gian + khoảng cách tối thiểu
        double distance = (currentState.speed / 3.6) * timeGap + minFollowingDistance;
        
        // Đảm bảo không vượt quá khoảng cách tối đa
        return std::min(distance, maxFollowingDistance);
    }
    
    // Tìm xe dẫn đường phía trước trong làn đường
    DetectedObject* findLeadVehicle() {
        std::vector<DetectedObject> objects = objectDetector->getDetectedObjects();
        
        DetectedObject* closest = nullptr;
        double minDistance = std::numeric_limits<double>::max();
        
        for (auto& obj : objects) {
            // Chỉ xét các đối tượng phía trước và trong làn đường
            if (isInSameLane(obj) && isAhead(obj)) {
                double distance = calculateLongitudinalDistance(obj);
                if (distance < minDistance) {
                    minDistance = distance;
                    closest = &obj;
                }
            }
        }
        
        return closest;
    }
    
    // Kiểm tra xem đối tượng có ở cùng làn đường không
    bool isInSameLane(const DetectedObject& obj) const {
        // Kiểm tra vị trí ngang của đối tượng so với xe
        double lateralDistance = std::abs(obj.position.y - currentState.position.y);
        return lateralDistance < laneWidth / 2.0;
    }
    
    // Kiểm tra xem đối tượng có phía trước không
    bool isAhead(const DetectedObject& obj) const {
        // Trong hệ tọa độ xe, trục x hướng về phía trước
        double longitudinalDistance = obj.position.x - currentState.position.x;
        return longitudinalDistance > 0;
    }
    
    // Tính khoảng cách dọc đến đối tượng
    double calculateLongitudinalDistance(const DetectedObject& obj) const {
        return obj.position.x - currentState.position.x;
    }
    
    // Tính toán vận tốc mục tiêu dựa trên xe phía trước
    double calculateTargetSpeed() {
        // Nếu không có xe phía trước, sử dụng vận tốc được cài đặt
        if (leadVehicle == nullptr) {
            return targetSpeed;
        }
        
        // Tính khoảng cách hiện tại đến xe phía trước
        double currentDistance = calculateLongitudinalDistance(*leadVehicle);
        
        // Tính khoảng cách an toàn mong muốn
        double safeDistance = calculateSafeDistance();
        
        // Vận tốc của xe phía trước (chuyển từ m/s sang km/h)
        double leadSpeed = leadVehicle->velocity.x * 3.6;
        
        // Nếu quá gần, giảm tốc độ
        if (currentDistance < safeDistance) {
            // Tỷ lệ khoảng cách
            double distanceRatio = currentDistance / safeDistance;
            
            // Điều chỉnh vận tốc để giữ khoảng cách an toàn
            // Càng gần, giảm tốc càng nhiều
            return std::min(targetSpeed, leadSpeed * distanceRatio);
        }
        // Nếu quá xa, tăng tốc nhưng không vượt quá vận tốc mục tiêu
        else if (currentDistance > safeDistance * 1.2) {
            return std::min(targetSpeed, leadSpeed + 5.0);
        }
        // Nếu ở khoảng cách phù hợp, giữ vận tốc của xe phía trước
        else {
            return leadSpeed;
        }
    }

public:
    // Constructor
    AdaptiveCruiseControl(VehicleController* vc, ObjectDetector* od)
        : vehicleController(vc), objectDetector(od),
          targetSpeed(0), minFollowingDistance(2.0),
          maxFollowingDistance(50.0), timeGap(1.5),
          isActiveState(false), leadVehicle(nullptr) {}
    
    void initialize() override {
        status = SystemStatus::Initialized;
    }
    
    void update(const VehicleState& state) override {
        // Cập nhật trạng thái hiện tại
        currentState = state;
        
        if (!isActiveState) {
            return;
        }
        
        // Tìm xe phía trước
        leadVehicle = findLeadVehicle();
        
        // Tính toán vận tốc mục tiêu
        double calculatedSpeed = calculateTargetSpeed();
        
        // Điều chỉnh vận tốc xe
        vehicleController->setTargetSpeed(calculatedSpeed);
        
        // Cập nhật trạng thái
        status = SystemStatus::Active;
    }
    
    bool isActive() const override {
        return isActiveState;
    }
    
    void activate() override {
        if (status == SystemStatus::Initialized || 
            status == SystemStatus::Inactive) {
            isActiveState = true;
            status = SystemStatus::Active;
            
            // Lưu vận tốc hiện tại làm vận tốc mục tiêu
            targetSpeed = currentState.speed;
            
            // Thông báo người dùng
            notifyUserActivation();
        }
    }
    
    void deactivate() override {
        if (isActiveState) {
            isActiveState = false;
            status = SystemStatus::Inactive;
            
            // Trả quyền điều khiển cho người lái
            vehicleController->disengageAutomaticControl();
            
            // Thông báo người dùng
            notifyUserDeactivation();
        }
    }
    
    SystemStatus getStatus() const override {
        return status;
    }
    
    std::string getSystemName() const override {
        return "Adaptive Cruise Control";
    }
    
    // Các phương thức đặc thù cho ACC
    void setTargetSpeed(double speed) {
        if (speed >= 30.0 && speed <= 180.0) {  // Giới hạn hợp lý
            targetSpeed = speed;
        }
    }
    
    void increaseTargetSpeed(double increment = 5.0) {
        targetSpeed = std::min(180.0, targetSpeed + increment);
    }
    
    void decreaseTargetSpeed(double decrement = 5.0) {
        targetSpeed = std::max(30.0, targetSpeed - decrement);
    }
    
    void setTimeGap(double seconds) {
        if (seconds >= 1.0 && seconds <= 3.0) {
            timeGap = seconds;
        }
    }
    
    // Getters
    double getTargetSpeed() const { return targetSpeed; }
    double getTimeGap() const { return timeGap; }
    double getDistanceToLeadVehicle() const {
        if (leadVehicle) {
            return calculateLongitudinalDistance(*leadVehicle);
        }
        return -1.0; // Không có xe phía trước
    }

private:
    const double laneWidth = 3.5; // Chiều rộng làn đường tiêu chuẩn (mét)
    
    void notifyUserActivation() {
        // Thông báo cho người dùng về việc kích hoạt ACC
    }
    
    void notifyUserDeactivation() {
        // Thông báo cho người dùng về việc tắt ACC
    }
};
```

## 5. Case Study: Hệ thống phát hiện điểm mù (Blind Spot Detection)

Một ví dụ khác về hệ thống ADAS đơn giản nhưng quan trọng:

```cpp
class BlindSpotDetection : public ADASSystem {
private:
    // Các thành phần được đóng gói
    std::vector<Sensor*> sideSensors;  // Cảm biến hai bên xe
    VehicleController* vehicleController;
    HMIController* hmiController;  // Giao diện người dùng
    
    // Cài đặt và trạng thái
    bool leftBlindSpotOccupied;
    bool rightBlindSpotOccupied;
    bool isActiveState;
    bool warningEnabled;  // Cho phép cảnh báo
    
    // Thông số xe
    double vehicleWidth;
    double vehicleLength;
    
    // Xác định vùng điểm mù
    bool isInLeftBlindSpot(const DetectedObject& object) const {
        // Vùng điểm mù bên trái là khu vực ở bên trái xe,
        // phía sau gương chiếu hậu và bên cạnh/phía sau xe
        
        // Lấy vị trí tương đối so với xe
        double relX = object.position.x - currentState.position.x;
        double relY = object.position.y - currentState.position.y;
        
        // Chuyển đổi sang tọa độ xe (xe hướng về trục x dương)
        double cosYaw = std::cos(currentState.yaw);
        double sinYaw = std::sin(currentState.yaw);
        
        double xVehicle = relX * cosYaw + relY * sinYaw;
        double yVehicle = -relX * sinYaw + relY * cosYaw;
        
        // Kiểm tra xem đối tượng có nằm trong vùng điểm mù bên trái không
        bool isOnLeftSide = yVehicle < -vehicleWidth/2 && 
                           yVehicle > -(vehicleWidth/2 + blindSpotWidth);
        
        bool isInLongitudinalRange = xVehicle > -vehicleLength/2 && 
                                    xVehicle < vehicleLength;
        
        return isOnLeftSide && isInLongitudinalRange;
    }
    
    bool isInRightBlindSpot(const DetectedObject& object) const {
        // Tương tự như isInLeftBlindSpot nhưng cho bên phải
        double relX = object.position.x - currentState.position.x;
        double relY = object.position.y - currentState.position.y;
        
        double cosYaw = std::cos(currentState.yaw);
        double sinYaw = std::sin(currentState.yaw);
        
        double xVehicle = relX * cosYaw + relY * sinYaw;
        double yVehicle = -relX * sinYaw + relY * cosYaw;
        
        bool isOnRightSide = yVehicle > vehicleWidth/2 && 
                            yVehicle < (vehicleWidth/2 + blindSpotWidth);
        
        bool isInLongitudinalRange = xVehicle > -vehicleLength/2 && 
                                    xVehicle < vehicleLength;
        
        return isOnRightSide && isInLongitudinalRange;
    }

public:
    // Constructor
    BlindSpotDetection(std::vector<Sensor*> sensors, 
                      VehicleController* vc, 
                      HMIController* hmi,
                      double width, 
                      double length)
        : sideSensors(sensors), vehicleController(vc), hmiController(hmi),
          leftBlindSpotOccupied(false), rightBlindSpotOccupied(false),
          isActiveState(false), warningEnabled(true),
          vehicleWidth(width), vehicleLength(length) {}
    
    void initialize() override {
        // Khởi tạo cảm biến
        for (auto sensor : sideSensors) {
            sensor->initialize();
        }
        
        status = SystemStatus::Initialized;
    }
    
    void update(const VehicleState& state) override {
        currentState = state;
        
        if (!isActiveState) {
            return;
        }
        
        // Thu thập dữ liệu từ cảm biến
        std::vector<DetectedObject> detectedObjects;
        for (auto sensor : sideSensors) {
            SensorData data = sensor->acquireData();
            
            // Xử lý dữ liệu cảm biến và phát hiện đối tượng
            std::vector<DetectedObject> objects = processData(data);
            
            // Thêm vào danh sách đối tượng được phát hiện
            detectedObjects.insert(detectedObjects.end(), objects.begin(), objects.end());
        }
        
        // Kiểm tra điểm mù
        bool prevLeftOccupied = leftBlindSpotOccupied;
        bool prevRightOccupied = rightBlindSpotOccupied;
        
        leftBlindSpotOccupied = false;
        rightBlindSpotOccupied = false;
        
        // Kiểm tra từng đối tượng
        for (const auto& object : detectedObjects) {
            if (isInLeftBlindSpot(object)) {
                leftBlindSpotOccupied = true;
            }
            
            if (isInRightBlindSpot(object)) {
                rightBlindSpotOccupied = true;
            }
        }
        
        // Kiểm tra cần đưa ra cảnh báo không
        bool shouldWarnLeft = leftBlindSpotOccupied && state.leftTurnSignal;
        bool shouldWarnRight = rightBlindSpotOccupied && state.rightTurnSignal;
        
        // Cập nhật đèn chỉ báo trên gương
        hmiController->setLeftMirrorIndicator(leftBlindSpotOccupied);
        hmiController->setRightMirrorIndicator(rightBlindSpotOccupied);
        
        // Phát âm thanh cảnh báo nếu cần
        if (warningEnabled && (shouldWarnLeft || shouldWarnRight)) {
            hmiController->playWarningSound(WarningSound::BlindSpotAlert);
        }
        
        // Phát hiện mới - có thể cung cấp phản hồi bổ sung
        if (!prevLeftOccupied && leftBlindSpotOccupied) {
            // Đối tượng mới xuất hiện ở điểm mù bên trái
        }
        
        if (!prevRightOccupied && rightBlindSpotOccupied) {
            // Đối tượng mới xuất hiện ở điểm mù bên phải
        }
        
        status = SystemStatus::Active;
    }
    
    bool isActive() const override {
        return isActiveState;
    }
    
    void activate() override {
        if (status == SystemStatus::Initialized || 
            status == SystemStatus::Inactive) {
            isActiveState = true;
            status = SystemStatus::Active;
        }
    }
    
    void deactivate() override {
        if (isActiveState) {
            isActiveState = false;
            status = SystemStatus::Inactive;
            
            // Tắt đèn chỉ báo
            hmiController->setLeftMirrorIndicator(false);
            hmiController->setRightMirrorIndicator(false);
        }
    }
    
    SystemStatus getStatus() const override {
        return status;
    }
    
    std::string getSystemName() const override {
        return "Blind Spot Detection";
    }
    
    // Các phương thức đặc thù cho BSD
    void enableWarning(bool enable) {
        warningEnabled = enable;
    }
    
    bool isWarningEnabled() const {
        return warningEnabled;
    }
    
    bool isLeftBlindSpotOccupied() const {
        return leftBlindSpotOccupied;
    }
    
    bool isRightBlindSpotOccupied() const {
        return rightBlindSpotOccupied;
    }

private:
    const double blindSpotWidth = 3.0; // Chiều rộng vùng điểm mù (mét)
    VehicleState currentState; // Trạng thái hiện tại của xe
    
    std::vector<DetectedObject> processData(const SensorData& data) {
        // Xử lý dữ liệu từ cảm biến để phát hiện các đối tượng
        // (Đây là phương thức giả định, trong thực tế sẽ phức tạp hơn)
        std::vector<DetectedObject> objects;
        
        // ... xử lý dữ liệu ...
        
        return objects;
    }
};
```

## 6. Kết luận

Việc áp dụng Abstraction và Encapsulation trong phát triển phần mềm ADAS mang lại nhiều lợi ích quan trọng:

1. **An toàn cao hơn**: Encapsulation đảm bảo dữ liệu và thuật toán quan trọng được bảo vệ
2. **Kiểm thử dễ dàng**: Các thành phần có thể được kiểm thử độc lập
3. **Khả năng mở rộng**: Dễ dàng thêm các tính năng ADAS mới thông qua abstraction
4. **Tái sử dụng mã nguồn**: Các thành phần như cảm biến, thuật toán phát hiện có thể dùng lại
5. **Quản lý phức tạp**: Hệ thống phức tạp được phân tách thành các thành phần nhỏ hơn, dễ quản lý

Trong thực tế, các hệ thống ADAS hiện đại sử dụng các nguyên tắc này để đảm bảo tính tin cậy, an toàn và khả năng mở rộng cao, đồng thời giảm thiểu lỗi tiềm ẩn có thể gây ra các vấn đề an toàn nghiêm trọng.
