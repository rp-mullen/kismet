#vertex
#version 330 core

layout (location = 0) in vec3 aPos;  // Vertex position
layout (location = 1) in vec3 aNormal;  // Vertex normal
layout (location = 2) in vec2 aTexCoords;  // Texture coordinates

out vec3 FragPos;  
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

#fragment
#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // Simple diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3)); // Directional light source
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Final color
    vec3 result = (diffuse + 0.2) * objectColor; // Ambient + Diffuse
    FragColor = vec4(result, 1.0);
}
