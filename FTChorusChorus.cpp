#include "FTChorusChorus.h"
#include "JuceHeader.h"

FTChorusChorus::FTChorusChorus()
:   mSampleRate(-1),
    mFeedbackSample(0.0f),
    mTimeSmoothed(0.0f),
    mDelayIndex(0)
{
    
}

FTChorusChorus::~FTChorusChorus()
{
    
}

void FTChorusChorus::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void FTChorusChorus::reset()
{
    mTimeSmoothed = 0.0f;
    
    zeromem(mBuffer, (sizeof(double) * maxBufferSize));
}

void FTChorusChorus::process(float* inAudio,
                             float inFeedback,
                             float inWetDry,
                             float* inModulationBuffer,
                             float* outAudio,
                             int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.98f);
    
    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        
        const double delayTimeModulation = (0.003 + (0.002f * inModulationBuffer[i]));
        mTimeSmoothed = mTimeSmoothed - smoothingCoefficient_Fine * (mTimeSmoothed - delayTimeModulation);
        
        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
        
        mFeedbackSample = sample;
        
        outAudio[i] = ((inAudio[i] * dry) + (sample * wet));
                
        mDelayIndex += 1;
        
        if (mDelayIndex >= maxBufferSize)
        {
            mDelayIndex -= maxBufferSize;
        }
    }
}

double FTChorusChorus::getInterpolatedSample(float inDelayTimeInSamples)
{
    float readPosition = (float)mDelayIndex - inDelayTimeInSamples;
    
    if(readPosition < 0.0f)
    {
        readPosition += (float)maxBufferSize;
    }
    
    int index_y0 = (int)readPosition - 1;
    if (index_y0 < 0)
    {
        index_y0 += (float)maxBufferSize;
    }
    
    int index_y1 = readPosition;
    if (index_y1 >= maxBufferSize)
    {
        index_y1 -= maxBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;
    
    float outSample = linearInterpolation(sample_y0, sample_y1, t);
    
    return outSample;
}
