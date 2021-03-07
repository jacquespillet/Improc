#version 440
//output
layout(location = 0) out vec4 outputColor; 
//main


in vec2 vUv;

uniform sampler2D mainTexture;

void main()
{
    outputColor = texture2D(mainTexture, vUv);
}