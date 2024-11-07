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
#include "Data/AHDSRData.h"
#include "Data/FilterData.h"
#include "Data/ConvDistortionData.h"
#include "Data/WaveShaperData.h"
#include "Data/Reverb1Data.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheenValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void renderOsc1Bus(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);
    void renderOsc2Bus(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);
    void renderSubBus(juce::AudioBuffer<float>& subBuffer, int startSample, int numSamples);

    void reset();


    static constexpr int numVoicesToProcess{ 1 };  // Polyphony
    static constexpr int getNumVoicesToProcess() { return numVoicesToProcess; }

    std::array<OscData, numVoicesToProcess>& getOscillator1() { return osc1; }
    std::array<WTOscData, numVoicesToProcess>& getOscillator2() { return osc2; }
    OscSubData& getSubOscillator() { return oscSub; }
    
    AHDSRData& getAHDSR1() { return ahdsr1; }
    AHDSRData& getAHDSR2() { return ahdsr2; }

    FilterData& getFilter1() { return filter1; }
    FilterData& getFilter2() { return filter2; }

    ConvDistortionData& getConvDist1() { return convDist1; }
    WaveShaperData& getWaveshaper1() { return waveShaper1; }

    ReverbData& getReverb1() { return reverb1; }

    void updateFilter1(const int filterType, const int filterDBOct, const float frequency,
        const float resonance, const float drive, const float envAmt);
    void updateFilter2(const int filterType, const int filterDBOct, const float frequency,
        const float resonance, const float drive, const float envAmt);

private:
    bool isPrepared{ false };
    juce::dsp::ProcessSpec spec;
    
    // LFOs

    // Audio Busses
    juce::AudioBuffer<float> osc1Buffer;
    juce::AudioBuffer<float> osc1FXBuffer;
    juce::AudioBuffer<float> osc2Buffer;
    juce::AudioBuffer<float> osc2FXBuffer;
    juce::AudioBuffer<float> oscSubBuffer;

    // Oscilators
    std::array<OscData, numVoicesToProcess> osc1;
    std::array<WTOscData, numVoicesToProcess> osc2;
    OscSubData oscSub;

    // Envelopes
    AHDSRData ahdsr1;
    AHDSRData ahdsr2;

    // Filters
    FilterData filter1; 
    FilterData filter2; 

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

