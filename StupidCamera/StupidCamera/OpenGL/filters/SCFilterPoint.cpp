//
//  SCFilterPoint.cpp
//
//  Created by rayyyhuang on 2021/4/16.
//

#include "SCFilterPoint.hpp"
#include <string.h>
#include "DelaunayTriangle.hpp"

namespace effect {

SCFilterPoint::~SCFilterPoint() {
    SAFE_DELETE_ARRAY(this->points);
}

void SCFilterPoint::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("point", "point");
}

void SCFilterPoint::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        outputFrameBuffer->activeFrameBuffer();
        
        program->use();
        
        program->setVertexAttribPointer("a_position", points);
        
        glDrawArrays(GL_POINTS, 0, pointsCount);
        
        glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    }
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
}


void SCFilterPoint::setPoints(std::vector<BasePoint> points) {
    if ((int)points.size() != pointsCount) {
        SAFE_DELETE_ARRAY(this->points);
        this->pointsCount = (int)points.size();
        this->points = new float[points.size() * 2];
    }
    if (pointsCount > 0) {
        memcpy(this->points, &points[0], sizeof(BasePoint) * points.size());
    }
}

bool SCFilterPoint::isNeedRender() {
    return points && pointsCount > 0 && enableRender;
}

}
