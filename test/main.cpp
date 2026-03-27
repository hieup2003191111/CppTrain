namespace utils {
    extern void parse_bt(); // Giả sử bạn muốn gọi bản của Radio
    extern void parse(); // Giả sử bạn muốn gọi bản của Radio

}

int main() {
    utils::parse_bt();
    utils::parse();

    return 0;
}