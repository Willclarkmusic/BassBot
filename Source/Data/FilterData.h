/*
  ==============================================================================

    FilterData.h
    Created: 19 Aug 2024 12:17:27pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParams(const int filterType, const int filterDBOct, const float frequency, 
        const float resonance, const float drive, const float envAmt, const float envelope = 1.0f);
    void reset();


private:
    juce::dsp::LadderFilter<float> filter;


};
