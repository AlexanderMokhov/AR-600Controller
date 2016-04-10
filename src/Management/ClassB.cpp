#include "ClassB.h"
#include "LogMaster.h"

ClassB::ClassB() : ICoreClass()
{

}

void ClassB::f2()
{
    LogMaster::Inst()->addLine("F2 from ClassB go F1 from ClassA");
    ClassA* cl = (ClassA*)(mCoreRegistry->getClass(0));
    cl->f1();
}
