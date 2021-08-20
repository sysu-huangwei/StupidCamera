attribute vec2 a_position;
attribute vec2 a_texCoord;
varying vec2 texcoordOut;
uniform vec2 offset;

varying vec2 texcoordOutNear[3];

void main()
{
    texcoordOut = a_texCoord;
    gl_Position = vec4(a_position, 0.0, 1.0);
    
    texcoordOutNear[0] = a_texCoord - offset;
    texcoordOutNear[1] = a_texCoord;
    texcoordOutNear[2] = a_texCoord + offset;
}
