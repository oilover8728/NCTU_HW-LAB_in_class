#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M, V, P;

out vec2 uv;

uniform mat4 Transpose_Inverse_M;
uniform vec3 LightPos;
uniform vec3 CamPos;
uniform vec4 Ambient_reflectivity;
uniform vec4 Diffuse_reflectivity;
uniform vec4 Specular_reflectivity;
uniform vec4 Ambient_intensity;
uniform vec4 Diffuse_intensity;
uniform vec4 Specular_intensity;
uniform float gloss;

out vec3 normal;
out vec3 vertex_to_light;
out vec3 vertex_to_camera;

out vec4 Ka;
out vec4 Kd;
out vec4 Ks;
out vec4 La;
out vec4 Ld;
out vec4 Ls;
out float a;

void main() {
  gl_Position = P * V * M * vec4(in_position, 1.0);
  uv= texcoord;

  Ka = Ambient_reflectivity;
  Kd = Diffuse_reflectivity;
  Ks = Specular_reflectivity;
  La = Ambient_intensity;
  Ld = Diffuse_intensity;
  Ls = Specular_intensity;
  a  =  gloss;
  normal = (Transpose_Inverse_M * vec4(in_normal,0.0f)).xyz;
  vertex_to_light =  LightPos - ( M * vec4(in_position, 1.0f)).xyz;
  
  vertex_to_camera = CamPos - ( M * vec4(in_position, 1.0f)).xyz;
}