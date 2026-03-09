void activate_parser();
bool internal_recursive_parse(); // Co tinh khai bao de "dung trom"

int main() {
    activate_parser(); // Chay binh thuong
    
    // Neu ban bo comment dong duoi day, Linker se bao loi "Undefined reference"
    // vi ham nay da bi danh dau la 't' (local), Linker khong tim thay no tu ngoai.
    //internal_recursive_parse(); 
    
    return 0;
}