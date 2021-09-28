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
    
    /// 滤镜的类型
    std::string filterType() override { return SCFilterType_Smooth; }
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
};

}

#endif /* SCFilterSmooth_hpp */
