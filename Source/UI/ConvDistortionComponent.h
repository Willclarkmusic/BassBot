/*
  ==============================================================================

    ConvDistortionComponent.h
    Created: 23 Aug 2024 4:59:24pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "..\PluginProcessor.h"

//==============================================================================
/*
*/
class ConvDistortionComponent  : public juce::Component
{
public:
    ConvDistortionComponent(BeastySynth1AudioProcessor& processor, juce::AudioProcessorValueTreeState& apvts,
        juce::String IRLoadID, juce::String dryWetID, juce::String gainID);
    ~ConvDistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BeastySynth1AudioProcessor& audioProcessor;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    void setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
        juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr <ComboBoxAttachment>& attachment);

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);


    // IR selector
    juce::ComboBox irSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> irSelectorAttachment;

    void updateIRComboBoxItems();


    // Dry Wet Mix 
    juce::Slider dryWetSlider;
    std::unique_ptr<SliderAttachment> dryWetSliderAttachment;
    juce::Label dryWetLabel{ "Dry/Wet", "Dry/Wet" };

    // Gain 
    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    juce::Label gainLabel{ "Gain", "Gain" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvDistortionComponent)
};
