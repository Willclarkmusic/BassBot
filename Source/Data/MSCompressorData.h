/*
  ==============================================================================

    MSCompressorData.h
    Created: 22 Aug 2024 4:43:58pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MSCompressorData
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBuffer);
    void updateMSCompParams(float midsGain, float sidesGain);

    void setCrossover();
    void setGains();
    void setMidParams();
    void setSideParams();

private:
    juce::dsp::Gain<float> midsGainParam;
    juce::dsp::Gain<float> sidesGainParam;

    float mMidsGain;
    float mSidesGain;

    

};

