#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FTChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FTChorusAudioProcessorEditor (FTChorusAudioProcessor&);
    ~FTChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FTChorusAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FTChorusAudioProcessorEditor)
};
