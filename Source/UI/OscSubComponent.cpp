/*
  ==============================================================================

    OscSubComponent.cpp
    Created: 23 Aug 2024 4:02:41pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscSubComponent.h"

//==============================================================================
OscSubComponent::OscSubComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId,
    juce::String macroID, juce::String transID, juce::String gainID)
{
    // Wave select
    juce::StringArray choices{ "Sin", "Saw", "Squ" };
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (apvts, waveSelectorId, oscWaveSelector);

    // Osc Pitch and gain control
    setSliderLabelDefault(oscMacroSlider, oscMacroLabel, apvts, macroID, oscMacroAttachment);
    setSliderLabelDefault(oscTransSlider, oscTransLabel, apvts, transID, oscTransAttachment);
    setSliderLabelDefault(oscGainSlider, oscGainLabel, apvts, gainID, oscGainAttachment);

}

OscSubComponent::~OscSubComponent()
{
}

void OscSubComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void OscSubComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Wave Selector menu
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;

    oscWaveSelector.setBounds((bounds.getWidth() / 3) * 2, 10, selectorWidth, selectorHeight);

    // OSC macro, trans and gain draw
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = oscWaveSelector.getBottom() + padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(oscMacroSlider, oscMacroLabel, KnobStartX, KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(oscTransSlider, oscTransLabel, oscMacroSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(oscGainSlider, oscGainLabel, oscTransSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

}

void OscSubComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void OscSubComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
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