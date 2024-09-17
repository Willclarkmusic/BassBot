/*
  ==============================================================================

    OscComponent.h
    Created: 15 Aug 2024 11:37:38am
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId,
        juce::String macroID, juce::String transID, juce::String gainID, juce::String panID, 
        juce::String unisonID, juce::String widthID, juce::String spreadID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    SectionTitleLabel osc1Title;

    ComboBoxMedium waveSelector;

    AnimatedKnobMedium macroKnob;
    AnimatedKnobMedium transKnob;
    AnimatedKnobMedium gainKnob;
    AnimatedKnobMedium panKnob;
    AnimatedKnobMedium unisonKnob;
    SliderBoxMedium widthKnob;
    SliderBoxMedium spreadKnob;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
