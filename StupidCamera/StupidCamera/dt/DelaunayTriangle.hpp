//
//  DelaunayTriangle.hpp
//
//  Created by rayyy on 2021/4/20.
//

#ifndef DelaunayTriangle_hpp
#define DelaunayTriangle_hpp

class DelaunayTriangle {
public:
    
    /// 三角剖分算法
    /// @param points 输入点，归一化，0~1
    /// @param pointsCount 点的数量
    /// @param trianglesCountOutput 输出三角形的数量
    /// @return 三角形的点【内存外部去delete】
    static float *getTriangles(float *points, int pointsCount, int& trianglesCountOutput);
};

#endif /* DelaunayTriangle_hpp */
