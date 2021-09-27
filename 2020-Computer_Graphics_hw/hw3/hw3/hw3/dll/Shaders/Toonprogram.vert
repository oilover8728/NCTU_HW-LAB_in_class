#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M, V, P;

uniform mat4 Transpose_Inverse_M;
uniform vec3 CamPos;
uniform vec3 LightPos;
uniform vec4 Diffuse_reflectivity;

out vec2 uv;

out vec3 normal;
out vec3 vertex_to_light;
out vec4 Kd;

void main() {
  gl_Position = P * V * M * vec4(in_position, 1.0);
  uv= texcoord;

  Kd = Diffuse_reflectivity;
  normal = (Transpose_Inverse_M * vec4(in_normal,0.0)).xyz;
  vertex_to_light =  LightPos - ( M * vec4(in_position, 1.0)).xyz;
}