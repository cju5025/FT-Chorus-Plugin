#include "LFO.h"
#include "JuceHeader.h"

FTChorusLFO::FTChorusLFO()
{
    reset();
}

FTChorusLFO::~FTChorusLFO()
{
    
}

void FTChorusLFO::reset()
{
    mPhase = 0.0f;
    zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void FTChorusLFO::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void FTChorusLFO::getHostBPM()
{
    DBG(mHostInfo.bpm);
}

void FTChorusLFO::process(float inRate, float inDepth, int inNumSamples)
{
    getHostBPM();
    
    const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
    
    for (int i = 0; i < inNumSamples; i++)
    {
        mPhase += (rate / mSampleRate);
        
        if (mPhase > 1)
        {
            mPhase -= 1.0f;
        }
        
        const float LFOPosition = sinf(mPhase * TWO_PI) * inDepth;
        
        mBuffer[i] = LFOPosition;
    }
}

float* FTChorusLFO::getBuffer()
{
    return mBuffer;
}
