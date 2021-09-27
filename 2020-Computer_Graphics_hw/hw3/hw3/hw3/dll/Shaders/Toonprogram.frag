#version 430

uniform sampler2D texture;

in vec2 uv;

in vec3 normal;
in vec3 vertex_to_light;
in vec4 Kd;

out vec4 color;

void main()
{
    vec4 object_color = texture2D(texture, uv);
    vec3 n = normalize(normal);
    vec3 vl = normalize(vertex_to_light);

    float intensity = 1;
    float level = max(dot(vl,n),0);

    if(level > 0.95) intensity = 1;
    else if(level>0.75) intensity = 0.8;
    else if(level>0.50) intensity = 0.6;
    else if(level>0.25) intensity = 0.4;
    else intensity = 0.2;


    color = Kd * object_color * intensity ;
} 