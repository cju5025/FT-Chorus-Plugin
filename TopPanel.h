#pragma once
#include "PanelBase.h"

class FTChorusTopPanel
:   public FTChorusPanelBase
{
    
public:
    
    FTChorusTopPanel(FTChorusAudioProcessor* inProcessor);
    ~FTChorusTopPanel();
    
    void paint(Graphics& g) override;

private:
    
};
