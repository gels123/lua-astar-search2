//
//  mapSearch.cpp
//
//  Created by GeLiusheng on 2021/12/28.
//  Copyright © 2021年 Liusheng Ge. All rights reserved.
//

#ifndef mapSearch_h
#define mapSearch_h

#include <stdio.h>
#include "astar.h"
#include "lua-mapSearch.h"

using namespace alg;

class MapSearch
{
public:
    int testFun(int a, int b);

public:
    MapSearch();
    ~MapSearch();

    int Init(unsigned int mapType, unsigned int mapSize, const char *mapFile = NULL);
    Path* FindPath(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

private:
    unsigned int m_mapType;
    unsigned int m_mapSize;
    char m_mapFile[128];
    Array2D<unsigned char> *p_mapGrid;
    AStar *p_astar;
};

#endif /* mapSearch_h */
