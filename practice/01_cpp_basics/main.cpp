#include <iostream>

bool is_valid_sample(int sample)
{
    return sample >= 0 && sample <= 100;
}

int main()
{
    int sample = 0;
    int count = 0;
    int sum = 0;

    std::cout << "请输入整数，按 Ctrl+D 结束输入：\n";

    while (std::cin >> sample)
    {
        if (!is_valid_sample(sample))
        {
            continue;
        }

        sum += sample;
        ++count;
    }

    if (count == 0)
    {
        std::cout << "没有有效数据。\n";
    }
    else
    {
        double average = static_cast<double>(sum) / count;

        std::cout << "有效数据个数：" << count << '\n';
        std::cout << "平均值：" << average << '\n';
    }

    return 0;
}
