#ifndef CLASSA_H
#define CLASSA_H

#include "ICoreClass.h"
#include "CoreRegistry.h"
#include "ClassB.h"

class ClassA : public ICoreClass
{
public:
    CoreRegistry *mCoreRegistry;
    ClassA();
    void AddRegisstry( CoreRegistry *reg) { mCoreRegistry = reg; }

    void f1();
    void f3();
};

#endif // CLASSA_H
