/*
  ==============================================================================

    FilterComponent.h
    Created: 21 Aug 2024 11:21:34am
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);

    void setTextButtonDefault(juce::TextButton& button, juce::String& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<ButtonAttachment>& attachment);

    void FilterComponent::setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
        juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr <ComboBoxAttachment>& attachment);


    // Filter type selector
    juce::ComboBox typeSelector;
    std::unique_ptr<ComboBoxAttachment> typeSelectorAttachment;

    // DB per OCt button
    juce::ComboBox dbOctSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> dbOctSelectorAttachment;

    // Drive Knob
    juce::Slider driveSlider;
    std::unique_ptr<SliderAttachment> driveSliderAttachment;
    juce::Label driveLabel{ "Drive", "Drive" };

    // Cutoff knob
    juce::Slider cutoffSlider;
    std::unique_ptr<SliderAttachment> cutoffSliderAttachment;
    juce::Label cutoffLabel{ "Cutoff", "Cutoff" };

    // Resonance Knob
    juce::Slider resSlider;
    std::unique_ptr<SliderAttachment> resSliderAttachment;
    juce::Label resLabel{ "Res", "Res" };

    // Resonance Knob
    juce::Slider envSlider;
    std::unique_ptr<SliderAttachment> envSliderAttachment;
    juce::Label envLabel{ "Env", "Env" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};

