#version 120

uniform highp vec3 lightPosition_wrld;
uniform highp vec3 color_mdl;

varying highp vec3 position_wrld;
varying highp vec3 normal_cmr;
varying highp vec3 eyeDirection_cmr;
varying highp vec3 lightDirection_cmr;

void main() {
    highp vec3 lightColor = vec3(1.0, 1.0, 1.0);
    highp float lightPower = 10.0;
    highp vec3 materialAmbientColor = vec3(0.5, 0.5, 0.5) * color_mdl;
    highp vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3) * color_mdl;

    highp float distance = length(lightPosition_wrld - position_wrld);

    highp vec3 n = normalize(normal_cmr);
    highp vec3 l = normalize(lightDirection_cmr);
    highp float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    highp vec3 E = normalize(eyeDirection_cmr);
    highp vec3 R = reflect(-l, n);
    highp float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

    gl_FragColor.rgb =
        materialAmbientColor +
        materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (distance * distance);
    gl_FragColor.a = 1.0;
}
