#pragma once
#include "Array.h"
#include "base.h"
class Delegate;
struct uEventArgs {
  public:
    virtual ~uEventArgs() {
    };
};
class CallbackObject {
  public:
    virtual ~CallbackObject() {
    }
    virtual void onCallBack(const Delegate& d, uEventArgs*  e) {
    }
};

class Delegate : public Array<CallbackObject*> {
  public:
    typedef Array<CallbackObject*> SuperType;
    virtual ~Delegate(void) {
    }

    Delegate& operator+= (CallbackObject* callback) {
        CXASSERT(!this->Find(callback));
        this->push_back(callback);
        return *this;
    }
    Delegate& operator-= (CallbackObject* callback) {
        iterator iter = std::find(this->begin(), this->end(), callback);
        if (iter != this->end())
            this->erase(iter);
        return *this;
    }
    void trigger(uEventArgs* event = 0) {
        iterator iEnd = this->end();
        for (iterator i = this->begin(); i != iEnd; ++i) {
            CallbackObject* callback = *i;
            callback->onCallBack(*this, event);
        }
    }
};
inline bool operator== (const Delegate& lhs, const Delegate& rhs) {
    return &lhs == &rhs;
}
