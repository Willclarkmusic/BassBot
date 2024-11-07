/*
  ==============================================================================

    LFO1Component.h
    Created: 21 Sep 2024 3:19:56pm
    Author:  BB8

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LFO1Component  : public juce::Component
{
public:
    LFO1Component();
    ~LFO1Component() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO1Component)
};
