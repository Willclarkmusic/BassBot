/*
  ==============================================================================

    ADSR1Data.h
    Created: 14 Aug 2024 9:41:36pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSR1Data : public juce::ADSR
{
public:
    void updateADSR1(const float attack1, const float decay1, const float sustain1, const float release1);

private:
    juce::ADSR::Parameters adsr1Params;
};
