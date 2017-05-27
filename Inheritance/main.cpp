#include <dlfcn.h>

#include <iostream>
#include <cstdio>
#include <typeinfo>

#include "SingleInherit.h"
#include "MulInherit.h"
#include "DiamondInherit.h"

using namespace std;

typedef void(*Fun)();

#define PARSE_LAYOUT(_type, _var)                           \
    do                                                      \
    {                                                       \
        cout<<"Memory layout of "#_type <<endl;             \
        cout<<"sizeof "#_type <<": "<<sizeof(_var)<<endl;   \
        tryParse((void ***)&(_var), sizeof(_var));          \
        cout<<endl;                                         \
    } while(0)

void printFunc(const char* cls, const char* func)
{
    cout<<cls<<"::"<<func<<endl;
}

int isAddrRunnable(void *pAddr)
{
    Dl_info info = {};

    dladdr(pAddr, &info);
    return (pAddr == info.dli_saddr)? 1: 0;
}

int runFuncIfValid(void *pAddr)
{
    if (isAddrRunnable(pAddr))
    {
        Fun pFun = (Fun)pAddr;

        pFun();
        return 0;
    }

    return -1;
}

int tryParseVtbl(int idx, void ***pVtbl)
{
    Fun pFun = nullptr;
    void **pPos = nullptr;

    if (nullptr==pVtbl || nullptr==pVtbl[0] ||!isAddrRunnable((void *)pVtbl[0][0]))
    {
        return -1;
    }

    printf("[%d] vtbl->\n", idx);
    pPos = (void **)((char *)pVtbl[0] - 3*sizeof(void *));
    printf("\tVirtual base offset(if any): %d\n", (int)*pPos++);
    printf("\tOffset to most derived object: %d\n", (int)*pPos++);
    printf("\tPointer to most derived type_info @ %p\n", *pPos);

    pFun = (Fun)pVtbl[0][0];
    for (int i = 0; pFun != nullptr; )
    {
        if (!isAddrRunnable((void *)pFun))
        {
            break;
        }

        printf("\t[%d] ", i, pFun);
        runFuncIfValid((void *)pFun);

        i++;
        pFun = (Fun)pVtbl[0][i];
    }

    return 0;
}

int tryParse(void ***pAddr, int size)
{
    int idx = 0;

    while (0<size)
    {
        if (tryParseVtbl(idx, pAddr))
        {
            // member variables of instance
            if (nullptr!=pAddr)
            {
                printf("[%d] %s\n", idx, (const char *) pAddr[0]);
            }
        }

        idx++;
        pAddr++;
        size -= sizeof(*pAddr);
    }

    return 0;
}

void testSingleInherit()
{
    SITopSimp siTopSimp;
    SIMidSimp siMidSimp;
    SIBtmSimp siBtmSimp;
    SITopVir siTopVir;
    SIMidVir siMidVir;
    SIBtmVir siBtmVir;

    cout<<"Testing single inheritance..."<<endl;

    cout<<"Single inheritance with no virtual function"<<endl;
    PARSE_LAYOUT(SITopSimp, siTopSimp);
    PARSE_LAYOUT(SIMidSimp, siMidSimp);
    PARSE_LAYOUT(SIBtmSimp, siBtmSimp);

    cout<<"======================================="<<endl;

    cout<<"Single inheritance with virtual functions"<<endl;
    PARSE_LAYOUT(SITopVir, siTopVir);
    PARSE_LAYOUT(SIMidVir, siMidVir);
    PARSE_LAYOUT(SIBtmVir, siBtmVir);
}

void testMulInherit()
{
    MIBaseLSimp miBaseLSimp;
    MIBaseRSimp miBaseRSimp;
    MIDeriveSimp miDeriveSimp;
    MIBaseLVir miBaseLVir;
    MIBaseRVir miBaseRVir;
    MIDeriveVir miDeriveVir;

    cout<<"Testing multiple inheritance..."<<endl;

    cout<<"Multiple inheritance with no virtual function"<<endl;
    PARSE_LAYOUT(MIBaseLSimp, miBaseLSimp);
    PARSE_LAYOUT(MIBaseRSimp, miBaseRSimp);
    PARSE_LAYOUT(MIDeriveSimp, miDeriveSimp);

    cout<<"======================================="<<endl;

    cout<<"Multiple inheritance with virtual functions"<<endl;
    PARSE_LAYOUT(MIBaseLVir, miBaseLVir);
    PARSE_LAYOUT(MIBaseRVir, miBaseRVir);
    PARSE_LAYOUT(MIDeriveVir, miDeriveVir);
}

void testDiamondInherit()
{
    VIBaseTop viBaseTop;
    VIBaseLDup viBaseLDup;
    VIBaseRDup viBaseRDup;
    VIDeriveDup viDeriveDup;
    VIBaseLVir viBaseLVir;
    VIBaseRVir viBaseRVir;
    VIDeriveVir viDeriveVir;
    VIBaseTop *pViBaseTop = nullptr;
    VIBaseLVir *pViBaseLVir;
    VIBaseRVir *pViBaseRVir;
    VIDeriveVir *pViDeriveVir;
    void *pMostDerivedObj;

    cout<<"Testing diamond inheritance..."<<endl;
    PARSE_LAYOUT(VIBaseTop, viBaseTop);

    cout<<"Diamond inheritance without virtual inheritance"<<endl;
    PARSE_LAYOUT(VIBaseLDup, viBaseLDup);
    PARSE_LAYOUT(VIBaseRDup, viBaseRDup);
    PARSE_LAYOUT(VIDeriveDup, viDeriveDup);

    cout<<"======================================="<<endl;
#if 1
    cout<<"Diamond inheritance with virtual inheritance"<<endl;
    PARSE_LAYOUT(VIBaseLVir, viBaseLVir);
    PARSE_LAYOUT(VIBaseRVir, viBaseRVir);
    PARSE_LAYOUT(VIDeriveVir, viDeriveVir);
#endif

    pViDeriveVir = &viDeriveVir;
    pViBaseTop = static_cast<VIBaseTop *>(pViDeriveVir);
    pViBaseLVir = static_cast<VIBaseLVir *>(pViDeriveVir);
    pViBaseRVir = static_cast<VIBaseRVir *>(pViDeriveVir);

    printf("pViBaseTop @ %p\n", pViBaseTop);
    printf("pViBaseLVir @ %p\n", pViBaseLVir);
    printf("pViBaseRVir @ %p\n", pViBaseRVir);
    printf("pViDeriveVir @ %p\n", pViDeriveVir);

    if (typeid(*pViBaseLVir) == typeid(*pViBaseRVir))
    {
        cout<<"typeid(*pViBaseLVir) == typeid(*pViBaseRVir)"<<endl;
    }
    pViDeriveVir = dynamic_cast<VIDeriveVir *>(pViBaseTop);
    printf("Downcasting: pViBaseTop => pViDeriveVir @ %p\n", pViDeriveVir);

    pViBaseRVir = dynamic_cast<VIBaseRVir *>(pViBaseTop);
    printf("Downcasting: pViBaseTop => pViBaseRVir @ %p\n", pViBaseRVir);

    pViBaseLVir = dynamic_cast<VIBaseLVir *>(pViBaseRVir);
    printf("Cross-casting: pViBaseRVir => pViBaseLVir @ %p\n", pViBaseLVir);

    pMostDerivedObj = dynamic_cast<void *>(pViBaseTop);
    printf("Casting to void *: pViBaseTop => pMostDerivedObj @ %p\n", pMostDerivedObj);
}

int main() {
    //testSingleInherit();
    //testMulInherit();
    testDiamondInherit();

    return 0;
}