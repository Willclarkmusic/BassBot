/*
  ==============================================================================

    Reverb1Component.cpp
    Created: 24 Aug 2024 3:34:36pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Reverb1Component.h"

//==============================================================================
Reverb1Component::Reverb1Component(juce::AudioProcessorValueTreeState& apvts, juce::String sizeID, 
    juce::String dampID, juce::String widthID, juce::String wetID, juce::String dryID)
{
    setSliderLabelDefault(sizeSlider, sizeLabel, apvts, sizeID, sizeAttachment);
    setSliderLabelDefault(dampSlider, dampLabel, apvts, dampID, dampAttachment);
    setSliderLabelDefault(widthSlider, widthLabel, apvts, widthID, widthAttachment);
    setSliderLabelDefault(wetSlider, wetLabel, apvts, wetID, wetAttachment);
    setSliderLabelDefault(drySlider, dryLabel, apvts, dryID, dryAttachment);
}

Reverb1Component::~Reverb1Component()
{
}

void Reverb1Component::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void Reverb1Component::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // OSC macro, trans and gain draw
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(sizeSlider, sizeLabel, KnobStartX, KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

    setBoundsSliderWLabel(dampSlider, dampLabel, sizeSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

    setBoundsSliderWLabel(widthSlider, widthLabel, dampSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

    setBoundsSliderWLabel(wetSlider, wetLabel, widthSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

    setBoundsSliderWLabel(drySlider, dryLabel, wetSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);


}

void Reverb1Component::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void Reverb1Component::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
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