#include "context.h"
#include <imgui.h>

ContextUPtr Context::Create(){
    auto context = ContextUPtr(new Context());
    if(!context->Init())
        return nullptr;
    return std::move(context);
}
bool Context::Init(){
    glm::vec3 vertices[] = {
        //first triangle
        first_position,
        second_position,
        third_position,
    };
    uint32_t indices[] = {
        0, 1, 2,
    };

    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 12);

    m_vertexLayout -> SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t)*6);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs",GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if(!vertShader||!fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if(!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.0f, 0.1f, 0.2f, 0.0f);
    return true;
}

void Context::Render(){
    if (ImGui::Begin("my first ImGui window")) {
        if (ImGui::ColorEdit4("clear color", glm::value_ptr(m_clearColor))){
            glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        }
        bool updated = false;
        updated |= ImGui::DragFloat3("Vertex 1", glm::value_ptr(first_position), 0.1f);
        updated |= ImGui::DragFloat3("Vertex 2", glm::value_ptr(second_position), 0.1f);
        updated |= ImGui::DragFloat3("Vertex 3", glm::value_ptr(third_position), 0.1f);
        if (updated) {
            glm::vec3 vertices[] = {
                first_position,
                second_position,
                third_position,
            };
            m_vertexBuffer->UpdateData(vertices, sizeof(vertices));
        }
    }
    ImGui::End();
    glClear(GL_COLOR_BUFFER_BIT);
    m_program->Use();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
