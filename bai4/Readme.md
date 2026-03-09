1.
Dùng tiền xử lí để :
-Tiết kiệm bộ nhớ (Flash/RAM): Giúp loại bỏ hoàn toàn mã nguồn thừa của các dòng xe khác ngay từ khi biên dịch, làm file firmware nhẹ nhất có thể.

-Quản lý nhiều dòng xe trong 1 file code: Bạn chỉ cần viết code một lần, khi muốn nạp cho xe nào thì chỉ cần gắn "thẻ" (-DMODEL_S hoặc -DMODEL_X) lúc biên dịch là xong.

-Chốt chặn an toàn (Safeguard): Lệnh #error ngăn chặn việc tạo ra file lỗi nếu người dùng quên chọn dòng xe, tránh hỏng hóc phần cứng khi nạp phần mềm.

2.
