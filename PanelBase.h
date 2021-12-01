#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "InterfaceDefines.h"

class FTChorusPanelBase
:   public Component
{
public:
    
    FTChorusPanelBase(FTChorusAudioProcessor* inProcessor);
    ~FTChorusPanelBase();
    
    void paint (Graphics& g) override;
    
protected:
    
    FTChorusAudioProcessor* mProcessor;
    
};
