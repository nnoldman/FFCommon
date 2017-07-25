#ifndef uBuffer_h__
#define uBuffer_h__
//-------------------------------------------------------------------------
/**
	@brief
	@author nnboy,29/9/2014  12:08
*/
namespace Basic {
class Buffer {
  public:
    Buffer();
    ~Buffer();
    Buffer ( size_t byteCnt );
    void reAllocate ( size_t byteSize );
    void reallocateByElementCount ( size_t cnt );
    void clear();
    inline void setElementByteCount ( size_t size );
    inline size_t length();
    inline size_t size();
    inline void setSize ( size_t size );
    inline size_t capacity() const;
    inline char* getPointer() const;
    inline wchar_t* getWChar();
    inline const char* getString() const;
    inline void copyTo ( void* dst );
    inline void copyFrom ( void* src );
    inline void setChar ( size_t idx, char c );
    template<typename T>
    void addElement ( T v );
    template<typename T>
    void addElement ( T* v, size_t cnt );
    void addString(const char* str);
    void setString(const char* str);


    Buffer& operator=(const char* str);

    template<typename T>
    inline void Buffer::set(size_t idx, const T& v) {
        *((T*)&mData[idx * sizeof(T)]) = v;
    }

    template<typename T>
    inline T& get ( size_t idx ) {
        return* ( ( T* ) &mData[idx * sizeof ( T )] ) ;
    }

    inline void zero() {
        dMemoryZero ( mData, length() );
    }
  protected:
    size_t mElementByteCount;
    size_t mCapacity;
    size_t mCount;
    union {
        char* mData;
        wchar_t* mWData;
    };
};
inline size_t Buffer::length() {
    return mCapacity * mElementByteCount;
}
inline char* Buffer::getPointer() const {
    return mData;
}
inline const char* Buffer::getString() const {
    return ( const char* ) mData;
}
inline void Buffer::setElementByteCount ( size_t size ) {
    mElementByteCount = size;
}

inline void Buffer::copyTo ( void* dst ) {
    dMemoryCopy ( dst, mData, mCount * mElementByteCount );
}

inline void Buffer::copyFrom ( void* src ) {
    dMemoryCopy ( mData, src, mCapacity * mElementByteCount );
}
template<typename T>
inline void Buffer::addElement ( T* v, size_t cnt ) {
    dMemoryCopy ( &mData[mCount * mElementByteCount], v, cnt * mElementByteCount );
    mCount += cnt;
}

template<typename T>
inline void Buffer::addElement ( T v ) {
    * ( ( T* ) &mData[mCount * sizeof ( T )] ) = v;
    mCount++;
}


inline size_t Buffer::size() {
    return mCount;
}

inline void Buffer::setChar ( size_t idx, char c ) {
    CXASSERT ( mData );
    mData[idx] = c;
}
inline size_t Buffer::capacity() const {
    return mCapacity;
}

inline void Buffer::clear() {
    mCount = 0;
    dMemoryZero ( mData, length() );
}
inline Buffer::Buffer ( void ) {
    mData = 0;
    mCount = 0;
    mCapacity = 0;
    mElementByteCount = 1;
}
inline Buffer::Buffer ( size_t byteCnt ) {
    mData = 0;
    mCount = 0;
    mCapacity = byteCnt;
    mElementByteCount = 1;
    reAllocate ( mCapacity );
}


inline Buffer::~Buffer ( void ) {
    dSafeDelete ( mData );
}

inline void Buffer::reAllocate ( size_t byteSize ) {
    dSafeDelete ( mData );
    mData = new char[byteSize];
    if ( mElementByteCount > 0 )
        mCapacity = byteSize / mElementByteCount;
    dMemoryZero ( mData, byteSize );
}

inline void Buffer::reallocateByElementCount ( size_t cnt ) {
    dSafeDelete ( mData );
    mCapacity = cnt;
    mData = new char[mCapacity * mElementByteCount];
    dMemoryZero ( mData, mCapacity * mElementByteCount );
}

inline void Buffer::setSize ( size_t size ) {
    mCount = size;
}

inline wchar_t* Buffer::getWChar() {
    return mWData;
}

inline void Buffer::addString( const char* str ) {
    CXASSERT(str);
    CXASSERT ( mData );
    CXASSERT(mElementByteCount == 1);
    size_t cnt = strlen(str) + 1;
    CXASSERT(cnt <= capacity());
    dMemoryCopy(&mData[mCount * mElementByteCount], (void*)str, cnt * mElementByteCount);
    mCount += cnt;
}

inline void Buffer::setString(const char* str) {
    this->clear();
    addString(str);
}

inline Buffer& Buffer::operator=(const char* str) {
    this->clear();
    addString(str);
    return *this;
}

}

#endif // uBuffer_h__
