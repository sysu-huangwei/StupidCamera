//
// Created by rayyyhuang on 2020/4/20.
//

#ifndef SCBASEDEFINE_H
#define SCBASEDEFINE_H

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) delete (x); (x) = nullptr; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if (x) delete [] (x); (x) = nullptr; }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p) if(p != NULL) {free(p); p = nullptr;}
#endif

//链接字符串的宏定义
#define STRINGIZE(x) #x
#define STRINGIZE2(x) STRINGIZE(x)
#define SHADER_STRING_CPP(text) STRINGIZE2(text)

typedef struct {
    float x;
    float y;
} SCPoint;

typedef struct {
    SCPoint p0;
    SCPoint p1;
} SCLine;

typedef struct {
    SCPoint p0;
    SCPoint p1;
    SCPoint p2;
} SCTriangle;

#endif //SCBASEDEFINE_H
