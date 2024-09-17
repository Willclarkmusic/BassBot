/*
  ==============================================================================

    OscSubComponent.h
    Created: 23 Aug 2024 4:02:41pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponents.h"


//==============================================================================
/*
*/
class OscSubComponent  : public juce::Component
{
public:
    OscSubComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId,
        juce::String macroID, juce::String transID, juce::String gainID);
    ~OscSubComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Title
    SectionTitleLabel oscSubTitle;

    // Osc wave select
    ComboBoxMedium waveSelector;

    // Knobs
    AnimatedKnobMedium macroKnob;
    AnimatedKnobMedium transKnob;
    AnimatedKnobMedium gainKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSubComponent)
};
