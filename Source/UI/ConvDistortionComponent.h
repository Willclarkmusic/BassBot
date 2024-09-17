/*
  ==============================================================================

    ConvDistortionComponent.h
    Created: 23 Aug 2024 4:59:24pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "..\PluginProcessor.h"
#include "CustomComponents.h"

//==============================================================================
/*
*/
class ConvDistortionComponent  : public juce::Component
{
public:
    ConvDistortionComponent(BeastySynth1AudioProcessor& processor, juce::AudioProcessorValueTreeState& apvts,
        juce::String IRLoadID, juce::String dryWetID, juce::String gainID);
    ~ConvDistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BeastySynth1AudioProcessor& audioProcessor;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    SectionTitleLabel convDistortionTitle;

    // IR selector
    ComboBoxMedium irSelector;

    void updateIRComboBoxItems();

    // Dry Wet Mix 
    AnimatedKnobMedium dryWetKnob;
    AnimatedKnobMedium gainKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvDistortionComponent)
};
