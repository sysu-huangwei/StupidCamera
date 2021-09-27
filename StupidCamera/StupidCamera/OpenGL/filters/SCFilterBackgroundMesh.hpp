//
//  SCFilterBackgroundMesh.hpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#ifndef SCFilterBackgroundMesh_hpp
#define SCFilterBackgroundMesh_hpp

#include "FilterChain.hpp"
#include "BaseDefine.h"

namespace effect {

/// 画背景+三角网格的滤镜
class SCFilterBackgroundMesh : public FilterChain {
public:
    
    SCFilterBackgroundMesh();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_BackgroundMesh; }
    
    /// 设置需要画的网格，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param mesh 点位信息
    /// @param meshStd 标准点位信息
    /// @param meshIndex 下标索引数组
    /// @param indexArrayCount meshIndex数组长度
    virtual void setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount);
    
};

}

#endif /* SCFilterBackgroundMesh_hpp */
