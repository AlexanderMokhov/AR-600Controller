#ifndef CLASSB_H
#define CLASSB_H

#include "ICoreClass.h"
#include "CoreRegistry.h"
#include "ClassA.h"

class ClassB : public ICoreClass
{
public:
    CoreRegistry *mCoreRegistry;
    ClassB();
    void AddRegisstry( CoreRegistry*reg) { mCoreRegistry = reg; }

    void f2();
};

#endif // CLASSB_H
