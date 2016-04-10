#ifndef COREREGISTRY_H
#define COREREGISTRY_H

#include "ICoreClass.h"
#include "vector"

class CoreRegistry
{
public:
    CoreRegistry();

    std::vector<ICoreClass*> mCoreClasses;

    ICoreClass* getClass(int ID) { return mCoreClasses.at(ID); }
    void addCoreClass(int ID, ICoreClass* class_) { mCoreClasses.push_back(class_); }

};

#endif // COREREGISTRY_H
