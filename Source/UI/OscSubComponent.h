/*
  ==============================================================================

    OscSubComponent.h
    Created: 23 Aug 2024 4:02:41pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);

    // Osc wave select
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    // Macro
    juce::Slider oscMacroSlider;
    std::unique_ptr<SliderAttachment> oscMacroAttachment;
    juce::Label oscMacroLabel{ "Macro", "Macro" };

    // Transpose
    juce::Slider oscTransSlider;
    std::unique_ptr<SliderAttachment> oscTransAttachment;
    juce::Label oscTransLabel{ "Trans", "Trans" };

    // Gain
    juce::Slider oscGainSlider;
    std::unique_ptr<SliderAttachment> oscGainAttachment;
    juce::Label oscGainLabel{ "Gain", "Gain" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSubComponent)
};
