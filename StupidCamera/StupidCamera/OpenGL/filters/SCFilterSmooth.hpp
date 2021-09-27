//
//  SCFilterSmooth.hpp
//
//  Created by Ray on 2021/8/22.
//

#ifndef SCFilterSmooth_hpp
#define SCFilterSmooth_hpp

#include "FilterChain.hpp"

namespace effect {

/// 模糊
class SCFilterSmooth : public FilterChain {
public:
    
    SCFilterSmooth();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Smooth; }
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    float alpha = 0.0f;
    
};

}

#endif /* SCFilterSmooth_hpp */
