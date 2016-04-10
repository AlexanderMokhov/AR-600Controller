#ifndef ARCORE_H
#define ARCORE_H

#include "CoreRegistry.h"

#include "SettingsStorage.h"
#include "MovesStorage.h"

class ARCore
{
public:
    //public methods
    static ARCore* Inst(){return m_inst;}
    static void Init(){delete m_inst; m_inst = new ARCore;}

    SettingsStorage* getSettingStore() { return m_SettingStore; }
    MovesStorage* getMovesStore() { return m_MovesStore; }

    void movesStoreInit();

private:
    ARCore();
    ~ARCore(){}
    ARCore(ARCore const&);

    //private variable
    static ARCore* m_inst;

    CoreRegistry* mCoreRegistry;

    SettingsStorage* m_SettingStore;
    MovesStorage* m_MovesStore;
};

#endif // ARCORE_H
