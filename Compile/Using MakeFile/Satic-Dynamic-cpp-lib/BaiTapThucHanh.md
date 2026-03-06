# Bài tập thực hành: Thư viện tĩnh và động trong C/C++

## Mục tiêu
- Hiểu cách xây dựng và sử dụng thư viện tĩnh và động trong C/C++
- Thực hành sử dụng Makefile để tự động hóa quá trình biên dịch
- Hiểu sự khác biệt giữa thư viện tĩnh và động qua thực hành

## Yêu cầu chung
- Mỗi bài tập, sinh viên cần tạo cả thư viện tĩnh và thư viện động
- Sử dụng Makefile để tự động hóa quá trình biên dịch
- Viết chương trình test để kiểm tra chức năng của thư viện
- Nộp báo cáo mô tả quá trình làm việc và kết quả đạt được

## Bài tập 1: Thư viện tính toán đơn giản
### Yêu cầu
1. Tạo thư viện `mathlib` với các hàm sau:
   - `int add(int a, int b)`: Tính tổng hai số nguyên
   - `int subtract(int a, int b)`: Tính hiệu hai số nguyên
   - `int multiply(int a, int b)`: Tính tích hai số nguyên
   - `float divide(int a, int b)`: Tính thương hai số nguyên
   - `double power(double base, int exponent)`: Tính lũy thừa
   - `double square_root(double x)`: Tính căn bậc hai

2. Viết chương trình test sử dụng thư viện tĩnh và động để thực hiện các tính toán và hiển thị kết quả.

### Gợi ý
- Sử dụng hàm `pow()` và `sqrt()` từ thư viện `math.h` cho hàm `power()` và `square_root()`
- Nhớ thêm `-lm` khi biên dịch để liên kết với thư viện math

## Bài tập 2: Thư viện xử lý chuỗi
### Yêu cầu
1. Tạo thư viện `strlib` với các hàm sau:
   - `char* str_reverse(const char* str)`: Đảo ngược chuỗi
   - `char* str_to_upper(const char* str)`: Chuyển chuỗi thành chữ hoa
   - `char* str_to_lower(const char* str)`: Chuyển chuỗi thành chữ thường
   - `int str_count(const char* str, char c)`: Đếm số lần xuất hiện của ký tự c trong chuỗi
   - `char* str_trim(const char* str)`: Loại bỏ khoảng trắng ở đầu và cuối chuỗi

2. Viết chương trình test sử dụng thư viện để xử lý các chuỗi nhập từ người dùng.

### Gợi ý
- Các hàm trả về chuỗi mới cần cấp phát động bộ nhớ, nhớ giải phóng bộ nhớ sau khi sử dụng
- Sử dụng các hàm trong `ctype.h` để xử lý các ký tự

## Bài tập 3: Thư viện xử lý mảng
### Yêu cầu
1. Tạo thư viện `arraylib` với các hàm sau:
   - `void sort_array(int arr[], int size, int ascending)`: Sắp xếp mảng
   - `int find_element(int arr[], int size, int element)`: Tìm phần tử trong mảng, trả về vị trí hoặc -1
   - `float average(int arr[], int size)`: Tính giá trị trung bình của mảng
   - `int max_element(int arr[], int size)`: Tìm giá trị lớn nhất
   - `int min_element(int arr[], int size)`: Tìm giá trị nhỏ nhất
   - `void filter_even(int arr[], int size, int result[], int* result_size)`: Lọc các số chẵn

2. Viết chương trình test cho phép người dùng tạo mảng và thực hiện các thao tác trên mảng.

### Gợi ý
- Sử dụng thuật toán sắp xếp đơn giản như bubble sort hoặc insertion sort
- Cần kiểm tra các trường hợp đặc biệt như mảng rỗng

## Bài tập 4: Thư viện xử lý tập tin
### Yêu cầu
1. Tạo thư viện `filelib` với các hàm sau:
   - `int count_lines(const char* filename)`: Đếm số dòng trong tập tin
   - `int count_words(const char* filename)`: Đếm số từ trong tập tin
   - `int search_string(const char* filename, const char* str)`: Tìm kiếm chuỗi, trả về số lần xuất hiện
   - `int copy_file(const char* source, const char* destination)`: Sao chép tập tin
   - `int merge_files(const char* file1, const char* file2, const char* destination)`: Gộp hai tập tin

2. Viết chương trình test sử dụng thư viện để xử lý các tập tin văn bản.

### Gợi ý
- Sử dụng các hàm xử lý tập tin trong `stdio.h`
- Kiểm tra các trường hợp lỗi khi mở tập tin

## Bài tập 5 (nâng cao): Thư viện đồ họa đơn giản
### Yêu cầu
1. Tạo thư viện `graphlib` với các hàm vẽ đơn giản trên console:
   - `void clear_screen()`: Xóa màn hình console
   - `void draw_line(int x1, int y1, int x2, int y2, char c)`: Vẽ đường thẳng
   - `void draw_rectangle(int x, int y, int width, int height, char c)`: Vẽ hình chữ nhật
   - `void draw_circle(int x, int y, int radius, char c)`: Vẽ hình tròn
   - `void set_color(int color)`: Đặt màu cho văn bản (sử dụng ANSI escape code)

2. Viết chương trình demo vẽ một hình đơn giản trên console.

### Gợi ý
- Sử dụng thuật toán Bresenham để vẽ đường thẳng và hình tròn
- Sử dụng ANSI escape sequence để điều khiển vị trí con trỏ và màu sắc

## Tiêu chí đánh giá
1. **Cấu trúc và tổ chức (30%):**
   - Tổ chức thư mục hợp lý
   - Chia tách header và implementation
   - Makefile hoạt động chính xác

2. **Chức năng (40%):**
   - Thư viện tĩnh và động hoạt động chính xác
   - Tất cả các hàm được cài đặt theo yêu cầu
   - Xử lý lỗi và trường hợp đặc biệt

3. **Chương trình test (20%):**
   - Kiểm tra đầy đủ các chức năng của thư viện
   - Giao diện người dùng dễ sử dụng
   - Hiển thị kết quả rõ ràng

4. **Báo cáo (10%):**
   - Mô tả quá trình làm việc
   - Giải thích các quyết định thiết kế
   - Hướng dẫn sử dụng rõ ràng

## Thời gian thực hiện
- 2 tuần

## Hình thức nộp bài
- Nộp mã nguồn qua hệ thống quản lý mã nguồn (GitHub, GitLab)
- Nộp báo cáo dưới dạng PDF

## Lưu ý
- Sinh viên có thể chọn làm một trong các bài tập trên hoặc làm tất cả
- Khuyến khích thêm các chức năng mở rộng vào thư viện
- Chú ý xử lý các trường hợp đặc biệt và lỗi có thể xảy ra
