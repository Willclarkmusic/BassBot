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
    convDistortionTitle.createSectionTitle("Convolution");
    addAndMakeVisible(convDistortionTitle);
    // IR select init
    juce::StringArray choices1{ audioProcessor.getIRDistFiles() };
    for (int i = 0; i < choices1.size(); i++)
    {
        choices1.set(i, juce::File(choices1[i]).getFileNameWithoutExtension());
    }

    irSelector.createComboBox(apvts, IRLoadID, choices1);
    addAndMakeVisible(irSelector);

    dryWetKnob.createKnobWithLabel(apvts, dryWetID, "Dry/Wet");
    addAndMakeVisible(dryWetKnob);
    gainKnob.createKnobWithLabel(apvts, gainID, "Drive");
    addAndMakeVisible(gainKnob);
}

ConvDistortionComponent::~ConvDistortionComponent()
{
}

void ConvDistortionComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void ConvDistortionComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    convDistortionTitle.setBoundsSectionTitle(padding, 8, 5);

    // Selector menu sizes
    irSelector.setBoundsComboBox(convDistortionTitle.getRight(), 8);

    // Knob sizes
    const auto KnobStartX = padding;
    const auto KnobStartY = irSelector.getBottom();
    dryWetKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    gainKnob.setBoundsKnobWithLabel(dryWetKnob.getRight(), KnobStartY);
}

void ConvDistortionComponent::updateIRComboBoxItems()
{
    auto& irComboBox = irSelector.getComboBox();


    juce::StringArray choices1{ audioProcessor.getIRDistFiles() };
    for (int i = 0; i < choices1.size(); i++)
    {
        choices1.set(i, juce::File(choices1[i]).getFileNameWithoutExtension());
    }

    // Clear any existing items
    irComboBox.clear();

    // Add items to the ComboBox
    for (const auto& filePath : choices1)
    {
        irComboBox.addItem(filePath, irComboBox.getNumItems() + 1);
    }

    // Optionally, select the first item
    if (irComboBox.getNumItems() > 0)
        irComboBox.setSelectedId(1);
}








