#version 430

uniform sampler2D texture;

in vec2 uv;

in vec3 normal;
in vec3 vertex_to_camera;
in vec4 bcolor;
in vec4 blcolor;

out vec4 color;

void main()
{
    vec3 n = normalize(normal);
    vec3 vc = normalize(vertex_to_camera);

    float CameraPercentage;
    CameraPercentage = max(dot(vc,n),0);
    if(CameraPercentage < 0.3){
        color = bcolor * (1 - CameraPercentage);
    }else{
        color = blcolor;
    }
} 