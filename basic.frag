#version 410 core
out vec4 FragColor;

//uniform PointLight pointLight;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 pointLightPos;
uniform bool isOn;
uniform float intensity;

uniform sampler2D texture0;

void main()
{
    // ambient
    //vec3 result = vec3(0.5, 0.5, 0.5) * texture(texture0, TexCoord).rgb;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor * texture(texture0, TexCoord).rgb;

    if (isOn) {
         vec3 ambient = vec3(0.0,1.0,1.0);
         vec3 pointDiffuse = vec3(0.0, 1.0, 1.0);

         // diffuse
         vec3 norm = normalize(Normal);
         vec3 lightDir = normalize(pointLightPos - FragPos);
         float diff = max(dot(norm, lightDir), 0.0);
         vec3 diffuse = pointDiffuse * diff;

         // attenuation
         float distance  = length(pointLightPos - FragPos);
         float attenuation = 1.0 / (distance*distance*0.05);

         ambient  *= attenuation*intensity;
         diffuse   *= attenuation*intensity;

         result += (ambient + diffuse) * texture(texture0, TexCoord).rgb;
     }
     FragColor = vec4(result, 1.0);


    ///
     /*
    float distance = length(position - FragPos);

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = ((ambient + diffuse) * objectColor);
    vec4 r = texture(texture0, TexCoord) * vec4(result, 1.0);
    //if (false) {
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        vec3 ambient2 = pointAmbient * vec3(texture(texture0, TexCoord));
        vec3 diffuse2 = pointDiffuse * diff * vec3(texture(texture0, TexCoord));
        ambient2 *= attenuation;
        diffuse2 *= attenuation;
        result = (ambient + diffuse);

    //}
    //
        FragColor = r * vec4(result, 1.0);

*/}
