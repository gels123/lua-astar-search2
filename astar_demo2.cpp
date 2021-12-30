#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "astar.h"
#include "mapSearch.h"

int main(void)
{
    MapSearch *ms = new MapSearch();
    ms->Init(1, 128, NULL);
    printf("=================\n");

    ms->FindPath(0, 0, 127, 127);
	
	return 0;
}
