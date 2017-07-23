#ifndef CharBuffer_h__
#define CharBuffer_h__
#include "Buffer.h"

namespace Basic {
template<int N>
class CharBuffer :public Buffer {
  public:
    CharBuffer()
        :Buffer(N) {
    }
};
}

#endif // CharBuffer_h__
