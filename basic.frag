#version 410 core
out vec4 FragColor;

//uniform PointLight pointLight;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 pointPosition;
uniform vec3 pointAmbient;
uniform vec3 pointDiffuse;
uniform float constant;
uniform float linear;
uniform float quadratic;
uniform bool isOn;

uniform sampler2D texture0;

void main()
{

    // ambient
     vec3 ambient = vec3(1.0,0.0,1.0);// * texture(texture0, TexCoord).rgb;
     vec3 pointPosition = vec3(0.0, 2.0, -7.0);

     // diffuse
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(pointPosition - FragPos);
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = pointDiffuse * diff;// * texture(texture0, TexCoord).rgb;

     // attenuation
     float distance  = length(pointPosition - FragPos);
     float attenuation = 1.0 / (distance*distance*0.05);//(constant + linear * distance + quadratic * (distance * distance));

     ambient  *= attenuation;
     diffuse   *= attenuation;


     vec3 result = (ambient + diffuse) * texture(texture0, TexCoord).rgb;
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
