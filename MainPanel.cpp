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
    mFXSliders.clear();
}

void FTChorusMainPanel::paint(Graphics& g)
{
    FTChorusPanelBase::paint(g);
    
    for (int i = 0; i < mFXSliders.size(); i++)
    {
        paintComponentLabel(g, mFXSliders[i]);
    }
    
    const int sliderSize = 75;
    int x = (getWidth() / 2) - (sliderSize * 1.5);
    int y = (getHeight()) - (sliderSize * 1.25);
    
    FTChorusParameterSlider* feedback =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_DelayFeedback]);
    feedback->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(feedback);
    mFXSliders.add(feedback);
    x += sliderSize * 2;
    
    FTChorusParameterSlider* wetdry =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_DelayWetDry]);
    wetdry->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(wetdry);
    mFXSliders.add(wetdry);
    x = (getWidth() / 2) - (sliderSize * 1.5);
    y = (getHeight() * 0.75) - (sliderSize * 1.75);
    
    FTChorusParameterSlider* rate =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_ModulationRate]);
    rate->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(rate);
    mFXSliders.add(rate);
    x += sliderSize * 2;
                
    FTChorusParameterSlider* depth =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_ModulationDepth]);
    depth->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(depth);
    mFXSliders.add(depth);

                
}
