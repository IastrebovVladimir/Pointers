#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

template <typename T>
class UniquePtr {
private:
    T* ptr;
public:
    UniquePtr(T* p = nullptr) : ptr(p) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* Get() const {
        return ptr;
    }

    void Reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    ~UniquePtr() {
        delete ptr;
    }
};

#endif