//
//  SCEffectEngine.hpp
//
//  Created by rayyyhuang on 2021/6/30.
//

#ifndef SCEffectEngine_hpp
#define SCEffectEngine_hpp

#include <vector>
#include "SCFaceData.hpp"
#include "SCFilterLut.hpp"
#include "SCFilterSmallHead.hpp"
#include "SCFilterSmooth.hpp"
#include "SCFilterSharpenUSM.hpp"

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
    void setFaceData(SCFaceData *faceData);
    
    /// 设置各种参数
    /// @param params 参数，key为滤镜的名称，value是一整个map，是给这个滤镜具体的参数。
    void setParams(const std::map<std::string, std::map<std::string, std::string> > &params);
    
private:
    SCFaceData *faceData;
    std::vector<SCFilterBase *> currentFilters;
    SCFilterLut *lutFilter;
    SCFilterSmallHead *smallHeadFilter;
    SCFilterSmooth *smoothFilter;
    SCFilterSharpenUSM *sharpenFilter;
};

}

#endif /* SCEffectEngine_hpp */
