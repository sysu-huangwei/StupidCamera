//
//  SCFilterMesh.hpp
//
//  Created by rayyy on 2021/4/22.
//

#ifndef SCFilterMesh_hpp
#define SCFilterMesh_hpp

#include "SCFilterBase.hpp"

/// 画三角网格的滤镜
class SCFilterMesh : public SCFilterBase {
public:
    SCFilterMesh();
    ~SCFilterMesh();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() override;
    
    /// 设置需要画的网格，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param mesh 点位信息，{x1, y1, x2, y2……}
    /// @param meshStd 标准点位信息，{x1, y1, x2, y2……}
    /// @param meshArrayCount mesh数组长度
    /// @param meshIndex 下标索引数组
    /// @param indexArrayCount meshIndex数组长度
    void setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount);
    
protected:
    int positionStdAttribute = -1;
    float *mesh = nullptr;
    float *meshStd = nullptr;
    int meshArrayCount = 0;
    unsigned int *meshIndex = nullptr;
    int indexArrayCount = 0;
};

#endif /* SCFilterMesh_hpp */
