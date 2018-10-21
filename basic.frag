#version 410 core
out vec4 FragColor;

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    bool isOn;
};

uniform PointLight pointLight;
uniform int materialDiffuse = 1;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D texture0;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec2 coords, vec3 texRgb);

void main()
{
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = texture(texture0, TexCoord) * vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec2 coords, vec3 texRgb)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = light.ambient * texture(texture0, TexCoord).rgb;
    vec3 diffuse = light.diffuse * diff * texture(texture0, TexCoord).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    return (ambient + diffuse);
}
