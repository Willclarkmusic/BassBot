/*
  ==============================================================================

    SynthSound.h
    Created: 11 Aug 2024 3:25:24pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }

};
