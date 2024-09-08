/*
  ==============================================================================

    WTOscData.h
    Created: 2 Sep 2024 12:39:02pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UnisonOsc.h"

class WTOscData : public juce::dsp::Oscillator<float>
{
public:
    WTOscData();
    ~WTOscData();

    void prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels);
    void loadWaveTableFile(const int& wtIndex, const juce::StringArray& wtArray);
    void initialiseOscillator();
    void renderNextBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    void setWaveFrequency(const int midiNoteNumber);

    float getNextSample();

    void updateOscParams(const float& morph, const int& transposition,
        const float& gain, const float& pan, const int& uniVoices, const float& uniWidth,
        const float& uniSpread);
    void setMorph(float morphValue); // 0.0 to 1.0 to morph between wave positions
    void setOscTrans(const int transposition);
    void setOscGain(const float gain);
    void setOscPan(const float pan);

    void resetAll();

private:
    std::vector<juce::AudioBuffer<float>> wavetables;

    juce::AudioBuffer<float> wavBuffer;
    std::vector<float> wavetableData;

    int wavetableSize{ 512 };
    float morphPosition = 0.0f; // Morph position between 0.0 and 1.0

    double currentSampleRate = 44100.0f;

    juce::dsp::Gain<float> oscGain;
    juce::dsp::Panner<float> oscPan;
    
    int lastMidiNoteNum{ 64 };
    int trans{ 0 };

    // Unison Voices
    static constexpr int maxUnisonVoices{ 6 };
    std::array<UnisonOsc, maxUnisonVoices> uniOscs;
    int uniVoicesParam = 0;

    float spread{ 0.0f };

};