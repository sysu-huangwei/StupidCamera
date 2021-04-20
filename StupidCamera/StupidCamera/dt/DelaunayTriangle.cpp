//
//  DelaunayTriangle.cpp
//
//  Created by rayyy on 2021/4/20.
//

#include "DelaunayTriangle.hpp"
#include <vector>
#include "delaunay.h"
using namespace std;
using namespace dt;

float *DelaunayTriangle::getTriangles(float *points, int pointsCount, int& trianglesCountOutput) {
    if (!points) {
        return nullptr;
    }
    
    Delaunay<float> instance;
    vector<Vector2<float>> vertices;
    
    for (int i = 0; i < pointsCount; i++) {
        vertices.push_back(Vector2<float>(points[2 * i], points[2 * i + 1]));
    }
    
    std::vector<Triangle<float>> triangles = instance.triangulate(vertices);
    
    trianglesCountOutput = (int)triangles.size();
    
    float *result = new float[triangles.size() * 6];
    for (int i = 0; i < triangles.size(); i++) {
        result[6 * i] = triangles[i].a->x;
        result[6 * i + 1] = triangles[i].a->y;
        result[6 * i + 2] = triangles[i].b->x;
        result[6 * i + 3] = triangles[i].b->y;
        result[6 * i + 4] = triangles[i].c->x;
        result[6 * i + 5] = triangles[i].c->y;
    }
    
    return result;
}
