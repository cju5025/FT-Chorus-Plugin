#include "PluginProcessor.h"
#include "PluginEditor.h"

FTChorusAudioProcessorEditor::FTChorusAudioProcessorEditor (FTChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

FTChorusAudioProcessorEditor::~FTChorusAudioProcessorEditor()
{
}

//==============================================================================
void FTChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FTChorusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
