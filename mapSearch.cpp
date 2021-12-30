//
//  mapSearch.cpp
//
//  Created by GeLiusheng on 2021/12/28.
//  Copyright © 2021年 Liusheng Ge. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mapSearch.h"

#define MARK 0xEE

using namespace alg;

MapSearch::MapSearch()
{
    // printf("MapSearch::MapSearch()\n");
    m_mapType = 0;
    m_mapSize = 0;
    memset(m_mapFile, '\0', sizeof(m_mapFile));
    p_mapGrid = NULL;
    p_astar = NULL;
}

MapSearch::~MapSearch()
{
    // printf("MapSearch::~MapSearch()\n");
    if(p_mapGrid != NULL) {
        delete p_mapGrid;
    }
}

int MapSearch::testFun(int a, int b)
{
    printf("MapSearch::testFun a=%d, b=%d\n", a, b);
    return a + b;
}

int MapSearch::Init(unsigned int mapType, unsigned int mapSize, const char *mapFile)
{
    if(mapType <= 0 || mapSize <= 0) {
        printf("MapSearch::Init error: mapType=%d, mapSize=%d, mapFile=%p\n", mapType, mapSize, mapFile);
        return 0;
    }
    srand(time(NULL));

    m_mapType = mapType;
    m_mapSize = mapSize;

    if(p_mapGrid != NULL) {
        delete p_mapGrid;
        p_mapGrid = NULL;
    }
    p_mapGrid = new Array2D<unsigned char>(mapSize, mapSize);
    p_mapGrid->clear(0);
	
    if(mapFile == NULL) {
        for	(unsigned int i = mapSize/4; i <= 3*mapSize/4; i++) {
            (*p_mapGrid)(3*mapSize/4,i) = AStar::WALL;
            (*p_mapGrid)(i,3*mapSize/4) = AStar::WALL;
        }

        printf("MapSearch::Init print map\n");
        for	(unsigned int i=0; i<mapSize;i++) {
            for(unsigned int j=0; j<mapSize;j++){
                if ((*p_mapGrid)(i,j) == AStar::WALL) {
                    printf("%c", AStar::WALL);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    } else {
        strncpy(m_mapFile, mapFile, sizeof(m_mapFile)-1);
    }

    p_astar = new AStar(*p_mapGrid);

    return 1;
}

Path* MapSearch::FindPath(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    // printf("MapSearch::FindPath x1=%d, y1=%d, x2=%d, y2=%d\n", x1, y1, x2, y2);
    if(!(x1 < m_mapSize && y1 < m_mapSize && x2 < m_mapSize && y2 < m_mapSize)) {
        return NULL;
    }
	Path* ptr = p_astar->run(x1, y1, x2, y2);
    // if(true) {
    //     printf("MapSearch::FindPath finish\n");
    //     Pos *tmpps = ptr->ps;
    //     for(int i=0;i<ptr->count;i++){
    //         printf("(%d,%d)\t", tmpps->x, tmpps->y);
    //         (*p_mapGrid)(tmpps->x, tmpps->y) = MARK;
    //         ++tmpps;
    //     }
    //     printf("\n");
    //     for	(unsigned int i=0;i<m_mapSize;i++) {
    //         for(unsigned int j=0;j<m_mapSize;j++) {
    //             if ((*p_mapGrid)(i,j) == AStar::WALL) {
    //                 printf("%c", AStar::WALL);
    //             } else if ((*p_mapGrid)(i,j) == MARK) {
    //                 printf("@");
    //                 (*p_mapGrid)(i,j) = 0;
    //             } else {
    //                 printf(".");
    //             }
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
    return ptr;
}