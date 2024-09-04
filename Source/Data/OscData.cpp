/*
  ==============================================================================

    OscData.cpp
    Created: 14 Aug 2024 11:46:20pm
    Author:  BB8

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    prepare(spec);
    //fmOsc.prepare(spec);
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.8f);
    oscPan.prepare(spec);
    oscPan.setPan(0);
    
    initialise(currentWaveType);

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].prepareToPlay(spec, i);
    }
}

float OscData::processNextSample(float input)  // depricated
{
    //fmModulator = fmOsc.processSample(input) * fmDepth;
    return oscGain.processSample(processSample(input));
}

void OscData::renderNextBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock{ buffer };

    jassert(audioBlock.getNumSamples() > 0);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    process(context);

    for (int i = 0; i < uniVoicesParam; i++)
    {
        uniOscs[i].renderNextBuffer(buffer, startSample, numSamples);
    }
    oscGain.process(context);
    oscPan.process(context);
}

void OscData::updateOscParams(const int& oscWaveChoice, const float& osc1Macro, const int& transposition, 
    const float& gain, const float& pan, const int& uniVoices, const float& uniWidth, const float& uniSpread)
{
    setWaveType(oscWaveChoice);
    setOscGain(gain);
    setOscPan(pan);
    setOscTrans(transposition);
    spread = uniSpread;
    uniVoicesParam = uniVoices;

    for (int index = 0; index < uniVoicesParam; index++)
    {
        uniOscs[index].setUniWidth(index, pan, uniWidth);
    }
}

void OscData::setOscGain(const float gain)
{
    oscGain.setGainLinear(gain);
}

void OscData::setOscPan(const float pan)
{
    oscPan.setPan(pan);
}

void OscData::setOscTrans(const int transposition)
{
    trans = transposition;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition));
    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].setUniFrequency(i, juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition), spread);
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    lastMidiNoteNum = midiNoteNumber;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + trans);
    setFrequency(currentFreq > 0 ? currentFreq : currentFreq * -1.0f);

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        if (i % 2 == 0)
        {
            uniOscs[i].setUniFrequency(i, currentFreq + (float(i) * 0.1f), spread);
        }
        else
        {
            uniOscs[i].setUniFrequency(i, currentFreq - (float(i) * 0.1f), spread);
        }
    }
    
}

void OscData::setWaveType(const int choice)
{   
    switch (choice)
    {
    case 0:
        // Sin
        currentWaveType = [](float x) { return std::sin(x); };
        initialise(currentWaveType);
        break;
    case 1:
        // Saw
        currentWaveType = [](float x) { return x / juce::MathConstants<float>::pi; };
        initialise(currentWaveType);
        break;
    case 2:
        // Squ
        currentWaveType = [](float x) { return x < 0.0f ? -1.0f : 1.0f; };
        initialise(currentWaveType);
        break;
    case 3:
        currentWaveType = [](float x) { return std::sin(x); };
        initialise(currentWaveType);
        break;
    default:
        //jassertfalse;
        break;
    }

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].initialise(currentWaveType);
    }
}

void OscData::resetAll()
{
    reset();
    //fmOsc.reset();
    oscGain.reset();
}




