/*
  ==============================================================================

    ConvDistortionComponent.cpp
    Created: 23 Aug 2024 4:59:24pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ConvDistortionComponent.h"

//==============================================================================
ConvDistortionComponent::ConvDistortionComponent(BeastySynth1AudioProcessor& processor, 
    juce::AudioProcessorValueTreeState& apvts, juce::String IRLoadID, 
    juce::String dryWetID, juce::String gainID) : audioProcessor(processor)
{
    // IR select init
    juce::StringArray choices1{ audioProcessor.getIRDistFiles()};
    for (int i = 0; i < choices1.size(); i++)
    {
        choices1.set(i, juce::File(choices1[i]).getFileNameWithoutExtension());
    }

    setComboBoxDefault(apvts, choices1, irSelector, IRLoadID, irSelectorAttachment);
    updateIRComboBoxItems();

    setSliderLabelDefault(dryWetSlider, dryWetLabel, apvts, dryWetID, dryWetSliderAttachment);
    setSliderLabelDefault(gainSlider, gainLabel, apvts, gainID, gainSliderAttachment);
}

ConvDistortionComponent::~ConvDistortionComponent()
{
}

void ConvDistortionComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void ConvDistortionComponent::resized()
{
    // Global 
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Selector menu sizes
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;

    irSelector.setBounds(10, 10, selectorWidth, selectorHeight);

    // Knob sizes
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = irSelector.getBottom() + padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    setBoundsSliderWLabel(dryWetSlider, dryWetLabel, KnobStartX, KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);
    setBoundsSliderWLabel(gainSlider, gainLabel, dryWetSlider.getRight(), KnobStartY, defKnobHeight,
        labelWidth, labelHeight, padding);

}

void ConvDistortionComponent::updateIRComboBoxItems()
{
    juce::StringArray choices1{ audioProcessor.getIRDistFiles() };
    for (int i = 0; i < choices1.size(); i++)
    {
        choices1.set(i, juce::File(choices1[i]).getFileNameWithoutExtension());
    }

    // Clear any existing items
    irSelector.clear();

    // Add items to the ComboBox
    for (const auto& filePath : choices1)
    {
        irSelector.addItem(filePath, irSelector.getNumItems() + 1);
    }

    // Optionally, select the first item
    if (irSelector.getNumItems() > 0)
        irSelector.setSelectedId(1);
}

void ConvDistortionComponent::setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
    juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr<ComboBoxAttachment>& attachment)
{
    comboBox.addItemList(choices, 1);
    addAndMakeVisible(comboBox);
    attachment = std::make_unique<ComboBoxAttachment>(apvts, ID, comboBox);
}

void ConvDistortionComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, 
    int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void ConvDistortionComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
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

