//
//  SCBaseGLUtils.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCBaseGLUtils.hpp"
#include <stdio.h>

unsigned BaseGLUtils::loadShader(int shaderType, const char *source) {
  unsigned shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  int compiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (compiled != GL_TRUE) {
    int infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen) {
      char *buf = new char[infoLen];
      glGetShaderInfoLog(shader, infoLen, NULL, buf);
      LOGE("Error: Could not compile shader, shaderType = %d \n "
           "ShaderInfoLog = %s, shader = %s \n", shaderType, buf, source);
      delete[] buf;
    }
    glDeleteShader(shader);
    shader = 0;
  }
  return shader;
}

unsigned BaseGLUtils::createProgram(const char *vertexSource, const char *fragmentSource) {
  unsigned vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
  if (vertexShader == 0) {
    LOGE("ERROR in load vertex shader! ");
    return 0;
  }
  unsigned pixelShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
  if (pixelShader == 0) {
    LOGE("ERROR in load fragment shader!");
    glDeleteShader(vertexShader);
    return 0;
  }

  unsigned program = glCreateProgram();
  if (program) {
    glAttachShader(program, vertexShader);
    glAttachShader(program, pixelShader);
    glLinkProgram(program);
    int linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
      int bufLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
      if (bufLength) {
        char *buf = new char[bufLength];
        glGetProgramInfoLog(program, bufLength, NULL, buf);
        LOGE("Could not link program:\n%s", buf);
        delete[] buf;
      }
      glDeleteProgram(program);
      program = 0;
    }
  } else {
    LOGE("Error: Could not create program");
  }
  glDeleteShader(vertexShader);
  glDeleteShader(pixelShader);
  return program;
}

unsigned BaseGLUtils::createTexture(int target, int wrapMode, int filterMode) {
  unsigned texture;
  glGenTextures(1, &texture);
  if (texture != 0) {
    glBindTexture(target, texture);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filterMode);
  } else {
    LOGE("ERROR in createTexture!");
  }
  return texture;
}

unsigned BaseGLUtils::createTexture2D() {
  return createTexture(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR);
}

unsigned BaseGLUtils::createTexture2D(int width, int height) {
  int texture = createTexture2D();
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  return texture;
}

unsigned BaseGLUtils::createFBO(int texture, int width, int height) {
  unsigned frameBuffer;
  glGenFramebuffers(1, &frameBuffer);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, texture, 0);

  int fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
    LOGE("createFBO failed, status: %d", fboStatus);
  }

  return frameBuffer;
}
