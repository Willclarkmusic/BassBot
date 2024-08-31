/*
  ==============================================================================

    ADSR1Component.cpp
    Created: 14 Aug 2024 9:41:13pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR1Component.h"

//==============================================================================
ADSR1Component::ADSR1Component(juce::AudioProcessorValueTreeState& apvts, juce::String attackID, 
    juce::String decayID, juce::String sustainID, juce::String releaseID)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    setSliderLabelSmall(attack1Slider, attack1Label, apvts, attackID, attack1Attachment);
    setSliderLabelSmall(decay1Slider, decay1Label, apvts, decayID, decay1Attachment);
    setSliderLabelSmall(sustain1Slider, sustain1Label, apvts, sustainID, sustain1Attachment);
    setSliderLabelSmall(release1Slider, release1Label, apvts, releaseID, release1Attachment);
}

ADSR1Component::~ADSR1Component()
{
}

void ADSR1Component::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void ADSR1Component::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 5;

    const auto sliderStartX = 0;
    const auto sliderStartY = 10;
    const auto smKnobSize = 60;
    const auto textBoxWidth = 60;
    const auto textBoxHeight = 10;

    setBoundsSliderWLabel(attack1Slider, attack1Label, sliderStartX, sliderStartY, smKnobSize, textBoxWidth, textBoxHeight, padding);
    setBoundsSliderWLabel(decay1Slider, decay1Label, attack1Slider.getRight(), sliderStartY, smKnobSize, textBoxWidth,
        textBoxHeight, padding);
    setBoundsSliderWLabel(sustain1Slider, sustain1Label, decay1Slider.getRight(), sliderStartY, smKnobSize, textBoxWidth, 
        textBoxHeight, padding);
    setBoundsSliderWLabel(release1Slider, release1Label, sustain1Slider.getRight(), sliderStartY, smKnobSize, textBoxWidth, 
        textBoxHeight, padding);
}

void ADSR1Component::setSliderParamsDefault(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(slider);
}

void ADSR1Component::setSliderLabelSmall(juce::Slider& slider, juce::Label& label,
    juce::AudioProcessorValueTreeState& apvts, juce::String ID,
    std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 15);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, ID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}

void ADSR1Component::setTextButtonDefault(juce::TextButton& button, juce::String& label,
    juce::AudioProcessorValueTreeState& apvts, juce::String ID,
    std::unique_ptr<ButtonAttachment>& attachment)
{
    button.setClickingTogglesState(true);
    button.setButtonText(label);
    addAndMakeVisible(button);

    attachment = std::make_unique<ButtonAttachment>(apvts, ID, button);
}

void ADSR1Component::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, 
    int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}