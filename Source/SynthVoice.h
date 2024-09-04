/*
  ==============================================================================

    SynthVoice.h
    Created: 11 Aug 2024 3:24:54pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/WTOscData.h"
#include "Data/OscSubData.h"
#include "Data/ADSR1Data.h"
#include "Data/FilterData.h"
#include "Data/ConvDistortionData.h"
#include "Data/WaveShaperData.h"
#include "Data/Reverb1Data.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound*) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheenValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

    void reset();

    std::array<OscData, 2>& getOscillator1() { return osc1; }
    std::array<WTOscData, 2>& getOscillator2() { return osc2; }
    std::array<OscSubData, 2>& getSubOscillator() { return oscSub; }

    
    ADSR1Data& getAdsr1() { return adsr1; }
    ADSR1Data& getAdsr2() { return adsr2; }

    FilterData& getFilter1() { return filter1; }

    ConvDistortionData& getConvDist1() { return convDist1; }
    WaveShaperData& getWaveshaper1() { return waveShaper1; }

    ReverbData& getReverb1() { return reverb1; }

    void updateFilter(const int filterType, const int filterDBOct, const float frequency,
        const float resonance, const float drive, const float envAmt);

private:
    bool isPrepared{ false };
    juce::dsp::ProcessSpec spec;

    // Envelopes
    ADSR1Data adsr1;
    ADSR1Data adsr2;

    // LFOs

    // Audio Busses
    juce::AudioBuffer<float> osc1Buffer;
    juce::AudioBuffer<float> osc2Buffer;
    juce::AudioBuffer<float> oscSubBuffer;

    // Oscilators
    static constexpr int numVoicesToProcess{ 2 };
    std::array<OscData, numVoicesToProcess> osc1;
    std::array<WTOscData, numVoicesToProcess> osc2;
    std::array<OscSubData, numVoicesToProcess> oscSub;

    // Gain
    juce::dsp::Gain<float> osc1Gain;
    juce::dsp::Gain<float> osc2Gain;
    juce::dsp::Gain<float> oscSubGain;

    // Filter 1
    FilterData filter1; 

    // Convolution Distortion 1
    ConvDistortionData convDist1;

    // WaveShaper 1
    WaveShaperData waveShaper1; 

    // Reverb 1
    ReverbData reverb1;

    // Filter 2

    // Delay 1

    // Reverb 1

};

