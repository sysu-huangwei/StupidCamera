//
//  SCFilterBaseTwoInput.hpp
//
//  Created by rayyy on 2021/8/20.
//

#ifndef SCFilterBaseTwoInput_hpp
#define SCFilterBaseTwoInput_hpp

#include "SCFilterBase.hpp"

namespace effect {

/// 双输入滤镜
class SCFilterBaseTwoInput : public SCFilterBase {
public:
    
    /// 设置第二输入图像的FBO
    /// @param secondInputFrameBuffer 第二输入图像的FBO
    virtual void setSecondInputFrameBuffer(std::shared_ptr<FrameBuffer> secondInputFrameBuffer);
    
protected:
    
    std::shared_ptr<FrameBuffer> secondInputFrameBuffer = nullptr;

};

}

#endif /* SCFilterBaseTwoInput_hpp */
