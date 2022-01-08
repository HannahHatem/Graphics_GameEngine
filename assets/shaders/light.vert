#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;


out Varyings {
    vec3 normal;
    vec3 view;
    vec3 world;
    vec2 tex_coord;
} vs_out;

uniform mat4 M;
uniform mat4 M_IT;
uniform mat4 VP;
uniform vec3 eye;

void main(){
    vec3 world = (M * vec4(position, 1.0)).xyz;
    gl_Position = VP * vec4(world, 1.0);
    vs_out.normal = (M_IT * vec4(normal, 0.0)).xyz;
    vs_out.view = eye - world;
    vs_out.world = world;
    vs_out.tex_coord = tex_coord;
}