//
//  SCFilterDrawAlpha.hpp
//
//  Created by rayyy on 2021/6/21.
//

#ifndef SCFilterDrawAlpha_hpp
#define SCFilterDrawAlpha_hpp

#include "SCFilterBase.hpp"

// 画出Alpha通道
class SCFilterDrawAlpha : public SCFilterBase {
public:
    SCFilterDrawAlpha();
    ~SCFilterDrawAlpha();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() override;
};

#endif /* SCFilterDrawAlpha_hpp */
