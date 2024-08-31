/*
  ==============================================================================

    OscSubData.cpp
    Created: 23 Aug 2024 4:02:20pm
    Author:  BB8

  ==============================================================================
*/

#include "OscSubData.h"

void OscSubData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    prepare(spec);
    setFrequency(220.f);
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.8f);

    initialise([](float x) { return std::sin(x); });
}

float OscSubData::processNextSample(float input)
{
    return oscGain.processSample(processSample(input));
}

void OscSubData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    oscGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscSubData::updateOscParams(const int oscWaveChoice, const float osc1Macro, const int transposition, const float gain)
{
    setWaveType(oscWaveChoice);
    setOscGain(gain);
    setOscTrans(transposition);
}

void OscSubData::setOscGain(const float gain)
{
    oscGain.setGainLinear(gain);
}

void OscSubData::setOscTrans(const int transposition)
{
    trans = transposition;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition));
}

void OscSubData::setWaveFrequency(const int midiNoteNumber)
{
    lastMidiNoteNum = midiNoteNumber;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + trans);
    setFrequency(currentFreq > 0 ? currentFreq : currentFreq * -1.0f);
}

void OscSubData::setWaveType(const int choice)
{
    switch (choice)
    {
    case 0:
        // Sin
        initialise([](float x) { return std::sin(x); });
        break;

    case 1:
        // Squ
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f;; });
        break;

    default:
        //jassertfalse;
        break;
    }
    // WaveTypes
    // return std::sin (x)                          //Sin
    // return x / juce::MathConstants<float>::pi    //Saw
    // return x <0.0f ? -1.0f : 1.0f;               //Squ
}

void OscSubData::resetAll()
{
    reset();
    oscGain.reset();
}