#include <iostream>     //编译前 预处理（头文件）后再编译


int main(void) 
{
    //using namespace std;    //std命名空间
    //"::"解析运算符
    //using std::cin;
    //using std::cout;
    //using std::endl;

    int carrots;

    std::cout << "How many carrots do you have?" << std::endl;
    std::cin >> carrots;
    std::cout << "Here are two more.";
    carrots += 2;
    std::cout << "Now you have " << carrots << " 6carrots" << std::endl;

    return 0;
}//作用域