//
//  SCFilterMesh.cpp
//
//  Created by rayyy on 2021/4/22.
//

#include "SCFilterMesh.hpp"
#include <string.h>

const char *kSCFilterMeshVertexShaderString = SHADER_STRING_CPP
(
 attribute highp vec2 a_position;
 attribute highp vec2 a_position_std;
 varying highp vec2 texcoordOut;
 
 void main()
 {
    texcoordOut = a_position_std;
    gl_Position = vec4(a_position * 2.0 - 1.0, 0.0, 1.0);
 }
);

const char *kSCFilterMeshFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D  u_texture;
 varying highp vec2 texcoordOut;
 void main()
 {
    vec4 srcColor = texture2D(u_texture,texcoordOut);
    gl_FragColor = srcColor;
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
    positionStdAttribute = glGetAttribLocation(programID, "a_position_std");
    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

FrameBuffer *SCFilterMesh::render() {
    if (!this->mesh) {
        return frameBuffer;
    }

    frameBuffer->activeFrameBuffer();
    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, mesh);
    
    glEnableVertexAttribArray(positionStdAttribute);
    glVertexAttribPointer(positionStdAttribute, 2, GL_FLOAT, false, 0, meshStd);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawElements(GL_TRIANGLES, indexArrayCount, GL_UNSIGNED_INT, (void *)meshIndex);
    
    afterDraw();
    return SCFilterBase::render();
}

void SCFilterMesh::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    outputFrameBuffer->activeFrameBuffer();
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, mesh);
    
    glEnableVertexAttribArray(positionStdAttribute);
    glVertexAttribPointer(positionStdAttribute, 2, GL_FLOAT, false, 0, meshStd);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawElements(GL_TRIANGLES, indexArrayCount, GL_UNSIGNED_INT, (void *)meshIndex);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void SCFilterMesh::setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    if (meshArrayCount != this->meshArrayCount) {
        if (this->mesh) {
            delete [] this->mesh;
            this->mesh = nullptr;
        }
        if (this->meshStd) {
            delete [] this->meshStd;
            this->meshStd = nullptr;
        }
        this->meshArrayCount = meshArrayCount;
        this->mesh = new float[meshArrayCount];
        this->meshStd = new float[meshArrayCount];
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
    if (meshStd && meshArrayCount > 0) {
        memcpy(this->meshStd, meshStd, sizeof(float) * meshArrayCount);
    }
    if (meshIndex && meshArrayCount > 0) {
        memcpy(this->meshIndex, meshIndex, sizeof(unsigned int) * indexArrayCount);
    }
}
