//
// Created by switch on 5/26/17.
//

#ifndef INHERITANCE_DIAMONDINHERIT_H
#define INHERITANCE_DIAMONDINHERIT_H

#include <iostream>

#include "Dbg.h"

class VIBaseTop {
public:
    const char *desc;
    VIBaseTop():desc("VIBaseTop.desc") {}
    virtual void funcVIBaseTop_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIBaseTop";
};

class VIBaseLDup: public VIBaseTop {
public:
    const char *desc;
    VIBaseLDup():desc("VIBaseLDup.desc") {}
    virtual void funcVIBaseLDup_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIBaseLDup";
};

class VIBaseRDup: public VIBaseTop {
public:
    const char *desc;
    VIBaseRDup():desc("VIBaseRDup.desc") {}
    virtual void funcVIBaseRDup_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIBaseRDup";
};

class VIDeriveDup : public VIBaseLDup, public VIBaseRDup {
public:
    const char *desc;
    VIDeriveDup():desc("VIDeriveDup.desc") {}
    virtual void funcVIDeriveDup_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIDeriveDup";
};

class VIBaseLVir: virtual public VIBaseTop {
public:
    const char *desc;
    VIBaseLVir():desc("VIBaseLVir.desc") {}
    virtual void funcVIBaseLVir_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIBaseLVir";
};

class VIBaseRVir: virtual public VIBaseTop {
public:
    const char *desc;
    VIBaseRVir():desc("VIBaseRVir.desc") {}
    virtual void funcVIBaseRVir_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIBaseRVir";
};

class VIDeriveVir : public VIBaseLVir, public VIBaseRVir {
public:
    const char *desc;
    VIDeriveVir():desc("VIDeriveVir.desc") {}
    virtual void funcVIDeriveVir_1() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "VIDeriveVir";
};


#endif //INHERITANCE_DIAMONDINHERIT_H
