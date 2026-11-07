#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include <cstddef>
#include <type_traits>

template <typename T>
class UniquePtr {
private:
    T* ptr;

    template <typename U>
    friend class UniquePtr;

public:
    UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    UniquePtr(UniquePtr<U>&& other) noexcept : ptr(other.ptr) {
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

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    UniquePtr& operator=(UniquePtr<U>&& other) noexcept {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;

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

template <typename T>
class UniquePtr<T[]> {
private:
    T* ptr;

public:
    explicit UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;

            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    T& operator[](std::size_t index) const noexcept {
        return ptr[index];
    }

    T* Get() const noexcept {
        return ptr;
    }

    void Reset(T* p = nullptr) noexcept {
        if (ptr != p) {
            delete[] ptr;
            ptr = p;
        }
    }

    ~UniquePtr() noexcept {
        delete[] ptr;
    }
};

#endif
