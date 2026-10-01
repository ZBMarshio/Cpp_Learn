# 2.1step2cpp

- C++对大小写、拼写均敏感
- 注释使用//（快捷键Ctrl+/）

## main()函数

### 作为接口的函数头
- int main() 作为函数头，作为操作系用和main()之间的接口
- 前面的int表示函数返回类型，后面的()为形参列表或参数列表

### 必须使用main()而不能叫其他名称
- 每个程序必须有一个main()启动

## C++注释

## C++预处理器和iostream文件

#include <iostream>

- 在源码编译前加入iostream文件内容
- 实质上是将iostream的文件内容替换这一行指令
- 为了使用cin和cout

## 头文件名

- 头文件(hander file)
- 仍可使用C语言的头文件拓展名h，也可以在函数前加c并去掉拓展名表示

## 名称空间

using namespace std;
- 使用名称空间可以区分不同版本的同名函数
如： Microflop::wanda();
    Piscine::wanda();
- 不使用using命令是需要std::endl
