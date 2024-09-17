/*
  ==============================================================================

    Reverb1Component.h
    Created: 24 Aug 2024 3:34:36pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class Reverb1Component  : public juce::Component
{
public:
    Reverb1Component(juce::AudioProcessorValueTreeState& apvts, juce::String sizeID,
        juce::String dampID, juce::String widthID, juce::String wetID, juce::String dryID);
    ~Reverb1Component() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SectionTitleLabel reverbTitle;
    
    AnimatedKnobMedium sizeSlider;
    AnimatedKnobMedium dampSlider;
    AnimatedKnobMedium widthSlider;

    SliderBoxMedium wetSlider;
    SliderBoxMedium drySlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Reverb1Component)
};
