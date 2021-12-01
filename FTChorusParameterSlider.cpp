#include "FTChorusParameterSlider.h"

FTChorusParameterSlider::FTChorusParameterSlider(AudioProcessorValueTreeState& stateToControl,
                    const String& parameterID)
:   Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    setColour(textBoxOutlineColourId, Colours::transparentWhite);
    setLookAndFeel(&mDialLookAndFeel);
    setRange(0.0f, 1.0f, 0.01f);
    
    mAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
}

FTChorusParameterSlider::~FTChorusParameterSlider()
{
    
}

