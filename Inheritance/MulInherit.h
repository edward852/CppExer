//
// Created by switch on 5/25/17.
//

#ifndef INHERITANCE_MULINHERIT_H
#define INHERITANCE_MULINHERIT_H


#include "Dbg.h"

class MIBaseLSimp {
public:
    const char *desc;
    MIBaseLSimp():desc("MIBaseLSimp.desc") {}

private:
    constexpr static const char *className = "MIBaseLSimp";
};

class MIBaseRSimp {
public:
    const char *desc;
    MIBaseRSimp():desc("MIBaseRSimp.desc") {}

private:
    constexpr static const char *className = "MIBaseRSimp";
};

class MIDeriveSimp : public MIBaseLSimp, public MIBaseRSimp {
public:
    const char *desc;
    MIDeriveSimp():desc("MIDeriveSimp.desc") {}

private:
    constexpr static const char *className = "MIDeriveSimp";
};

class MIBaseLVir {
public:
    const char *desc;
    MIBaseLVir():desc("MIBaseLVir.desc") {}
    virtual void funcMIBaseLVir_1() { printFunc(className, __func__); }
    virtual void funcMIBaseLVir_2() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "MIBaseLVir";
};

class MIBaseRVir {
public:
    const char *desc;
    MIBaseRVir():desc("MIBaseRVir.desc") {}
    virtual void funcMIBaseRVir_1() { printFunc(className, __func__); }
    virtual void funcMIBaseRVir_2() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "MIBaseRVir";
};

class MIDeriveVir : public MIBaseLVir, public MIBaseRVir {
public:
    const char *desc;
    MIDeriveVir():desc("MIDeriveVir.desc") {}
    virtual void funcMIBaseLVir_1() { printFunc(className, __func__); }
    virtual void funcMIBaseRVir_2() { printFunc(className, __func__); }
    virtual void funcMIDeriveVir_1() { printFunc(className, __func__); }
    virtual void funcMIDeriveVir_2() { printFunc(className, __func__); }

private:
    constexpr static const char *className = "MIDeriveVir";
};


#endif //INHERITANCE_MULINHERIT_H
