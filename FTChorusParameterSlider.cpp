#include "FTChorusParameterSlider.h"

FTChorusParameterSlider::FTChorusParameterSlider(AudioProcessorValueTreeState& stateToControl,
                    const String& parameterID)
:   Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    setColour(textBoxOutlineColourId, Colours::transparentWhite);
    setLookAndFeel(&mDialLookAndFeel);
    setRange(0.0f, 1.0f, 0.001f);
    
    mAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
}

FTChorusParameterSlider::~FTChorusParameterSlider()
{
    
}
