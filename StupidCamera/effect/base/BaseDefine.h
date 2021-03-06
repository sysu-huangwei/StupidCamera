//
// Created by rayyyhuang on 2020/4/20.
//

#ifndef BASEDEFINE_H
#define BASEDEFINE_H

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) delete (x); (x) = NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if (x) delete [] (x); (x) = NULL; }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}
#endif

typedef struct {
    float x;
    float y;
} BasePoint;

typedef struct {
    BasePoint p0;
    BasePoint p1;
} BaseLine;

typedef struct {
    BasePoint p0;
    BasePoint p1;
    BasePoint p2;
} BaseTriangle;

#endif //BASEDEFINE_H
