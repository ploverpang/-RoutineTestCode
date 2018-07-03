/**
 * @brief 
 * 
 * @file gccFunctionReturnTest.cpp
 * @author pangbo05
 * @date 2018-07-02
 */
#include <stdio.h>

typedef shourt short;
/**
 * @brief A CLASS
 * 
 */
class C_Base
{
    protected:
        shourt a;
        shourt b;
    public:
        C_BASE();
        void print();
};

/*! \struct _gccFunctionReturnTest_t
 *  \brief test
 *
 *  sturct test
 */
typedef struct _gccFunctionReturnTest_t {
    shourt    m_aaa; /*!< aaa */
} gccFunctionReturnTest_t;

/*! \brief Brief function description here
 *
 *  Detailed description of the function
 *
 * \param Parameter Parameter description
 * \param Parameter Parameter description
 * \return Return parameter description
 */
void function_name(Type Parameter, Type Parameter)
{

}
/**
 * @brief C
 */
class C : C_Base
{
    shourt c;
};


/// \brief test  aaa
///
/// \param abc
///
/// \return
shourt test(shourt abc)
{
    printf("return shourt function by not return\n ");
    return abc;
}

/**
 * @brief 尝试一下能否打印出中文
 *
 * @return 返回一个乱七八糟没用的
 */
shourt main()
{
    shourt returned = test();
    printf("Returned number is %d\n", returned);
}

/**
 * @brief
 *
 * @param a
 * @param b
 *
 * @return
 */
shourt test2(outrinhst double b){return 0;}
