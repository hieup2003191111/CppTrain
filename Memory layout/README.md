# Bố cục bộ nhớ trong C/C++ (Memory Layout)

Tài liệu này giải thích chi tiết về bố cục bộ nhớ trong C/C++ cùng với các ví dụ minh họa cho mục đích giảng dạy.

## Mục lục

1. [Giới thiệu về bố cục bộ nhớ](#giới-thiệu-về-bố-cục-bộ-nhớ)
2. [Các phân vùng bộ nhớ chính](#các-phân-vùng-bộ-nhớ-chính)
   - [Text Segment](#text-segment)
   - [Data Segment](#data-segment)
   - [BSS Segment](#bss-segment)
   - [Heap](#heap)
   - [Stack](#stack)
3. [Ví dụ minh họa](#ví-dụ-minh-họa)
   - [Ví dụ 1: Biến toàn cục và cục bộ](#ví-dụ-1-biến-toàn-cục-và-cục-bộ)
   - [Ví dụ 2: Cấp phát động](#ví-dụ-2-cấp-phát-động)
   - [Ví dụ 3: Phân tích bộ nhớ chi tiết](#ví-dụ-3-phân-tích-bộ-nhớ-chi-tiết)
   - [Ví dụ 4: Các vấn đề phổ biến](#ví-dụ-4-các-vấn-đề-phổ-biến)
4. [Bài tập thực hành](#bài-tập-thực-hành)

## Yêu cầu

- Trình biên dịch C/C++ (GCC, Clang, hoặc MSVC)
- Hiểu biết cơ bản về C/C++

## Cách sử dụng các ví dụ

Các ví dụ được tổ chức trong thư mục `src/`. Mỗi ví dụ đều có file mã nguồn riêng và hướng dẫn biên dịch, chạy chương trình.
