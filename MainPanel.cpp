#include "MainPanel.h"
#include "Parameters.h"

FTChorusMainPanel::FTChorusMainPanel(FTChorusAudioProcessor* inProcessor)
:   FTChorusPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mTopPanel = std::make_unique<FTChorusTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());
    
}

FTChorusMainPanel::~FTChorusMainPanel()
{
    
}
