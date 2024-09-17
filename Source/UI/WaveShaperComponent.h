/*
  ==============================================================================

    WaveShaperComponent.h
    Created: 23 Aug 2024 12:16:27pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class WaveShaperComponent  : public juce::Component
{
public:
    WaveShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String inputID,
        juce::String outputID, juce::String typeID);
    ~WaveShaperComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Title
    SectionTitleLabel saturationTitle;

    // Type Selector
    ComboBoxMedium waveTypeSelector;
    //juce::ComboBox waveTypeSelector;
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeSelectorAttachment;

    // Input Knob
    AnimatedKnobMedium inputSlider;
    AnimatedKnobMedium outputSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveShaperComponent)
};
