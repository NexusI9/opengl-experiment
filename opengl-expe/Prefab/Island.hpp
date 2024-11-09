//
//  Island.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#ifndef Island_hpp
#define Island_hpp

#include <stdio.h>
#include <vector>
#include "./Chunk.hpp"


class Island{
  
public:
    
    Island() = default;
    ~Island(){};
    
private:
    
    std::vector<Chunk> chunks;
    Chunk spawnChunk();
    
    
};

#endif /* Island_hpp */
