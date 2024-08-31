/*
  ==============================================================================

    MSCompressorComponent.cpp
    Created: 22 Aug 2024 4:44:18pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MSCompressorComponent.h"

//==============================================================================
MSCompressorComponent::MSCompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String midsGainID,
    juce::String sidesGainID)
{
    setSliderLabelDefault(midsGainSlider, midsGainLabel, apvts, midsGainID, midsGainAttachment);
    setSliderLabelDefault(sidesGainSlider, sidesGainLabel, apvts, sidesGainID, sidesGainAttachment);
}

MSCompressorComponent::~MSCompressorComponent()
{
}

void MSCompressorComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void MSCompressorComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // OSC macro, trans and gain draw
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(midsGainSlider, midsGainLabel, KnobStartX, KnobStartY, defKnobHeight, 
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(sidesGainSlider, sidesGainLabel, midsGainSlider.getRight(), KnobStartY, 
        defKnobHeight, labelWidth, labelHeight, padding);

}

void MSCompressorComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void MSCompressorComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
    juce::AudioProcessorValueTreeState& apvts, juce::String ID,
    std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, ID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}