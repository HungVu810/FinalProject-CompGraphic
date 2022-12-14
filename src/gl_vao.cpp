#include"../include/gl_vao.h"
#include"../include/runtime_except.h"
#include<cassert>
#include<vector>

gl_vao::gl_vao() : gl_object::gl_object(){
    glGenVertexArrays(1, &name);
    glGenBuffers(1, &ebo);
}

gl_vao::~gl_vao() noexcept{
    glDeleteVertexArrays(1, &name);
    glDeleteBuffers(1, &ebo);
}

void gl_vao::bind() const{
    glBindVertexArray(name);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void gl_vao::attribFormat(unsigned index, unsigned component, GLenum type, bool normalized, size_t stride, const void *offset){
    assert(index >= 0);
    try{
        glVertexAttribPointer(index, component, type, normalized, stride, offset);
        glEnableVertexAttribArray(index);
    }
    catch(...){
        runtimeException();
    }
}

void gl_vao::eboData(const std::vector<unsigned> &ebuf, GLenum usage){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * ebuf.size(), ebuf.data(), usage);
}
