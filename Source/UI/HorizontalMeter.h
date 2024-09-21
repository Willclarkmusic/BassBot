/*
  ==============================================================================

    HorizontalMeter.h
    Created: 21 Sep 2024 12:29:22am
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>



class HorizontalMeter : public juce::Component
{
public:
    HorizontalMeter() {}
    ~HorizontalMeter() {}
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        g.setColour(juce::Colours::white.withBrightness(0.2f));
        g.fillRoundedRectangle(bounds, 5.0f);

        g.setGradientFill(gradient);
        const auto scaledX = juce::jmap(level, -60.0f, 6.0f, 0.0f, static_cast<float>(getWidth()));
        g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
    }

    void resized() override
    {
        const auto bounds = getLocalBounds().toFloat();
        gradient = juce::ColourGradient(
            juce::Colours::aquamarine,
            bounds.getBottomLeft(),
            juce::Colours::red,
            bounds.getBottomRight(),
            false
        );
        gradient.addColour(0.8, juce::Colours::yellow);
    }

    void setMeterLevel(const float value) { level = value; }

private:
    float level = -60.0f;
    juce::ColourGradient gradient;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HorizontalMeter)

};
