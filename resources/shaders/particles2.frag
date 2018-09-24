#version 450

layout(location = 0) in vec2 pos;
layout(location = 1) in float pointSize;
layout(location = 2) in vec3 color;

layout(location = 0) out vec4 oColor;

layout(push_constant) uniform PushConstants
{
    vec2 resolution;
};

void main()
{
    vec2 screenPos = pos * resolution;
    float radius = pointSize * .5;
    vec2 fragCoord = gl_FragCoord.xy;
    float d = length(fragCoord - screenPos)/radius;
    if (d >= 1.)
        discard; // Do not blend zeros
    float alpha = 1. - pow(d, 4.); // Adjust alpha smoothness
    oColor = vec4(color, alpha * 0.8);
}