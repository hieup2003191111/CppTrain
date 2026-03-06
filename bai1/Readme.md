1.
1.1.
Biến khai báo trong hàm chỉ lưu giữ giá trị trong block,ngoài block sẽ bị xoá.
1.2.
Khai báo biến với từ khoá static sẽ lưu lại giá trị trước đó.
2.
2.1.
Khi truyền giá trị vào tham số hàm,hệ thống tạo thêm 1 bản sao copy lưu trữ ở stack->làm tốn bộ nhớ với struct lớn.
2.2.
Khi truyền vào tham chiếu ,lưu trữ kích thước con trỏ là 4 or 8 byte->tiết kiệm bộ nhớ

void displaySongInList(int listPosition,const SongMetadata& song) {}

3.
con tro cap 2 dùng để thay đổi giá trị vùng nhớ mà con trỏ đang trỏ đến
có 2 cách:con trỏ cấp 2 và tham chiếu con trỏ
vd1: void nextpoint(int ** current,int * next){}
vd2: void nextpoint(int *& current,int * next){}

4.không thể trả về 1 địa chỉ,tham chiếu của 1 biến stack được khai báo trong hàm,phải sử dụng biến static
