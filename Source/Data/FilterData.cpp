/*
  ==============================================================================

    FilterData.cpp
    Created: 19 Aug 2024 12:17:27pm
    Author:  BB8

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    filter.prepare(spec);
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float>{block});
}

void FilterData::updateParams(const int filterType, const int filterDBOct, const float frequency,
    const float resonance, const float drive, const float envAmt, const float envelope)
{
    switch (filterDBOct)
    {
    case 0:
        switch (filterType)
        {
        case 0:
            filter.setMode(juce::dsp::LadderFilterMode::LPF12);
            break;
        case 1:
            filter.setMode(juce::dsp::LadderFilterMode::BPF12);
            break;
        case 2:
            filter.setMode(juce::dsp::LadderFilterMode::HPF12);
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (filterType)
        {
        case 0:
            filter.setMode(juce::dsp::LadderFilterMode::LPF24);
            break;
        case 1:
            filter.setMode(juce::dsp::LadderFilterMode::BPF24);
            break;
        case 2:
            filter.setMode(juce::dsp::LadderFilterMode::HPF24);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    float envMod = (envelope - 0.1f) / (0.9f);
    auto modulation = envMod * envAmt;
    float modFreq = frequency + modulation;
    modFreq = std::fmin (std::fmax (modFreq, 20.0f), 20000.0f);

    filter.setCutoffFrequencyHz(modFreq);
    filter.setResonance(resonance);
    filter.setDrive(drive);
}

//void FilterData::modulateCutoff()

void FilterData::reset()
{
    filter.reset();
}
