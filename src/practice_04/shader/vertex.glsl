#version 330 core 
layout (location = 0) in vec3 aPos;
uniform float offset;

void main(){
    gl_Position = vec4(0.5 + offset, -0.5 , -0.5 , 1.0f);
    gl_PointSize = 20.0f;
}
