//
//  Program.hpp
//
//  Created by rayyy on 2021/7/5.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <map>
#include "SCBaseDefine.h"

#if PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif PLATFORM_IOS
#define GLES_SILENCE_DEPRECATION 1
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

class Program {
public:
    
    void init(std::string vertexSource, std::string fragmentSource);
    
    void release();
    
    void use();
    
    void setUniform1i(std::string name, int x);
    
    void setUniform1f(std::string name, float x);
    
    void setUniform2i(std::string name, int x, int y);
    
    void setUniform2f(std::string name, float x, float y);
    
private:
    
    GLuint compileShader(GLenum type, const char *shaderSource);
    
    GLuint createProgram(const char *vertexSource, const char *fragmentSource);
    
    GLint getUniformLocation(std:: string name);
    
    GLint getAttributeLocation(std:: string name);
    
    GLuint programID = 0;
    std::map<std::string, GLint> locationMap;
    
};

#endif /* Program_hpp */
