#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 Projection;
uniform mat4 View;

out vec3 frag_normal;
out vec2 frag_texcoord;

void main() {
  gl_Position =  Projection * View * M * vec4(position, 1.0);
  frag_normal = normal;
  frag_texcoord = texcoord;
}

