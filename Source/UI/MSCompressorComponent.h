/*
  ==============================================================================

    MSCompressorComponent.h
    Created: 22 Aug 2024 4:44:18pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/*
*/
class MSCompressorComponent  : public juce::Component
{
public:
    MSCompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String midsGainID, 
        juce::String sidesGainID);
    ~MSCompressorComponent() override;

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

    // Mids Gain
    juce::Slider midsGainSlider;
    std::unique_ptr<SliderAttachment> midsGainAttachment;
    juce::Label midsGainLabel{ "Mids", "Mids" };

    // Sides Gain
    juce::Slider sidesGainSlider;
    std::unique_ptr<SliderAttachment> sidesGainAttachment;
    juce::Label sidesGainLabel{ "Sides", "Sides" };

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MSCompressorComponent)
};
