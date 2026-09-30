#include <iostream>

double celsius_to_fahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32.0;
}

double fahrenheit_to_celsius(double fahrenheit)
{
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main()
{
    int choice = 0;
    double temperature = 0.0;

    std::cout << "请选择转换方向：\n";
    std::cout << "1. 摄氏度转华氏度\n";
    std::cout << "2. 华氏度转摄氏度\n";
    std::cout << "请输入选项：";

    if (!(std::cin >> choice) || (choice != 1 && choice != 2))
    {
        std::cout << "选项无效。\n";
        return 1;
    }

    std::cout << "请输入温度：";

    if (!(std::cin >> temperature))
    {
        std::cout << "输入无效。\n";
        return 1;
    }

    if (choice == 1)
    {
        double result = celsius_to_fahrenheit(temperature);
        std::cout << temperature << " 摄氏度 = "
                  << result << " 华氏度\n";
    }
    else
    {
        double result = fahrenheit_to_celsius(temperature);
        std::cout << temperature << " 华氏度 = "
                  << result << " 摄氏度\n";
    }

    return 0;
}