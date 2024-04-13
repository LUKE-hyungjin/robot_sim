#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "common.h"

CLASS_PTR(Buffer)
class Buffer{
public:
    static BufferUPtr CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t datasize);

    ~Buffer();
    uint32_t Get() const { return m_buffer; }
    void Bind() const;
    void UpdateData(void* data, size_t size);

private:
    Buffer() {}
    bool Init(uint32_t bufferType, uint32_t usage, const void* data, size_t datasize);
    uint32_t m_buffer { 0 };
    uint32_t m_bufferType { 0 };
    uint32_t m_usage { 0 };
};

#endif