#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex;
in vec2 TexCoord;
uniform bool HaveLighting;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 objectColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir  = normalize(viewPos - FragPos);

    vec3 finalColor;
    float finalAlpha;

    vec4 texColor = texture(tex, TexCoord);

    if (HaveLighting) {
        vec3 ambient = 0.3 * vec3(objectColor);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = 1.0 * diff * vec3(objectColor);

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
        vec3 specular = vec3(1.0) * spec;

        finalColor = (ambient + diffuse + specular) * texColor.rgb;
        finalAlpha = texColor.a * objectColor.a;
    }
    else {
        finalColor = objectColor.rgb * texColor.rgb;
        finalAlpha = texColor.a * objectColor.a;
    }

    FragColor = vec4(finalColor, finalAlpha);
}
