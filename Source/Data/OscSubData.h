/*
  ==============================================================================

    OscSubData.h
    Created: 23 Aug 2024 4:02:20pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscSubData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels);
    float processNextSample(float input);
    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setWaveType(const int choice);
    void updateOscParams(const int midiNoteNumber, const float osc1Macro, const int oscTrans, const float gain);
    void setOscGain(const float gain);
    void setOscTrans(const int transposition);
    void setWaveFrequency(const int midiNoteNumber);

    void resetAll();


private:
    juce::dsp::Gain<float> oscGain;

    int lastMidiNoteNum;
    int trans{ 0 };

};