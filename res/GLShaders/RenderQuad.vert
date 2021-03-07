#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 tangent;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;

out vec2 vUv;

//main
void main()
{
    vUv = uv;

    vec4 worldPos = vec4(position.xyz, 1.0);
    gl_Position = worldPos;
}