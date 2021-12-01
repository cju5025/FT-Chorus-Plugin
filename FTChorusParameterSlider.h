#pragma once
#include "JuceHeader.h"
#include "InterfaceDefines.h"
#include "FTChorusDial.h"

class FTChorusParameterSlider
:   public Slider
{
public:
    
    FTChorusParameterSlider(AudioProcessorValueTreeState& stateToControl,
                        const String& parameterID);
    
    ~FTChorusParameterSlider();
        
private:
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    FTChorusDial mDialLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FTChorusParameterSlider);
};
