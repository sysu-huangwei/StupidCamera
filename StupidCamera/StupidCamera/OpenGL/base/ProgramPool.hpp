//
//  ProgramPool.hpp
//
//  Created by rayyy on 2021/7/5.
//

#ifndef ProgramPool_hpp
#define ProgramPool_hpp

#include <map>
#include "Program.hpp"

class ProgramPool {
public:
    
    static std::shared_ptr<ProgramPool> getSharedInstance();
    
    Program* fetchProgramFromPool(std::string vertexSource, std::string fragmentSource);
    
    void clearProgramFromPool();
    
private:
    
    std::map<std::string, Program *> programCache;
};

#endif /* ProgramPool_hpp */
