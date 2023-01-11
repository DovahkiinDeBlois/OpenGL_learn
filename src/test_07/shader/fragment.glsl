#version 330 core
out vec4 FragColor;
in vec4 ourcolor;
in vec2 TexCoord;
// uniform vec4 vColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;

void main(){
    // FragColor = vec4(ourcolor.x, ourcolor.y+vColor.y, ourcolor.z, 1.0f);
    // FragColor = vec4(ourcolor.x, ourcolor.y, ourcolor.z, 1.0f);
    // FragColor = vec4(ourcolor);
    // FragColor = texture(texture1, TexCoord) * vec4(ourcolor);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y * -1)), alpha) * vec4(ourcolor);
    // FragColor = texture(texture2, TexCoord) * vec4(ourcolor);
    // FragColor = texture(ourTextuer, TexCoord);
}