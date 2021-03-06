//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <stdexcept>

//template<typename T, int MAXSIZE>
//class Stack{
    //private:
        //T elems[MAXSIZE];
        //int numElems;

    //public:
        //Stack();
        //void push(T const&);
        //void pop();
        //T top() const;
        //bool isEmpty() const{
            //return numElems == 0;
        //}

        //bool isFull() const{
            //return numElems == MAXSIZE;
        //}
//};

//template<typename T, int MAXSIZE>
//Stack<T, MAXSIZE>::Stack():numElems(0)
//{
    //// 不作任何事，仅为了初始化numElems。
//}

//template<typename T, int MAXSIZE>
//void Stack<T, MAXSIZE>::push(T const& elem)
//{
    //if(numElems == MAXSIZE)
    //{
        //throw std::out_of_range("Stack<>::push()==>stack is full.");
    //}

    //elems[numElems] = elem;
    //++numElems;
//}

//template<typename T, int MAXSIZE>
//void Stack<T, MAXSIZE>::pop()
//{
    //if(numElems <= 0)
    //{
        //throw std::out_of_range("Stack<>::pop: empty stack");
    //}

    //--numElems;
//}

//template<typename T, int MAXSIZE>
//T Stack<T, MAXSIZE>::top()const
//{
    //if(numElems)
    //{
        //throw std::out_of_range("Stack<>::pop: empty stack");
    //}

    //// 返回最后一个元素。
    //return elems[numElems - 1];
//}

//int main()
//{
    //try
    //{
        //Stack<int, 20> int20Stack;
        //Stack<int, 40> int40Stack;
        //Stack<std::string, 40> stringStack;

        //int20Stack.push(7);
        //std::cout<<"int20Stack.top() : "<<int20Stack.top()<<std::endl;
        //int20Stack.pop();

        //stringStack.push("HelloWorld!");
        //std::cout<<"stringStack.top() : "<<stringStack.top()<<std::endl;
        //stringStack.pop();
        //stringStack.pop();
    //}
    //catch(std::exception const& ex)
    //{
        //std::cerr<<"Exception: "<<ex.what()<<std::endl;

        //return EXIT_FAILURE;
    //}

    //return 0;
//}

#include <stdio.h>

template<typename T, int MAX_SIZE=20, bool COPY=true>
class CTEST
{
public:
    CTEST () = default;
    virtual ~CTEST () = default;
    void print_value();
    void not_template_method();

private:
};

template<typename T, int MAX_SIZE, bool COPY>
void CTEST<T, MAX_SIZE, COPY>::print_value()
{
    if(COPY)
    {
        printf("Can COPY**************\n");
    }
    T a;
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("%d\n", i);
    }
}

int main(int argc, char *argv[])
{
    CTEST<int, 5, false> ctest;
    ctest.print_value();
    ctest.not_template_method();
    return 0;
}



