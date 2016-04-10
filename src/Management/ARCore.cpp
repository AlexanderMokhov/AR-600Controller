#include "ARCore.h"

ARCore * ARCore::m_inst = 0;

void ARCore::movesStoreInit()
{
    m_MovesStore = new MovesStorage();
    mCoreRegistry->addCoreClass(1, m_MovesStore);
    m_MovesStore->addRegistry(mCoreRegistry);
}

ARCore::ARCore()
{
    mCoreRegistry = new CoreRegistry();

    m_SettingStore = new SettingsStorage();
    mCoreRegistry->addCoreClass(0, m_SettingStore);
}
