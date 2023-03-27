#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 acolor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourcolor;
out vec2 TexCoord;
uniform float offsetx;
uniform float offsety;

void main(){
    // aPos.x = aPos.x+offset;
    gl_Position = vec4(aPos, 1.0f);
    // gl_Position = vec4(aPos.x + offsetx, aPos.y + offsety , aPos.z, 1.0f);
    // gl_Position = vec4(aPos.x, aPos.y , aPos.z, 1.0f);
    ourcolor = acolor;
    TexCoord = aTexCoord;
    gl_PointSize = 20.0f;
}
