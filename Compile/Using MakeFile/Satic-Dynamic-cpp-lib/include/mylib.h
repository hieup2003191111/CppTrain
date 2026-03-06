#ifndef MYLIB_H
#define MYLIB_H

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define MYLIB_API __declspec(dllexport)
    #else
        #define MYLIB_API __declspec(dllimport)
    #endif
#else
    #define MYLIB_API
#endif

/**
 * @brief In một thông báo chào mừng
 */
MYLIB_API void hello();

/**
 * @brief Tính tổng hai số nguyên
 * 
 * @param a Số nguyên thứ nhất
 * @param b Số nguyên thứ hai
 * @return Tổng của hai số
 */
MYLIB_API int add(int a, int b);

/**
 * @brief Tính hiệu hai số nguyên
 * 
 * @param a Số nguyên thứ nhất
 * @param b Số nguyên thứ hai
 * @return Hiệu của hai số
 */
MYLIB_API int subtract(int a, int b);

#endif /* MYLIB_H */
