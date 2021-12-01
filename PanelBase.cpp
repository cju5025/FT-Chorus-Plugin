#include "PanelBase.h"

FTChorusPanelBase::FTChorusPanelBase(FTChorusAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}

FTChorusPanelBase::~FTChorusPanelBase()
{
    
}

void FTChorusPanelBase::paint (Graphics& g)
{
    g.setColour(Colour(67, 76, 80));
    g.fillAll();    
}
