/*
  ==============================================================================

    CustomComponents.h
    Created: 30 Aug 2024 4:20:19pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomComponents  : public juce::Component
{
public:
    CustomComponents();
    ~CustomComponents() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComponents)
};



class AnimatedKnobMedium : public juce::Component
{
public:
    void createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String labelString);
    void setBoundsKnobWithLabel(int xPos, int yPos);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int knobRadius = 80;
    int labelHeight = 15;
    int labelWidth = 80;
    int padding = 5;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    juce::Label label;
};