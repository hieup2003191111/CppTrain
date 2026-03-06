// string_utils.h
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef STRING_UTILS_EXPORTS
    #define STRING_UTILS_API __declspec(dllexport)
  #else
    #define STRING_UTILS_API __declspec(dllimport)
  #endif
#else
  #define STRING_UTILS_API __attribute__((visibility("default")))
#endif

#include <string>
#include <vector>

namespace stringutils {

/**
 * Chuyển đổi một chuỗi sang chữ hoa
 * @param input Chuỗi đầu vào
 * @return Chuỗi đã được chuyển sang chữ hoa
 */
STRING_UTILS_API std::string toUpper(const std::string& input);

/**
 * Chuyển đổi một chuỗi sang chữ thường
 * @param input Chuỗi đầu vào
 * @return Chuỗi đã được chuyển sang chữ thường
 */
STRING_UTILS_API std::string toLower(const std::string& input);

/**
 * Tách chuỗi thành các phần dựa trên ký tự phân cách
 * @param input Chuỗi đầu vào
 * @param delimiter Ký tự phân cách
 * @return Vector chứa các phần của chuỗi
 */
STRING_UTILS_API std::vector<std::string> split(const std::string& input, char delimiter);

/**
 * Nối các chuỗi trong một vector với ký tự phân cách
 * @param strings Vector chứa các chuỗi
 * @param delimiter Ký tự phân cách
 * @return Chuỗi đã được nối
 */
STRING_UTILS_API std::string join(const std::vector<std::string>& strings, const std::string& delimiter);

} // namespace stringutils

#endif // STRING_UTILS_H
