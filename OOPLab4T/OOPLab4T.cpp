#include <iostream>

class VectorULong
{
    static int objectCount;
    unsigned long* a;
    int size;
    int state;

public:
    enum State {
        NO_ERROR = 0,
        OUT_OF_MEMORY,
        INDEX_OUT_OF_RANGE
    };

    int getErrorCode() const {
        return state;
    }

    static int getObjectCount() {
        return objectCount;
    }

    VectorULong() : size(1), state(NO_ERROR) {
        a = new unsigned long[size];
        if (a == nullptr) {
            state = OUT_OF_MEMORY;
            return;
        }
        a[0] = 0;
        ++objectCount;
    }

    VectorULong(int Size) : size(Size), state(NO_ERROR) {
        a = new unsigned long[Size];
        if (a == nullptr) {
            state = OUT_OF_MEMORY;
            return;
        }
        for (int i = 0; i < Size; i++) {
            a[i] = 0;
        }
        ++objectCount;
    }

    VectorULong(int Size, unsigned long Value) : size(Size), state(NO_ERROR) {
        a = new unsigned long[Size];
        if (a == nullptr) {
            state = OUT_OF_MEMORY;
            return;
        }
        for (int i = 0; i < Size; i++) {
            a[i] = Value;
        }
        ++objectCount;
    }

    VectorULong(const VectorULong& other) : size(other.size), state(other.state) {
        a = new unsigned long[size];
        if (a == nullptr) {
            state = OUT_OF_MEMORY;
            return;
        }
        for (int i = 0; i < size; i++) {
            a[i] = other.a[i];
        }
        ++objectCount;
    }

    ~VectorULong() {
        delete[] a;
        --objectCount;
    }

    VectorULong& operator=(const VectorULong& other) {
        if (this != &other) {
            delete[] a;
            size = other.size;
            state = other.state;
            a = new unsigned long[size];
            if (a == nullptr) {
                state = OUT_OF_MEMORY;
                return *this;
            }
            for (int i = 0; i < size; i++) {
                a[i] = other.a[i];
            }
        }
        return *this;
    }

    VectorULong operator+(const VectorULong& b) const {
        if (size != b.size) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] + b.a[i];
        }
        return result;
    }

    VectorULong operator-(const VectorULong& b) const {
        if (size != b.size) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] - b.a[i];
        }
        return result;
    }

    VectorULong operator*(unsigned long scalar) const {
        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] * scalar;
        }
        return result;
    }

    VectorULong operator/(unsigned long scalar) const {
        if (scalar == 0) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] / scalar;
        }
        return result;
    }

    VectorULong operator%(unsigned long scalar) const {
        if (scalar == 0) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] % scalar;
        }
        return result;
    }

    VectorULong operator|(const VectorULong& b) const {
        if (size != b.size) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] | b.a[i];
        }
        return result;
    }

    VectorULong operator^(const VectorULong& b) const {
        if (size != b.size) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] ^ b.a[i];
        }
        return result;
    }

    VectorULong operator&(const VectorULong& b) const {
        if (size != b.size) {
            VectorULong result(1);
            result.state = INDEX_OUT_OF_RANGE;
            return result;
        }

        VectorULong result(size);
        for (int i = 0; i < size; i++) {
            result.a[i] = a[i] & b.a[i];
        }
        return result;
    }

    VectorULong operator++() {
        for (int i = 0; i < size; i++) {
            ++a[i];
        }
        return *this;
    }

    VectorULong operator++(int) {
        VectorULong temp(*this);
        operator++();
        return temp;
    }

    VectorULong operator--() {
        for (int i = 0; i < size; i++) {
            --a[i];
        }
        return *this;
    }

    VectorULong operator--(int) {
        VectorULong temp(*this);
        operator--();
        return temp;
    }

    VectorULong operator-() const {
        VectorULong result(*this);
        for (int i = 0; i < size; i++) {
            result.a[i] - result.a[i];
        }
        return result;
    }

    bool operator!() const {
        return size == 0;
    }

    VectorULong operator~() const {
        VectorULong result(*this);
        for (int i = 0; i < size; i++) {
            result.a[i] = ~result.a[i];
        }
        return result;
    }

    VectorULong& operator+=(const VectorULong& b) {
        if (size != b.size) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] += b.a[i];
        }
        return *this;
    }

    VectorULong& operator-=(const VectorULong& b) {
        if (size != b.size) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] -= b.a[i];
        }
        return *this;
    }

    VectorULong& operator*=(unsigned long scalar) {
        for (int i = 0; i < size; i++) {
            a[i] *= scalar;
        }
        return *this;
    }

    VectorULong& operator/=(unsigned long scalar) {
        if (scalar == 0) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] /= scalar;
        }
        return *this;
    }

    VectorULong& operator%=(unsigned long scalar) {
        if (scalar == 0) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] %= scalar;
        }
        return *this;
    }

    VectorULong& operator|=(const VectorULong& b) {
        if (size != b.size) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] |= b.a[i];
        }
        return *this;
    }

    VectorULong& operator^=(const VectorULong& b) {
        if (size != b.size) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] ^= b.a[i];
        }
        return *this;
    }

    VectorULong& operator&=(const VectorULong& b) {
        if (size != b.size) {
            state = INDEX_OUT_OF_RANGE;
            return *this;
        }

        for (int i = 0; i < size; i++) {
            a[i] &= b.a[i];
        }
        return *this;
    }

    bool operator==(const VectorULong& b) const {
        if (size != b.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (a[i] != b.a[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorULong& b) const {
        return !(*this == b);
    }

    bool operator>(const VectorULong& b) const {
        if (size != b.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (a[i] <= b.a[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const VectorULong& b) const {
        return *this > b || *this == b;
    }

    bool operator<(const VectorULong& b) const {
        return !(*this >= b);
    }

    bool operator<=(const VectorULong& b) const {
        return !(*this > b);
    }

    unsigned long& operator[](int index) {
        if (index < 0 || index >= size) {
            state = INDEX_OUT_OF_RANGE;
            return a[size - 1];
        }
        return a[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const VectorULong& vec) {
        for (int i = 0; i < vec.size; ++i) {
            os << vec.a[i] << ' ';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, VectorULong& vec) {
        for (int i = 0; i < vec.size; ++i) {
            is >> vec.a[i];
        }
        return is;
    }
};

int VectorULong::objectCount = 0;

int main() {
    VectorULong v1(5, 7);
    VectorULong v2(5, 15);
    VectorULong v3(5, 10);
    VectorULong v4(5, 0);

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;
    std::cout << "v4: " << v4 << std::endl;

    v4 = v2 + v3;
    std::cout << "v1 = v2 + v3: " << v4 << std::endl;
    v4 = v2 - v3;
    std::cout << "v1 = v2 - v3: " << v4 << std::endl;
    v4 = v2 * 2;
    std::cout << "v1 = v2 * 2: " << v4 << std::endl;
    v4 = v2 / 2;
    std::cout << "v1 = v2 / 2: " << v4 << std::endl;
    v4 = v2 % 3;
    std::cout << "v1 = v2 % 3: " << v4 << std::endl;
    v4 = v2 | v3;
    std::cout << "v1 = v2 | v3: " << v4 << std::endl;
    v4 = v2 ^ v3;
    std::cout << "v1 = v2 ^ v3: " << v4 << std::endl;
    v4 = v2 & v3;
    std::cout << "v1 = v2 & v3: " << v4 << std::endl;

    ++v1;
    std::cout << "++v1: " << v1 << std::endl;
    v1++;
    std::cout << "v1++: " << v1 << std::endl;
    --v1;
    std::cout << "--v1: " << v1 << std::endl;
    v1--;
    std::cout << "v1--: " << v1 << std::endl;
    return 0;
}
