//
//  ProgramPool.cpp
//
//  Created by rayyyhuang on 2021/7/5.
//

#include "ProgramPool.hpp"
#include <mutex>
#include "SCBaseDefine.h"

static std::shared_ptr<ProgramPool> programPoolSharedInstance;
static std::mutex programPoolSharedInstanceLock;

std::shared_ptr<ProgramPool> ProgramPool::getSharedInstance() {
    if (programPoolSharedInstance == nullptr) {
        std::lock_guard<std::mutex> lock(programPoolSharedInstanceLock);
        if (programPoolSharedInstance == nullptr) {
            programPoolSharedInstance = std::make_shared<ProgramPool>();
        }
    }
    return programPoolSharedInstance;
}

Program* ProgramPool::fetchProgramFromPool(std::string vertexSource, std::string fragmentSource) {
    std::string key = vertexSource + "_" + fragmentSource;
    if (programCache.find(key) != programCache.end()) {
        return programCache.at(key);
    } else {
        Program *program = new Program();
        program->init(vertexSource, fragmentSource);
        programCache[key] = program;
        return program;
    }
}

void ProgramPool::clearProgramFromPool() {
    std::map<std::string, Program *>::iterator it;
    for (it = programCache.begin(); it != programCache.end(); it++) {
        (*it).second->release();
        SAFE_DELETE((*it).second);
    }
    programCache.clear();
}
