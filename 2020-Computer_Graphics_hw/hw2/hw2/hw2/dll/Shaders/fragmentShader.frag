#version 430

layout(binding = 0) uniform sampler2D Texture;

in vec3 frag_normal;
in vec2 frag_texcoord;

out vec4 frag_Color;


void main() {
    frag_Color = texture2D(Texture, frag_texcoord); 
}