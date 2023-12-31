#include <iostream>

void pp(int& i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << "\n";
}

int main(int argc, char* argv[])
{
    int  arr[10] = {};
    int* harr    = new int[10];

    std::cout << "Stack Allocated Memory Addresses\n";
    for (size_t i = 0; i < 10; i++)
    {
        pp(arr[i]);
    }

    std::cout << "\nHeap Allocated Memory Addresses\n";
    for (size_t i = 0; i < 10; i++)
    {
        pp(harr[i]);
    }
}