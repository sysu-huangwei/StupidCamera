precision highp float;

uniform sampler2D u_texture;
varying vec2 texcoordOut;
varying vec2 texcoordOutNear[3];

void main()
{
    vec4 srcColor = texture2D(u_texture, texcoordOut);
    
    vec4 sum = vec4(0.0);
    sum += texture2D(u_texture, texcoordOutNear[0]);
    sum += texture2D(u_texture, texcoordOutNear[1]);
    sum += texture2D(u_texture, texcoordOutNear[2]);
    sum *= 0.3333333;
    
    gl_FragColor = vec4(sum.rgb, srcColor.a);
}
