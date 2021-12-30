#version 450 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex;
out vec2 texture_coord;
out vec3 frag_position;
out vec3 normal_vec;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    frag_position = vec3(model * vec4(pos, 1.0f));
    normal_vec = normal;
    texture_coord = tex;
}
