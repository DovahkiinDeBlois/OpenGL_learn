#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 acolor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourcolor;
out vec2 TexCoord;
uniform float offsetx;
uniform float offsety;

// 旋转
uniform mat4 transform;

void main(){
    // aPos.x = aPos.x+offset;
    // gl_Position = mat4(2.0) * vec4(aPos, 1.0f);
    // float radian = radians(30.0);
    // float cos = cos(radian);
    // float sin = sin(radian);
    // mat4 mx = mat4(
    //     1.0,  0.0,  0.0,  0.0,
    //     0.0,  cos,  -sin, 0.0,
    //     0.0,  sin,  cos, 0.0,
    //     0.0, 0.0, 0.0, 1.0
    // );

    // mat4 my = mat4(
    //     cos,  0.0,  -sin, 0.0,
    //     0.0,  1.0,  0.0,  0.0,
    //     sin,  0.0,  cos, 0.0,
    //     0.0, 0.0, 0.0, 1.0
    // );

    // gl_Position = mx * my vec4(aPos, 1.0f);
    gl_Position = transform * vec4(aPos, 1.0f);
    // gl_Position = vec4(aPos.x + offsetx, aPos.y + offsety , aPos.z, 1.0f);
    // gl_Position = vec4(aPos.x, aPos.y , aPos.z, 1.0f);
    ourcolor = acolor;
    // TexCoord = aTexCoord;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    gl_PointSize = 20.0f;
}
