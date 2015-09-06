//
//  GameHelper.h
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#ifndef __KOF__GameHelper__
#define __KOF__GameHelper__

#include <stdio.h>

class GameHelper{
    
public:
    static std::vector<std::string> split(std::string, char);
    static std::string randomString(size_t);
    
};
#endif /* defined(__KOF__GameHelper__) */
