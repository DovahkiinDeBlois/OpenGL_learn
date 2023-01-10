#version 330 core
out vec4 FragColor;
in vec4 ourcolor;
in vec2 TexCoord;
// uniform vec4 vColor;
uniform sampler2D ourTextuer;

void main(){
    // FragColor = vec4(ourcolor.x, ourcolor.y+vColor.y, ourcolor.z, 1.0f);
    // FragColor = vec4(ourcolor.x, ourcolor.y, ourcolor.z, 1.0f);
    // FragColor = vec4(ourcolor);
    // FragColor = texture(ourTextuer, TexCoord) * vec4(ourcolor);
    FragColor = texture(ourTextuer, TexCoord);
}