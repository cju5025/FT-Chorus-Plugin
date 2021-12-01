#include "PluginProcessor.h"
#include "PluginEditor.h"

FTChorusAudioProcessorEditor::FTChorusAudioProcessorEditor (FTChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    mMainPanel = std::make_unique<FTChorusMainPanel>(&audioProcessor);
    addAndMakeVisible(mMainPanel.get());
}

FTChorusAudioProcessorEditor::~FTChorusAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void FTChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setFont(font_3);
}

void FTChorusAudioProcessorEditor::resized()
{

}
