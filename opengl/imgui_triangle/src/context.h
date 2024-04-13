#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"

CLASS_PTR(Context)
class Context{
public:
    static ContextUPtr Create();

    void Render();
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
    glm::vec3 first_position { glm::vec3(0.5f, -0.5f, 0.0f) };
    glm::vec3 second_position { glm::vec3(-0.5f, -0.5f, 0.0f) };
    glm::vec3 third_position { glm::vec3(0.0f, 0.5f, 0.0f) };

    glm::vec4 m_clearColor { glm::vec4(0.1f, 0.2f, 0.3f, 0.0f) };
};

#endif