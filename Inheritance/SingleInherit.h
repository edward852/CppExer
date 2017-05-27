//
// Created by switch on 5/25/17.
//

#ifndef INHERITANCE_SINGLEINHERIT_H
#define INHERITANCE_SINGLEINHERIT_H


#include "Dbg.h"

class SITopSimp {
public:
    const char* desc;
    SITopSimp ():desc("SITopSimp.desc") {}

private:
    constexpr static const char *className = "SITopSimp";
};

class SIMidSimp: public SITopSimp {
public:
    const char* desc;
    SIMidSimp ():desc("SIMidSimp.desc") {}

private:
    constexpr static const char *className = "SIMidSimp";
};

class SIBtmSimp: public SIMidSimp {
public:
    const char* desc;
    SIBtmSimp ():desc("SIBtmSimp.desc") {}

private:
    constexpr static const char *className = "SIBtmSimp";
};

class SITopVir {
public:
    const char* desc;
    SITopVir ():desc("SITopVir.desc") {}
    virtual void funcSITopVir1() { printFunc(className, __func__); }
    virtual void funcSITopVir2() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "SITopVir";
};

class SIMidVir: public SITopVir {
public:
    const char* desc;
    SIMidVir ():desc("SIMidVir.desc") {}
    virtual void funcSITopVir1() { printFunc(className, __func__); }
    virtual void funcSIMidVir1() { printFunc(className, __func__); }
    virtual void funcSIMidVir2() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "SIMidVir";
};

class SIBtmVir: public SIMidVir {
public:
    const char* desc;
    SIBtmVir ():desc("SIBtmVir.desc") {}
    virtual void funcSITopVir2() { printFunc(className, __func__); }
    virtual void funcSIMidVir1() { printFunc(className, __func__); }
    virtual void funcSIBtmVir1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "SIBtmVir";
};

#endif //INHERITANCE_SINGLEINHERIT_H
