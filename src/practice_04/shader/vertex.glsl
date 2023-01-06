#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 acolor;

out vec3 ourcolor;
uniform float offset;

void main(){
    // aPos.x = aPos.x+offset;
    // gl_Position = vec4(aPos, 1.0f);
    gl_Position = vec4(aPos.x + offset, aPos.y , aPos.z, 1.0f);
    // gl_Position = vec4(aPos.x, aPos.y , aPos.z, 1.0f);
    ourcolor = acolor;
    gl_PointSize = 20.0f;
}
