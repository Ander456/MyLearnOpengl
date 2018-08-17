#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}

//// 玻璃效果
//void main()
//{
//    float ratio = 1.00 / 1.52;
//    vec3 I = normalize(Position - cameraPos);
//    vec3 R = refract(I, normalize(Normal), ratio);
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);
//}
