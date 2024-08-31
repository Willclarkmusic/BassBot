/*
  ==============================================================================

    UnisonOsc.h
    Created: 26 Aug 2024 4:05:14pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class UnisonOsc : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec, const int index);
    void renderNextBuffer(juce::AudioBuffer<float> &buffer, int startSample, int numSamples);
    void setUniFrequency(const int& index, const float& frequency, const float& spread);
    void setUniWidth(const int& index, const float& pan, const float& uniWidth);

    void resetAllUni();

private:
    juce::AudioBuffer<float> uniBuffer;
    juce::dsp::Gain<float> uniOscGain;
    juce::dsp::Panner<float> uniOscPan;

};