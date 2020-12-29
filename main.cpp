#include <iostream>

template<size_t N>
struct ALL_COUNT {
    static constexpr unsigned long long value = 13*ALL_COUNT<N - 1>::value;
};
template<>
struct ALL_COUNT<1> {
    static constexpr unsigned long long value = 13;
};

int main()
{
    std::cout << "Общее количество перестановок: " <<  ALL_COUNT<13>::value << std::endl;
    std::cout << "Количество перестановок при которых суммы равны: " <<  ALL_COUNT<6>::value << std::endl;
    return 0;
}
