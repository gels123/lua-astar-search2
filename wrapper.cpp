#include <stdio.h>
#include "wrapper.h"
#include "mapSearch.h"
 
using namespace alg;

#ifdef __cplusplus
extern "C" {
#endif

//create a MapSearch instance
void* create()
{
	MapSearch *p = new MapSearch();
	printf("wrapper.cp::create p=%p\n", (void*)p);
	return (void*) p;
}

void release(void *pms)
{
	if(pms == NULL) {
		printf("wrapper.cpp::release error: pms == 0");
		return;
	}
	MapSearch *p = (MapSearch *) pms;
	delete p;
}

// testFun function
int testFun(void *pms, int a, int b)
{	
	if(pms == NULL) {
		printf("wrapper.cpp::testFun error: pms == 0");
		return 0;
	}
	MapSearch *p = (MapSearch *) pms;
	if(p == NULL) {
		printf("wrapper.cpp::init error: p == 0");
		return 0;
	}
	printf("wrapper.cpp::testFun p=%p a=%d b=%d\n", (void*)p, a, b);
    return p->testFun(a, b);
}

int init(void *pms, unsigned int mapType, unsigned int mapSize, const char *mapFile)
{
	if(pms == NULL) {
		printf("wrapper.cpp::init error1: pms == 0");
		return 0;
	}
	MapSearch *p = (MapSearch *) pms;
	if(p == NULL) {
		printf("wrapper.cpp::init error2: p == 0");
		return 0;
	}
	return p->Init(mapType, mapSize, mapFile);
}

Path* findPath(void *pms, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	if(pms == NULL) {
		printf("wrapper.cpp::init error1: pms == 0");
		return NULL;
	}
	MapSearch *p = (MapSearch *) pms;
	if(p == NULL) {
		printf("wrapper.cpp::init error2: p == 0");
		return NULL;
	}
	return p->FindPath(x1, y1, x2, y2);
}

#ifdef __cplusplus
}
#endif
