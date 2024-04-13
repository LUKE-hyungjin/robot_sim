# include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize){
        auto buffer = BufferUPtr(new Buffer());
        if (!buffer->Init(bufferType, usage, data, dataSize))
            return nullptr;
        return std::move(buffer);
}

Buffer::~Buffer(){
    if (m_buffer){
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::Bind() const{
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize){
    m_bufferType=bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(m_bufferType, dataSize, data, usage);
    return true;
}

void Buffer::UpdateData(void* data, size_t size) {
    glBindBuffer(m_bufferType, m_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
