#pragma once

enum FTChorusParameter
{
    kFTChorusParameter_InputGain = 0,
    kFTChorusParameter_DelayTime,
    kFTChorusParameter_DelayFeedback,
    kFTChorusParameter_DelayWetDry,
    kFTChorusParameter_OutputGain,
    kFTChorusParameter_ModulationRate,
    kFTChorusParameter_ModulationDepth,
    kFTChorusParameter_TotalNumParameters
};

static String FTChorusParameterID [ kFTChorusParameter_TotalNumParameters ] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "Wet / Dry",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth"
};

static String FTChorusParameterLabel [ kFTChorusParameter_TotalNumParameters ] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "Wet/Dry",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth"
};

static float FTChorusParameterDefaultValue [ kFTChorusParameter_TotalNumParameters ] =
{
    0.5f,
    0.25f,
    0.5f,
    0.5f,
    0.5f,
    0.25f,
    0.5f
};
