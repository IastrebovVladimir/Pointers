#ifndef SHAREDPTR_H
#define SHAREDPTR_H

template<typename T>
class SharedPtr {
private:
    T* ptr;
    std::size_t *referenceCount;

    void RemoveCurrent() noexcept {
        if (referenceCount == nullptr)
            return;

        (*referenceCount)--;

        if (*referenceCount == 0) {
            delete ptr;
            delete referenceCount;
        }

        ptr = nullptr;
        referenceCount = nullptr;
    }

public:
    SharedPtr() noexcept : ptr(nullptr), referenceCount(nullptr) {}

    SharedPtr(T *object) : ptr(object) {
        if (object == nullptr)
            referenceCount = nullptr;
        else
            referenceCount = new std::size_t(1);
    }

    SharedPtr(const SharedPtr &other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount != nullptr) {
            (*referenceCount)++;
        }
    }

    SharedPtr(SharedPtr &&other) noexcept : ptr(other.ptr), referenceCount(other.referenceCount) {
        other.ptr = nullptr;
        other.referenceCount = nullptr;
    }

    SharedPtr &operator=(const SharedPtr &other) noexcept {
        if (this != &other) {
            if (other.referenceCount != nullptr)
                (*other.referenceCount)++;

            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;
        }

        return *this;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept {
        if (this != &other) {
            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;

            other.ptr = nullptr;
            other.referenceCount = nullptr;
        }

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

    std::size_t GetReferenceCount() const {
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
