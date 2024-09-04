#include <iostream>
#include <algorithm>

template <typename T>
class Vector {
    size_t size;
    size_t rsize;
    T* vector;

public:
    Vector(size_t s)
        : size(s), rsize(0), vector(new T[size]) {}

    ~Vector() {
        delete[] vector;
    }

    Vector(const Vector& other)
        : size(other.size), rsize(other.rsize), vector(new T[other.size]) {
        std::copy(other.vector, other.vector + other.rsize, vector);
    }

    Vector(Vector&& other) noexcept
        : size(other.size), rsize(other.rsize), vector(other.vector) {
        other.size = 0;
        other.rsize = 0;
        other.vector = nullptr;
    }

    Vector& operator=(Vector other) {
        swap(other);
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(size, other.size);
        std::swap(rsize, other.rsize);
        std::swap(vector, other.vector);
    }

    void push_back(const T& num) {
        if (rsize == size) {
            resize(size * 2);
        }
        vector[rsize++] = num;
    }

    void pop() {
        if (rsize > 0) {
            --rsize;
        }
    }

    T at(size_t index) const {
        if (index < rsize) {
            return vector[index];
        }
        throw std::out_of_range("Index out of range");
    }

    void erase(size_t index) {
        if (index < rsize) {
            std::move(vector + index + 1, vector + rsize, vector + index);
            --rsize;
        }
    }

    void insert(size_t index, const T& num) {
        if (index <= rsize) {
            if (rsize == size) {
                resize(size * 2);
            }
            std::move(vector + index, vector + rsize, vector + index + 1);
            vector[index] = num;
            ++rsize;
        }
    }

    void print() const {
        for (size_t i = 0; i < rsize; ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }

    bool empty() const {
        return rsize == 0;
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return size;
    }

private:
    void resize(size_t new_size) {
        T* new_vector = new T[new_size];
        std::copy(vector, vector + rsize, new_vector);
        delete[] vector;
        vector = new_vector;
        size = new_size;
    }
};

int main() {
    Vector<int> my(2);

    for (int i = 0; i < 2; ++i) {
        my.push_back(i + 1);
    }

    std::cout << "Full vector:" << std::endl;
    my.print();

    my.push_back(3);
    my.push_back(4);
    my.push_back(5);
    std::cout << "Add 3, 4, 5:" << std::endl;
    my.print();

    Vector<int> B(my);
    std::cout << "Copy constructor:" << std::endl;
    my.print();
    B.print();

    return 0;
}

