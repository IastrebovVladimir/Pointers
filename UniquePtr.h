#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

template <typename T>
class UniquePtr {
private:
    T* ptr;
public:
    UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    T& operator*() const noexcept {
        return *ptr;
    }

    T* Get() const noexcept {
        return ptr;
    }

    void Reset(T* p = nullptr) noexcept {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    ~UniquePtr() noexcept {
        delete ptr;
    }
};

#endif
