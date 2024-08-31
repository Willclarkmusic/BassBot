/*
  ==============================================================================

    WaveShaperComponent.cpp
    Created: 23 Aug 2024 12:16:27pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveShaperComponent.h"

//==============================================================================
WaveShaperComponent::WaveShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String inputID, 
    juce::String outputID, juce::String typeID)
{
    // Type select
    juce::StringArray choices{ "Tan", "Sin", "Cos" };
    waveTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(waveTypeSelector);
    waveTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (apvts, typeID, waveTypeSelector);

    setSliderLabelDefault(inputSlider, inputLabel, apvts, inputID, inputSliderAttachment);
    setSliderLabelDefault(outputSlider, outputLabel, apvts, outputID, outputSliderAttachment);

}

WaveShaperComponent::~WaveShaperComponent()
{
}

void WaveShaperComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void WaveShaperComponent::resized()
{
    // Global 
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Wave Selector menu
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;

    waveTypeSelector.setBounds((bounds.getWidth() / 3) * 2, 10, selectorWidth, selectorHeight);

    // Knob sizes
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = waveTypeSelector.getBottom() + padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(inputSlider, inputLabel, KnobStartX, KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(outputSlider, outputLabel, inputSlider.getRight(), KnobStartY,
        defKnobHeight, labelWidth, labelHeight, padding);
}

void WaveShaperComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void WaveShaperComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
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