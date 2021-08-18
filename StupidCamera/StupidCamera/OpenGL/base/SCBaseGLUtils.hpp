//
//  SCBaseGLUtils.hpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#ifndef SCBaseGLUtils_hpp
#define SCBaseGLUtils_hpp

#include "SCBaseDefine.h"
#include "SCBaseLog.h"

#if PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif PLATFORM_IOS
#define GLES_SILENCE_DEPRECATION 1
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif



class BaseGLUtils {
public:

 /**
  * 根据指定的着色器类型和脚本生成着色器。
  *
  * @param shaderType 着色器类型
  * @param source 着色器脚本
  * @return 着色器
  */
 static unsigned loadShader(int shaderType, const char *source);

 /**
  * 根据指定的着色器脚本创建着色器程序。
  *
  * @param vertexSource 顶点着色器脚本
  * @param fragmentSource 片段着色器脚本
  * @return 着色器程序
  */
 static unsigned createProgram(const char *vertexSource, const char *fragmentSource);

 /**
  * 根据指定的参数创建纹理。
  *
  * @param target 纹理类型
  * @param wrapMode 纹理环绕方式
  * @param filterMode 纹理过滤方式
  * @return 要创建的纹理
  */
 static unsigned createTexture(int target, int wrapMode, int filterMode);

 /**
  * 创建 2D 纹理
  * @return 要创建的纹理
  */
 static unsigned createTexture2D();

 /**
  * 创建 2D 纹理
  *
  * @param width 宽
  * @param height 高
  * @return 要创建的纹理
  */
 static unsigned createTexture2D(int width, int height);

 /**
  * 创建 FBO
  * @param texture 要绑定这个fbo的纹理
  * @return 要创建的FBO
  */
 static unsigned createFBO(int texture, int width, int height);
    
 static unsigned char *LoadImage_File(const char *filePath, int *hidth, int *height);
    
 static GLuint LoadTexture_File(const char *filePath, int *outWidth, int *outHeight);
    
};




#endif /* SCBaseGLUtils_hpp */
