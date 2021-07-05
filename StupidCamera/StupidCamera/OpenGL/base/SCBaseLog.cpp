//
// Created by rayyy on 2020/4/20.
//

#include "SCBaseLog.h"

static int sBaseLogLevel = BASE_LOG_LEVEL_ALL;

void BASE_SetLogLevel(int level) {
    sBaseLogLevel = level;
}

int BASE_GetLogLevel() {
    return sBaseLogLevel;
}
