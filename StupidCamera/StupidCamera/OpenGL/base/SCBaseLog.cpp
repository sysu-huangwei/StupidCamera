//
// Created by rayyyhuang on 2020/4/20.
//

#include "SCBaseLog.h"

static int sBaseLogLevel = BASE_LOG_LEVEL_ALL;

void setBaseLogLevel(int level) {
    sBaseLogLevel = level;
}

int getBaseLogLevel() {
    return sBaseLogLevel;
}
