#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> params;
    
    for (int i = 0; i < kFTChorusParameter_TotalNumParameters; i++)
    {
        params.push_back(std::make_unique<AudioParameterFloat>(FTChorusParameterID[i],
                                                               FTChorusParameterLabel[i],
                                                               NormalisableRange<float> (0.0f, 1.0f, 0.001f),
                                                               FTChorusParameterDefaultValue[i]));
    }
    return { params.begin(), params.end() };
}

FTChorusAudioProcessor::FTChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                        parameters(*this,
                                   nullptr,
                                   Identifier("FTChorus"),
                                   createParameterLayout())
#endif
{
    initializeDSP();
}

FTChorusAudioProcessor::~FTChorusAudioProcessor()
{
}

//==============================================================================
const juce::String FTChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FTChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FTChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FTChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FTChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FTChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FTChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FTChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FTChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void FTChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FTChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mChorus[i]->setSampleRate(sampleRate);
        mLFO[i]->setSampleRate(sampleRate);
    }
    
    mDryWetSmoothed.reset(sampleRate, 0.004f);
    mFeedbackSmoothed.reset(sampleRate, 0.004f);
}

void FTChorusAudioProcessor::releaseResources()
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mChorus[i]->reset();
        mLFO[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FTChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FTChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        float rate = -(*parameters.getRawParameterValue(FTChorusParameterID[kFTChorusParameter_ModulationRate]));
        
        if (channel > 0)
        {
            rate = *parameters.getRawParameterValue(FTChorusParameterID[kFTChorusParameter_ModulationRate]);
        }
        
        mLFO[channel]->process(rate,
                               *parameters.getRawParameterValue(FTChorusParameterID[kFTChorusParameter_ModulationDepth]),
                               buffer.getNumSamples());
        
        mDryWetSmoothed.setTargetValue(*parameters.getRawParameterValue(FTChorusParameterID[kFTChorusParameter_WetDry]));
        mFeedbackSmoothed.setTargetValue(*parameters.getRawParameterValue(FTChorusParameterID[kFTChorusParameter_Feedback]));
        
        mChorus[channel]->process(channelData,
                                 mFeedbackSmoothed.getNextValue(),
                                 mDryWetSmoothed.getNextValue(),
                                 mLFO[channel]->getBuffer(),
                                 channelData,
                                 buffer.getNumSamples());
        
    }
}

//==============================================================================
bool FTChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FTChorusAudioProcessor::createEditor()
{
    return new FTChorusAudioProcessorEditor (*this);
}

//==============================================================================
void FTChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void FTChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

void FTChorusAudioProcessor::initializeDSP()
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mChorus[i] = std::make_unique<FTChorusChorus>();
        mLFO[i] = std::make_unique<FTChorusLFO>();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FTChorusAudioProcessor();
}
