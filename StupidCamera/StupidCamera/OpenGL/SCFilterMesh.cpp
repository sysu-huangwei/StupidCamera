//
//  SCFilterMesh.cpp
//
//  Created by rayyy on 2021/4/22.
//

#include "SCFilterMesh.hpp"
#include <string.h>

const char *kSCFilterMeshVertexShaderString = SHADER_STRING_CPP
(
 attribute vec2 a_position;
 attribute vec2 a_texCoord;
 varying vec2 texcoordOut;
 
 void main()
 {
    texcoordOut = a_position;
    gl_Position = vec4(a_position * 2.0 - 1.0, 0.0, 1.0);
 }
);

const char *kSCFilterMeshFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D  u_texture;
 varying vec2 texcoordOut;
 void main()
 {
    vec4 srcColor = texture2D(u_texture,texcoordOut);
    gl_FragColor = vec4(1,0,0,1);//srcColor;
 }
);

SCFilterMesh::SCFilterMesh():SCFilterBase() {
    
}

SCFilterMesh::~SCFilterMesh() {
    if (this->mesh) {
        delete [] this->mesh;
        this->mesh = nullptr;
    }
    if (this->meshIndex) {
        delete [] this->meshIndex;
        this->meshIndex = nullptr;
    }
}

void SCFilterMesh::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterMeshVertexShaderString, kSCFilterMeshFragmentShaderString);
    positionAttribute = glGetAttribLocation(programID, "a_position");
    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

unsigned SCFilterMesh::render() {
    if (!this->mesh) {
        return isRenderToOutside ? textureIDOutside : srcTextureID;
    }
    
    if (isRenderToOutside) {
        glBindFramebuffer(GL_FRAMEBUFFER, fboIDOutside);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureIDOutside, 0);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    }
    
    glViewport(0, 0, width, height);
    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, mesh);
    
    glEnableVertexAttribArray(textureCoordinateAttribute);
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawElements(GL_TRIANGLES, indexArrayCount, GL_UNSIGNED_INT, (void *)meshIndex);
    
    afterDraw();
    return SCFilterBase::render();
}


void SCFilterMesh::setMesh(float *mesh, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    if (meshArrayCount != this->meshArrayCount) {
        if (this->mesh) {
            delete [] this->mesh;
            this->mesh = nullptr;
        }
        this->meshArrayCount = meshArrayCount;
        this->mesh = new float[meshArrayCount];
    }
    if (indexArrayCount != this->indexArrayCount) {
        if (this->meshIndex) {
            delete [] this->meshIndex;
            this->meshIndex = nullptr;
        }
        this->indexArrayCount = indexArrayCount;
        this->meshIndex = new unsigned int[indexArrayCount];
    }
    if (mesh && meshArrayCount > 0) {
        memcpy(this->mesh, mesh, sizeof(float) * meshArrayCount);
    }
    if (meshIndex && meshArrayCount > 0) {
        memcpy(this->meshIndex, meshIndex, sizeof(unsigned int) * indexArrayCount);
    }
}
