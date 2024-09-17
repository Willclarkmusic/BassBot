/*
  ==============================================================================

    AHDSRComponent.h
    Created: 6 Sep 2024 11:33:20pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class AHDSRComponent  : public juce::Component
{
public:
    AHDSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID,
        juce::String holdID, juce::String decayID, juce::String sustainID, juce::String releaseID, 
        juce::String attackSlopeID, juce::String decaySlopeID, juce::String releaseSlopeID);
    ~AHDSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    AnimatedKnobSmall attackKnob;
    AnimatedKnobSmall holdKnob;
    AnimatedKnobSmall decaykKnob;
    AnimatedKnobSmall sustainKnob;
    AnimatedKnobSmall releaseKnob;

    SliderBoxSmall attackSlopeKnob;
    SliderBoxSmall decaySlopeKnob;
    SliderBoxSmall releasekSlopeKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AHDSRComponent)
};
