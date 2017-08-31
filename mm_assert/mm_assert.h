#ifndef MM_ASSERT_H_3OUSSMA4
#define MM_ASSERT_H_3OUSSMA4

#ifdef DEBUG
#define MY_ASSERT(condition) do { \
    if(!(condition))                \
    {\
        assert(condition);\
    }\
}while(0)
#else
#define MY_ASSERT(condition) do { \
    if((condition)){}\
}while(0)
#endif

#endif /* end of include guard: MM_ASSERT_H_3OUSSMA4 */
