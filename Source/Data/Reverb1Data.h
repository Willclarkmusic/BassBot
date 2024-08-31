/*
  ==============================================================================

    Reverb1Data.h
    Created: 24 Aug 2024 3:34:17pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ReverbData : juce::Reverb
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int numChannels);
    void renderNextBlock(juce::AudioBuffer<float>& buffer);
    void updateParams(const float& size, const float& damping, const float& width, const float& wet, const float& dry);
    void resetAll();

private:
    Parameters reverbParams;

};