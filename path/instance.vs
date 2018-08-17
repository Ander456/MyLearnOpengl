//#version 330 core
//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec3 aColor;
//
//out vec3 fColor;
//
//uniform vec2 offsets[100];
//
//void main()
//{
//    vec2 offset = offsets[gl_InstanceID];
//    gl_Position = vec4(aPos + offset, 0.0, 1.0);
//    fColor = aColor;
//}

//#version 330 core
//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aOffset;
//
//out vec3 fColor;
//
//void main()
//{
//    fColor = aColor;
//    gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
//}

//// 小星星 普通版
//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 2) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//
//uniform mat4 projection;
//uniform mat4 view;
//uniform mat4 model;
//
//void main()
//{
//    TexCoords = aTexCoords;
//    gl_Position = projection * view * model * vec4(aPos, 1.0f);
//}

// 小星星 实例化版 批量刷
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}

