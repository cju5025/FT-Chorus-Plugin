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
    g.setFont( font_2 );
    g.setColour( Colour( 1, 124, 168 ) );
    g.drawText( mLabel, 0, 0, getWidth(), 80, Justification::centred, false );
    
    for (int i = 0; i < mFXSliders.size(); i++)
    {
        g.setColour(Colour( 1, 124, 168 ) );
        paintComponentLabel( g, mFXSliders[ i ] );
    }
    
    const int sliderSize = 50;
    int x = 50;
    int y = (getHeight() * 0.5) - (sliderSize * 0.5);
    
    FTChorusParameterSlider* feedback =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_DelayFeedback]);
    feedback->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(feedback);
    mFXSliders.add(feedback);
    x += sliderSize * 2;
    
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
    x += sliderSize * 2;
                
    FTChorusParameterSlider* wetdry =
    new FTChorusParameterSlider(mProcessor->parameters, FTChorusParameterID[kFTChorusParameter_DelayWetDry]);
    wetdry->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(wetdry);
    mFXSliders.add(wetdry);
}
