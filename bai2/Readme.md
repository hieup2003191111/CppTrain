1.
khi biến khai báo trong hàm .
hàm kết thúc thì biến sẽ không còn được cấp vùng nhớ,tuy nhiên giá trị sẽ bị giữ lại làm giá trị rác.
Khi đó,khai báo 1 biến nhưng chưa khởi tạo sẽ bị dính vào giá trị rác đó.

2.
khi khai báo 1 biến trong hàm giống tên biến toàn cục gây ra hiện tượng che khuất biến.
khi gọi hàm sẽ chỉ thay đổi biến tạm trong hàm,không tác động đến biến toàn cục bên ngoài
cách sửa:không khai báo mới,chỉ gán giá trị

3.
  vd:   const volatile int * const  i = &hardware_variable;
const 1: cố định giá trị của vùng nhớ mà con trỏ lưu giữ

volatile : tránh biên dịch tối ưu hoá code,bắt buộc đọc từ bộ nhớ(không đọc từ thanh ghi như thông thường)

const 2: không cho phép trỏ đi chỗ khác