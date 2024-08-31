/*
  ==============================================================================

    FilterComponent.cpp
    Created: 21 Aug 2024 11:21:34am
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId,
    juce::String dbOctID, juce::String driveID, juce::String cutoffID, juce::String resID, juce::String envID)
{
    // Filter select
    juce::StringArray choices1{ "Lpf", "Bpf", "Hpf" };
    setComboBoxDefault(apvts, choices1, typeSelector, filterTypeSelectorId, typeSelectorAttachment);

    // Filter DB/oct
    juce::StringArray choices2{ "12db/oct", "24db/oct" };
    setComboBoxDefault(apvts, choices2, dbOctSelector, dbOctID, dbOctSelectorAttachment);

    setSliderLabelDefault(driveSlider, driveLabel, apvts, driveID, driveSliderAttachment);
    setSliderLabelDefault(cutoffSlider, cutoffLabel, apvts, cutoffID, cutoffSliderAttachment);
    setSliderLabelDefault(resSlider, resLabel, apvts, resID, resSliderAttachment);
    setSliderLabelDefault(envSlider, envLabel, apvts, envID, envSliderAttachment);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void FilterComponent::resized()
{
    // Global 
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Selector menu sizes
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;

    typeSelector.setBounds(10, 10, selectorWidth, selectorHeight);
    dbOctSelector.setBounds(typeSelector.getRight() + padding, 10, selectorWidth, selectorHeight);

    // Knob sizes
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = typeSelector.getBottom() + padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(driveSlider, driveLabel, KnobStartX, KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(cutoffSlider, cutoffLabel, driveSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(resSlider, resLabel, cutoffSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(envSlider, envLabel, resSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
}

void FilterComponent::setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
    juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr <ComboBoxAttachment>& attachment)
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    comboBox.addItemList(choices, 1);
    addAndMakeVisible(comboBox);
    attachment = std::make_unique<ComboBoxAttachment>(apvts, ID, comboBox);
}

void FilterComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void FilterComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
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

void FilterComponent::setTextButtonDefault(juce::TextButton& button, juce::String& label,
    juce::AudioProcessorValueTreeState& apvts, juce::String ID,
    std::unique_ptr<ButtonAttachment>& attachment)
{
    button.setClickingTogglesState(true);
    button.setButtonText(label);
    addAndMakeVisible(button);

    attachment = std::make_unique<ButtonAttachment>(apvts, ID, button);
}




