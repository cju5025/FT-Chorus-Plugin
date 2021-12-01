#pragma once

#include "PanelBase.h"
#include "TopPanel.h"
#include "FTChorusParameterSlider.h"
#include "GUIHelpers.h"

class FTChorusMainPanel
:   public FTChorusPanelBase
{
public:
    
    FTChorusMainPanel(FTChorusAudioProcessor* inProcessor);
    ~FTChorusMainPanel();
    
    void paint(Graphics& g) override;
    
private:
    
    std::unique_ptr<FTChorusTopPanel> mTopPanel;
    
    String mLabel;
    
    OwnedArray<FTChorusParameterSlider> mFXSliders;
};
