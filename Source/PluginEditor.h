/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PresetComponent.h"
#include "PluginProcessor.h"
#include "UI/HorizontalMeter.h"

#include "UI/AHDSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/WTOscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/ConvDistortionComponent.h"
#include "UI/OscSubComponent.h"
#include "UI/WaveShaperComponent.h"
#include "UI/Reverb1Component.h"

#include "UI/MSCompressorComponent.h"

//==============================================================================
/**
*/
class BeastySynth1AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    BeastySynth1AudioProcessorEditor (BeastySynth1AudioProcessor&);
    ~BeastySynth1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;
private:   
    PresetComponent::PresetPanel presetPanel;
    BeastySynth1AudioProcessor& audioProcessor;
    HorizontalMeter meterL, meterR;

    int totalWidth = 1100;
    int totalHeight = 590;
    juce::Image logo1;

    OscComponent osc1;
    FilterComponent filter1;
    ConvDistortionComponent convDist1;
    Reverb1Component reverb1;

    WTOscComponent osc2;
    FilterComponent filter2;

    AHDSRComponent ahdsr1;
    AHDSRComponent ahdsr2;

    OscSubComponent oscSub;
    WaveShaperComponent waveShaper1;

    MSCompressorComponent MSCompressor;


    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeastySynth1AudioProcessorEditor)
};
