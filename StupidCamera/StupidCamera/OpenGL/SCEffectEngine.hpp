//
//  SCEffectEngine.hpp
//
//  Created by rayyyhuang on 2021/6/30.
//

#ifndef SCEffectEngine_hpp
#define SCEffectEngine_hpp

#include <vector>
#include "FaceData.hpp"
#include "LutFilter.hpp"
#include "SmallHeadFilter.hpp"
#include "SmoothFilter.hpp"
#include "SharpenFilter.hpp"
#include "FacePointFilter.hpp"
#include "BackgroundLineFilter.hpp"

namespace effect {

class SCEffectEngine {
public:
    SCEffectEngine();
    ~SCEffectEngine();
    
    /// 初始化，必须在GL线程
    void init();
    
    /// 释放资源，必须在GL线程
    void release();
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    void resize(int width, int height);
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    void setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer);
    
    /// 渲染，必须在GL线程
    /// @return 结果FrameBuffer
    std::shared_ptr<FrameBuffer> render();
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer);
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    void setFaceData(std::shared_ptr<FaceData> faceData);
    
    /// 设置各种参数
    /// @param params 参数，key为滤镜的名称，value是一整个map，是给这个滤镜具体的参数。
    void setParams(const std::map<std::string, std::map<std::string, std::string> > &params);
    
private:
    std::shared_ptr<FaceData> faceData;
    std::vector<std::shared_ptr<BaseFilter>> currentFilters;
    std::shared_ptr<LutFilter> lutFilter;
    std::shared_ptr<SmallHeadFilter> smallHeadFilter;
    std::shared_ptr<SmoothFilter> smoothFilter;
    std::shared_ptr<SharpenFilter> sharpenFilter;
    std::shared_ptr<FacePointFilter> facePointFilter;
    std::shared_ptr<BackgroundLineFilter> lineFilter;
};

}

#endif /* SCEffectEngine_hpp */
