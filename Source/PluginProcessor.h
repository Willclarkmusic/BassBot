/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PresetManager.h"

#include "SynthVoice.h"
#include "SynthSound.h"
#include "Data\MSCompressorData.h"

//==============================================================================
/**
*/
class BeastySynth1AudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    BeastySynth1AudioProcessor();
    ~BeastySynth1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processParameters();

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================

    // Preset Managment
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    Service::PresetManager& getPresetManager() { return presetManager; }

    // Global settings
    juce::AudioProcessorValueTreeState apvts;
    juce::dsp::ProcessSpec spec;

    juce::StringArray getIRDistFiles();
    juce::StringArray getWaveTableFiles();

    float getRmsValue(const int channel) const
    {
        jassert(channel == 0 || channel == 1);
        if (channel == 0)
            return rmsLevelLeft.getCurrentValue();
        if (channel == 1)
            return rmsLevelLeft.getCurrentValue();
        return 0.0f;
    }

private:
    Service::PresetManager presetManager;
    juce::Synthesiser synth;
    
    void parameterChanged(const juce::String& parameterID, float newValue);

    juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    MSCompressorData MSCompressor;

    int polyphony = 1;

    juce::LinearSmoothedValue<float> rmsLevelLeft, rmsLevelRight;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeastySynth1AudioProcessor)
};
