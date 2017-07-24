#pragma once
template<typename T>
class WeakPointer : public std::weak_ptr<T> {
  public:
    typedef WeakPointer<T> MyType;
    typedef std::weak_ptr<T> Super;
    MyType& operator=(Pointer<T> rhs) {
        rhs.
    }
    T* operator->() {
        CXASSERT(this->expired());
        return this->lock();
    }
    operator bool() {
        return this->expired() && this->lock() != nullptr;
    }
};
