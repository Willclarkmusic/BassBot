/*
  ==============================================================================

    WaveShaperData.h
    Created: 23 Aug 2024 12:16:08pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class WaveShaperData
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBuffer(juce::AudioBuffer<float>& buffer);
    void updateParams(const float input, const float output, const int type);

    void resetAll();

private:
    juce::dsp::WaveShaper<float> wsTahn{ juce::dsp::FastMathApproximations::tanh };
    juce::dsp::WaveShaper<float> wsSinh{ juce::dsp::FastMathApproximations::sin };
    juce::dsp::WaveShaper<float> wsCosh{ juce::dsp::FastMathApproximations::cos };

    int wsType = 0;

    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain;

};