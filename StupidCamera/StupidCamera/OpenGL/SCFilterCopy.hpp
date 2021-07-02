//
//  SCFilterCopy.hpp
//
//  Created by rayyy on 2020/11/26.
//

#ifndef SCFilterCopy_hpp
#define SCFilterCopy_hpp

#include "SCFilterBase.hpp"

/// 画原图的滤镜
class SCFilterCopy : public SCFilterBase {
public:
    SCFilterCopy();
    ~SCFilterCopy();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() override;
    
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;

};

#endif /* SCFilterCopy_hpp */
