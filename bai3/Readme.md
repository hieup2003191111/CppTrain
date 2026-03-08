1.
khi gọi đệ quy không điểm dừng,sẽ bị tràn bộ nhớ stack(stack overflow)
2.
 char imageBuffer[5 * 1024 * 1024];  
//khai báo như trên sẽ tốn 5MB ở stack,gây crash hệ thống vì stack ít dung lượng
 
 std::vector<char> imageBuffer(5* 1024 *1024);
 //khai báo ở heap sẽ chạy được

3.
Với dữ liệu dùng chung nhiều nơi,yêu cầu không chỉnh sửa được và an toàn,để nó ở vùng text segment
4.

khi khai báo biến global không khởi tạo giá trị,biến sẽ nằm ở bss segment và được gán giá trị 0 khi hoạt động.
Đối với mảng struct ở bss,sẽ không gán giá trị 0 toàn bộ ngay vào file thực thi nên không làm tăng kích thước file thực thi.Khi khởi tạo giá trị thì buộc phải ghi toàn bộ giá trị vào file thực thi.

Quy đổi :
1 kb = 2^10 Byte = 1024 byte
1 mb = 2^10 * 2^10 byte = 1024^2
1 gb = 2^10 * 2^10 * 2^10 byte = 1024 ^3