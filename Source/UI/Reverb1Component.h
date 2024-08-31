/*
  ==============================================================================

    Reverb1Component.h
    Created: 24 Aug 2024 3:34:36pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos,
        int sliderWH, int labelW, int labelH, int padding);

    // Transpose
    juce::Slider sizeSlider;
    std::unique_ptr<SliderAttachment> sizeAttachment;
    juce::Label sizeLabel{ "Size", "Size" };

    // Transpose
    juce::Slider dampSlider;
    std::unique_ptr<SliderAttachment> dampAttachment;
    juce::Label dampLabel{ "Damp", "Damp" };

    // Transpose
    juce::Slider widthSlider;
    std::unique_ptr<SliderAttachment> widthAttachment;
    juce::Label widthLabel{ "Width", "Width" };

    // Transpose
    juce::Slider drySlider;
    std::unique_ptr<SliderAttachment> dryAttachment;
    juce::Label dryLabel{ "Dry", "Dry" };

    // Transpose
    juce::Slider wetSlider;
    std::unique_ptr<SliderAttachment> wetAttachment;
    juce::Label wetLabel{ "Wet", "Wet" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Reverb1Component)
};
