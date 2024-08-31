/*
  ==============================================================================

    WaveShaperComponent.h
    Created: 23 Aug 2024 12:16:27pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);

    // Type Selector
    juce::ComboBox waveTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeSelectorAttachment;

    // Input Knob
    juce::Slider inputSlider;
    std::unique_ptr<SliderAttachment> inputSliderAttachment;
    juce::Label inputLabel{ "Input", "Input" };

    // Output Knob
    juce::Slider outputSlider;
    std::unique_ptr<SliderAttachment> outputSliderAttachment;
    juce::Label outputLabel{ "Output", "Output" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveShaperComponent)
};
