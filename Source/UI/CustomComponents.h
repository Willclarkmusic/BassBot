/*
  ==============================================================================

    CustomComponents.h
    Created: 30 Aug 2024 4:20:19pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomComponents  : public juce::Component
{
public:
    CustomComponents();
    ~CustomComponents() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComponents)
};

class SectionTitleLabel : public juce::Component
{
public:
    void createSectionTitle(juce::String labelString);
    void setBoundsSectionTitle(int xPos, int yPos, int charCount);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int boundsWidth = 80;
    int boundsHeight = 25;
    int labelWidth = 80;
    int labelHeight = 20;
    int padding = 5;

    juce::Label label;
};


class AnimatedKnobMedium : public juce::Component
{
public:
    void createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& waveSelectorID, juce::String labelString);
    void setBoundsKnobWithLabel(int xPos, int yPos);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int knobRadius = 80;
    int labelHeight = 15;
    int labelWidth = 80;
    int padding = 5;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    juce::Label label;
};

class AnimatedKnobSmall : public juce::Component
{
public:
    void createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& waveSelectorID, juce::String labelString);
    void setBoundsKnobWithLabel(int xPos, int yPos);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int knobRadius = 50;
    int labelHeight = 10;
    int labelWidth = 50;
    int padding = 5;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    juce::Label label;
};

class ComboBoxMedium : public juce::Component
{
public:
    void createComboBox(juce::AudioProcessorValueTreeState& apvts, juce::String& comboBoxID, juce::StringArray& choices);
    void setBoundsComboBox(int xPos, int yPos);
    void paint(juce::Graphics& g) override;
    juce::ComboBox& getComboBox() { return comboBox; }

private:
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    int padding = 5;
    int selectorWidth = 60;
    int selectorHeight = 20;

    juce::ComboBox comboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachment;
    juce::StringArray choices;
};

class SliderBoxMedium : public juce::Component
{
public:
    void createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& waveSelectorID, juce::String labelString);
    void setBoundsKnobWithLabel(int xPos, int yPos);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int boundsWidth = 80;
    int boundsHeight = 40;
    int knobWidth = 60;
    int knobHeight = 15;
    int labelWidth = 80;
    int labelHeight = 15;

    int padding = 5;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    juce::Label label;
};

class SliderBoxSmall : public juce::Component
{
public:
    void createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& waveSelectorID, juce::String labelString);
    void setBoundsKnobWithLabel(int xPos, int yPos);
    void paint(juce::Graphics& g) override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    int boundsWidth = 45;
    int boundsHeight = 25;
    int knobWidth = 40;
    int knobHeight = 15;
    int labelWidth = 40;
    int labelHeight = 10;

    int padding = 5;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    juce::Label label;
};