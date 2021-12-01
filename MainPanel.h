#pragma once

#include "PanelBase.h"
#include "TopPanel.h"

class FTChorusMainPanel
:   public FTChorusPanelBase
{
public:
    
    FTChorusMainPanel(FTChorusAudioProcessor* inProcessor);
    ~FTChorusMainPanel();
    
private:
    
    std::unique_ptr<FTChorusTopPanel> mTopPanel;
};
