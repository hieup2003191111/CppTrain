1.
a,
-Static library:
kích thước file lớn hơn vì copy toàn bộ mã nguồn thư viện vào file thực thi
-Dynamic library:
kích thước file nhỏ hơn vì chỉ chứa lời nhắc gọi đến thư viện bên ngoài.
b,
Trong ô tô,ưu tiên dùng static library vì :
-đảm bảo tính ổn định,không lo bị thiếu thư viện khi chạy.
-phù hợp yêu cầu tốc độ cao,tiết kiệm thời gian
Khi nào dùng dynamic:
-khi cần update lại 1 chức năng,phần mềm mà không cần tải lại toàn bộ firmware
2.
lệnh biên dịch g++
có 2 file main.cpp và thư viện flac
static : g++ main.cpp libflac.a -o music_app_static
dynamic: g++ main.cpp -L. -lflac -o music_app_dynamic
3.
DLL Hell:
khi 2 ứng dung A và B cùng dùng chung 1 file thư viện .so.
Ứng dụng A cập nhật phiên bản mới của thư viện ,nhưng B không tương thích và lập tức bị lỗi.