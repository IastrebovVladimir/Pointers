#ifndef SHAREDPTR_H
#define SHAREDPTR_H

template<typename T>
class SharedPtr {
private:
    // rvalue r lvalue - прочитать
    // прочитать про циклические указатели
    T* ptr;
    std::size_t *referenceCount;

    void RemoveCurrent() {
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
    SharedPtr() : ptr(nullptr), referenceCount(nullptr) {}

    SharedPtr(T *object) : ptr(object) {
        if (object == nullptr)
            referenceCount = nullptr;
        else
            referenceCount = new std::size_t(1);
    }

    SharedPtr(const SharedPtr &other) : ptr(other.ptr), referenceCount(other.referenceCount) {
        if (referenceCount != nullptr) {
            (*referenceCount)++;
        }
    }

    SharedPtr(SharedPtr &&other) : ptr(other.ptr), referenceCount(other.referenceCount) {
        other.ptr = nullptr;
        other.referenceCount = nullptr;
    }

    SharedPtr &operator=(const SharedPtr &other) {
        if (this != &other) {
            if (other.referenceCount != nullptr)
                (*other.referenceCount)++;

            RemoveCurrent();

            ptr = other.ptr;
            referenceCount = other.referenceCount;
        }

        return *this;
    }

    SharedPtr &operator=(SharedPtr &&other) {
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

    T* Get() const {
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

    ~SharedPtr() {
        RemoveCurrent();
    }

};

#endif