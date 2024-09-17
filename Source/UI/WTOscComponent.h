/*
  ==============================================================================

    WTOscComponent.h
    Created: 2 Sep 2024 12:39:57pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomComponents.h"
#include "..\PluginProcessor.h"

//==============================================================================
/*
*/
class WTOscComponent  : public juce::Component
{
public:
    WTOscComponent(BeastySynth1AudioProcessor& processor, juce::AudioProcessorValueTreeState& apvts, 
        juce::String waveSelectorId, juce::String morphID, juce::String transID, juce::String gainID, 
        juce::String panID, juce::String unisonID, juce::String widthID, juce::String spreadID);
    ~WTOscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    BeastySynth1AudioProcessor& audioProcessor;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    SectionTitleLabel osc2Title;

    ComboBoxMedium waveSelector;

    AnimatedKnobMedium morphKnob;
    AnimatedKnobMedium transKnob;
    AnimatedKnobMedium gainKnob;
    AnimatedKnobMedium panKnob;
    AnimatedKnobMedium unisonKnob;

    SliderBoxMedium widthKnob;
    SliderBoxMedium spreadKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WTOscComponent)
};
