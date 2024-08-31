/*
  ==============================================================================

    OscData.h
    Created: 14 Aug 2024 11:46:20pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "UnisonOsc.h"

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels);
    float processNextSample(float input);
    void renderNextBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    void setWaveType(const int choice);
    void updateOscParams(const int& oscWaveChoice, const float& osc1Macro, const int& transposition,
        const float& gain, const float& pan, const int& uniVoices, const float& uniWidth, const float& uniSpread);
    void setOscGain(const float gain);
    void setOscPan(const float pan);
    void setOscTrans(const int transposition);
    void setWaveFrequency(const int midiNoteNumber);

    void resetAll();
    //void setFmOsc(const float freq);

private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) { return std::sin(x); } };
    std::function< NumericType(NumericType)> currentWaveType = [](float x) { return std::sin(x); };

    // Unison Voices
    static constexpr int maxUnisonVoices{ 12 };
    std::array<UnisonOsc, maxUnisonVoices> uniOscs;
    int uniVoicesParam = 0;

    juce::dsp::Gain<float> oscGain; 
    juce::dsp::Panner<float> oscPan;

    float spread{ 0.0f };
    
    int lastMidiNoteNum;
    int trans{ 0 };

};

