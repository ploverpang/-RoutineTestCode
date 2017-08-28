#include <stdio.h>
#include <float.h>

/// \brief mmRound 四舍五入取整
///
/// \param float
///
/// \return 整数
#ifndef mmRound
#define mmRound(a)            (int)((a) + ((a) >= 0 ? 0.5f : -0.5f))
#endif

/// \brief mmCell 向上取整
///
/// \param 浮点数
///
/// \return 整数
#ifndef mmCeil
#define mmCeil(a)            (((a) > 0) ? (((a) - (int)(a)) > FLT_EPSILON ? ((int)(a) + 1) : (int)(a)) : (int)(a))
#endif

/// \brief mmFloor 向下取整
///
/// \param 浮点数
///
/// \return 整数
#ifndef mmFloor
#define mmFloor(a)            (((a) >= 0) ? (int)(a) : (((int)(a) - (a)) > FLT_EPSILON ? ((int)(a)-1) : (int)(a)))
#endif

int main(int argc, char *argv[])
{
    float test_data[7] = {1.1f, 1.0f, 0.9f, 0.f, -0.9f, -1.0f, 1.1f};
    for (int i = 0; i < 7; ++i) {
        printf("data: %f\t round:%d\t ceil = %d\t floor:%d\n", test_data[i],mmRound(test_data[i]), mmCeil(test_data[i]), mmFloor(test_data[i]));
    }
    return 0;
}
