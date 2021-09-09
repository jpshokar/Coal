#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TC;

uniform sampler2D ST;
void main()
{
    
    BrightColor = texture(ST,TC);
    
    
}   