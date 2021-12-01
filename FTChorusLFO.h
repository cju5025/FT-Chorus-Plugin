#pragma once
#include "AudioHelpers.h"

class FTChorusLFO
{
public:
    FTChorusLFO();
    ~FTChorusLFO();
    
    void reset();
    
    void setSampleRate(double inSampleRate);
    
    void process(float inRate, float inDepth, int inNumSamples);
    
    float* getBuffer();
    
private:
    
    double mSampleRate;
    
    float mPhase;
    
    float mBuffer[maxBufferSize];
};
