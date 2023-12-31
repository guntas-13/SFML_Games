#include <iostream>

template <typename T>
class DynamicArray
{
    size_t m_size;
    T* m_array;

public:

    DynamicArray(size_t size)
        : m_size(size)
        , m_array(new T[size])
    {
        std::cout << "Array Constructor\n";
    }

    ~DynamicArray()
    {
        delete [] m_array;
        std::cout << "Array Destructor\n";
    }

    void print() const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            std::cout << i << " " << m_array[i]  << "\n";
        }
    }

    // Operator Overloading -> using the "[]" operator
    
    // "const" handling
    const T& operator [](size_t size) const
    {
        return m_array[size];
    }

    // non "const" version of the same function
    T& operator [](size_t size)
    {
        return m_array[size];
    }

};

int main(int argc, char* argv[])
{

    DynamicArray<float> MyArray(10);

    MyArray[2] = 3.14;
    MyArray[6] = 2.71;

    MyArray.print();
    return 0;
}