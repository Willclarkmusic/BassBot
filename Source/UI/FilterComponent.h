/*
  ==============================================================================

    FilterComponent.h
    Created: 21 Aug 2024 11:21:34am
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId,
        juce::String dbOctID, juce::String driveID, juce::String cutoffID, juce::String resID, juce::String envID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Title
    SectionTitleLabel filterTitle;

    // Selectors
    ComboBoxMedium typeSelector;
    ComboBoxMedium dbOctSelector;

    // Knobs
    AnimatedKnobMedium cutoffKnob;
    AnimatedKnobMedium resKnob;
    SliderBoxMedium driveSlider;
    SliderBoxMedium envAmountSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};

