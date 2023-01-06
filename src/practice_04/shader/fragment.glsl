#version 330 core

layout (location = 1) in vec4 icolor;
out vec4 FragColor;
uniform vec4 vColor;
void main(){
    FragColor = vec4(icolor.x + vColor.x, icolor.y + vColor.y, icolor.z + vColor.z, icolor.w + vColor.w);
}