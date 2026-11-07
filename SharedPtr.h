#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <cstddef>
#include <stdexcept>
#include <type_traits>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    std::size_t* referenceCount;

    template <typename U>
    friend class SharedPtr;

    void RemoveCurrent() noexcept {
        if (referenceCount != nullptr) {
            --(*referenceCount);

            if (*referenceCount == 0) {
                delete ptr;
                delete referenceCount;
            }
        }

        ptr = nullptr;
        referenceCount = nullptr;
    }

public:
    SharedPtr() noexcept : ptr(nullptr), referenceCount(nullptr) {}

    SharedPtr(T* object) : ptr(object) {
        if (object == nullptr)
            referenceCount = nullptr;
        else
            referenceCount = new std::size_t(1);
    }

    SharedPtr(const SharedPtr& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount != nullptr) {
            ++(*referenceCount);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        other.ptr = nullptr;
        other.referenceCount = nullptr;
    }

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    SharedPtr(const SharedPtr<U>& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount != nullptr) {
            ++(*referenceCount);
        }
    }

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    SharedPtr(SharedPtr<U>&& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        other.ptr = nullptr;
        other.referenceCount = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            if (other.referenceCount != nullptr) {
                ++(*other.referenceCount);
            }

            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;

            other.ptr = nullptr;
            other.referenceCount = nullptr;
        }

        return *this;
    }

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    SharedPtr& operator=(const SharedPtr<U>& other) noexcept {
        if (other.referenceCount != nullptr) {
            ++(*other.referenceCount);
        }

        RemoveCurrent();

        ptr = other.ptr;
        referenceCount = other.referenceCount;

        return *this;
    }

    template <typename U> requires std::is_convertible_v<U*, T*> && (!std::is_array_v<U>)
    SharedPtr& operator=(SharedPtr<U>&& other) noexcept {
        RemoveCurrent();

        ptr = other.ptr;
        referenceCount = other.referenceCount;

        other.ptr = nullptr;
        other.referenceCount = nullptr;

        return *this;
    }

    T& operator*() const {
        if (ptr == nullptr) {
            throw std::runtime_error("Cannot dereference an empty SharedPtr");
        }

        return *ptr;
    }

    T* Get() const noexcept {
        return ptr;
    }

    std::size_t GetReferenceCount() const noexcept {
        return referenceCount == nullptr ? 0 : *referenceCount;
    }

    bool Empty() const noexcept {
        return ptr == nullptr;
    }

    void Reset(T* object = nullptr) {
        if (ptr == object)
            return;

        RemoveCurrent();

        if (object != nullptr) {
            ptr = object;
            referenceCount = new std::size_t(1);
        }
    }

    ~SharedPtr() noexcept {
        RemoveCurrent();
    }
};

template <typename T>
class SharedPtr<T[]> {
private:
    T* ptr;
    std::size_t* referenceCount;

    void RemoveCurrent() noexcept {
        if (referenceCount != nullptr) {
            --(*referenceCount);

            if (*referenceCount == 0) {
                delete[] ptr;
                delete referenceCount;
            }
        }

        ptr = nullptr;
        referenceCount = nullptr;
    }

public:
    SharedPtr() noexcept : ptr(nullptr), referenceCount(nullptr) {}

    SharedPtr(T* object) : ptr(object) {
        if (object == nullptr)
            referenceCount = nullptr;
        else
            referenceCount = new std::size_t(1);
    }

    SharedPtr(const SharedPtr& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount != nullptr) {
            ++(*referenceCount);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        other.ptr = nullptr;
        other.referenceCount = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            if (other.referenceCount != nullptr) {
                ++(*other.referenceCount);
            }

            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;

            other.ptr = nullptr;
            other.referenceCount = nullptr;
        }

        return *this;
    }

    T& operator[](std::size_t index) const noexcept {
        return ptr[index];
    }

    T* Get() const noexcept {
        return ptr;
    }

    std::size_t GetReferenceCount() const noexcept {
        return referenceCount == nullptr ? 0 : *referenceCount;
    }

    bool Empty() const noexcept {
        return ptr == nullptr;
    }

    void Reset(T* object = nullptr) {
        if (ptr == object)
            return;

        RemoveCurrent();

        if (object != nullptr) {
            ptr = object;
            referenceCount = new std::size_t(1);
        }
    }

    ~SharedPtr() noexcept {
        RemoveCurrent();
    }
};

#endif
