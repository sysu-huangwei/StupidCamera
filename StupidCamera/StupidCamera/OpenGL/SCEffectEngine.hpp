//
//  SCEffectEngine.hpp
//
//  Created by rayyy on 2021/6/30.
//

#ifndef SCEffectEngine_hpp
#define SCEffectEngine_hpp

#include "SCFaceData.hpp"
#include "SCFilterLut.hpp"
#include "SCFilterSmallHead.hpp"

class SCEffectEngine {
public:
    SCEffectEngine();
    ~SCEffectEngine();
    
    /// 初始化，必须在GL线程
    void init();
    
    /// 释放资源，必须在GL线程
    void release();
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    void resize(int width, int height);
    
    /// 设置输入图像的纹理ID
    /// @param srcTextureID 输入图像的纹理ID
    void setSrcTextureID(unsigned srcTextureID);
    
    /// 渲染，必须在GL线程
    /// @return 结果FrameBuffer
    FrameBuffer *render();
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    void setFaceData(SCFaceData *faceData);
    
    /// 替换Lut图，切换滤镜用
    /// @param path LUT图的路径
    void replaceLutImagePath(const char *path);
    
    void setLutDegree(float degree);
    
    void setSmallHeadDegree(float degree);
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    void renderToFrameBuffer(FrameBuffer *outputFrameBuffer);
    
private:
    SCFaceData *faceData;
    SCFilterLut *lutFilter;
    SCFilterSmallHead *smallHeadFilter;
};

#endif /* SCEffectEngine_hpp */
