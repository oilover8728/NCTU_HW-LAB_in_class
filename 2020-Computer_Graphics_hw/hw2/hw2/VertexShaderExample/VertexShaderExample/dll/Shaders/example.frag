#version 430

in vec3 color;
out vec4 frag_color;

void main() {
    frag_color = vec4(color, 1.0);
}
//// TODO ////
//
// Hint:
// 1. Recieve texcoord and Normal from vertex shader
// 2. Calculate and return final color to opengl
//