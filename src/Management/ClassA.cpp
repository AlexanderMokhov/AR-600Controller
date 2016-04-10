#include "ClassA.h"
#include "LogMaster.h"

ClassA::ClassA() : ICoreClass()
{

}

void ClassA::f1()
{
    LogMaster::Inst()->addLine("F1 from ClassA");
}

void ClassA::f3()
{
    LogMaster::Inst()->addLine("F3 from ClassA go F2 from ClassB");
    ClassB* cl = (ClassB*)(mCoreRegistry->getClass(1));
    cl->f2();
}
