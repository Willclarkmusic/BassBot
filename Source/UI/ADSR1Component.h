/*
  ==============================================================================

    ADSR1Component.h
    Created: 14 Aug 2024 9:41:13pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSR1Component  : public juce::Component
{
public:
    ADSR1Component(juce::AudioProcessorValueTreeState& apvts, juce::String attackID,
        juce::String decayID, juce::String sustainID, juce::String releaseID);
    ~ADSR1Component() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    void setSliderLabelSmall(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);
    void setTextButtonDefault(juce::TextButton& button, juce::String& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<ButtonAttachment>& attachment);
    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);

    void setSliderParamsDefault(juce::Slider& slider);

    juce::Slider attack1Slider;
    juce::Slider decay1Slider;
    juce::Slider sustain1Slider;
    juce::Slider release1Slider;

    juce::Label attack1Label{ "a", "a" };
    juce::Label decay1Label{ "d", "d" };
    juce::Label sustain1Label{ "s", "s" };
    juce::Label release1Label{ "r", "r" };


    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attack1Attachment;
    std::unique_ptr<SliderAttachment> decay1Attachment;
    std::unique_ptr<SliderAttachment> sustain1Attachment;
    std::unique_ptr<SliderAttachment> release1Attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR1Component)
};
