#version 430

uniform sampler2D texture;

in vec2 uv;

in vec3 normal;
in vec3 vertex_to_light;
in vec3 vertex_to_camera;

in vec4 Ka;
in vec4 Kd;
in vec4 Ks;
in vec4 La;
in vec4 Ld;
in vec4 Ls;
in float a;

out vec4 color;

void main()
{
    vec4 object_color = texture2D(texture, uv);
    vec3 n = normalize(normal);
    vec3 vl = normalize(vertex_to_light);
    vec3 vc = normalize(vertex_to_camera);

    vec3 reflect_vector = ( 2 * max(dot(vl,n),0) * n) - vl;
    
    vec4 Ambient = Ka * La * object_color;
    vec4 Diffuse = Kd * Ld  * object_color * max(dot(vl,n),0);
    vec4 Specular = Ks * Ls  * pow(max(dot(vc,reflect_vector),0),a);

    color = Ambient + Diffuse + Specular;
} 