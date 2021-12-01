#pragma once

enum FTChorusParameter
{
    kFTChorusParameter_DelayTime = 0,
    kFTChorusParameter_DelayFeedback,
    kFTChorusParameter_DelayWetDry,
    kFTChorusParameter_ModulationRate,
    kFTChorusParameter_ModulationDepth,
    kFTChorusParameter_TotalNumParameters
};

static String FTChorusParameterID [ kFTChorusParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet / Dry",
    "Modulation Rate",
    "Modulation Depth"
};

static String FTChorusParameterLabel [ kFTChorusParameter_TotalNumParameters ] =
{
    "Feedback",
    "Wet/Dry",
    "Modulation Rate",
    "Modulation Depth"
};

static float FTChorusParameterDefaultValue [ kFTChorusParameter_TotalNumParameters ] =
{
    0.5f,
    0.5f,
    0.25f,
    0.5f
};
