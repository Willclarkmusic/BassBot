/*
  ==============================================================================

    PresetManager.h
    Created: 31 Aug 2024 1:45:57pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Service
{
    class PresetManager
    {
    public:
        static const juce::File defaultDirectory;
        static const juce::String extension;

        PresetManager(juce::AudioProcessorValueTreeState& apvts);

        void savePreset(const juce::String& presetName);
        void deletePreset(const juce::String& presetName);
        void loadPreset(const juce::String& presetName);
        int loadNextPreset();
        int loadPrevPreset();
        juce::StringArray getAllPresets() const;
        juce::String getCurrentPreset() const;

    private:
        juce::AudioProcessorValueTreeState& valueTreeState;
        juce::String currentPreset;


    };
}