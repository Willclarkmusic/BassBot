/*
  ==============================================================================

    SynthVoice.cpp
    Created: 11 Aug 2024 3:24:54pm
    Author:  BB8

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    for (int v = 0; v < numVoicesToProcess; v++)
    {
        osc1[v].setWaveFrequency(midiNoteNumber);
        osc2[v].setWaveFrequency(midiNoteNumber);
        oscSub[v].setWaveFrequency(midiNoteNumber - 12);
    }
    
    adsr1.noteOn();
    adsr2.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr1.noteOff();
    adsr2.noteOff();

    if (!allowTailOff || !adsr1.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheenValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();

    adsr1.setSampleRate(sampleRate);
    adsr2.setSampleRate(sampleRate);

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    for (int v = 0; v < numVoicesToProcess; v++)
    {
        osc1[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);
        osc2[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);
        oscSub[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);
        
    }

    osc1Gain.prepare(spec);
    osc1Gain.setGainLinear(0.6f);

    osc2Gain.prepare(spec);
    osc2Gain.setGainLinear(0.6f);

    oscSubGain.prepare(spec);
    oscSubGain.setGainLinear(0.6f);

    filter1.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    
    convDist1.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    waveShaper1.prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);

    reverb1.prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);

    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    //if (! isVoiceActive())
    //    return;

    //Osc1 Audio Bus
    osc1Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    // mod activations
    adsr2.applyEnvelopeToBuffer(outputBuffer, 0, osc1Buffer.getNumSamples());

    osc1Buffer.clear();

    for (int v = 0; v < numVoicesToProcess; v++) // process each oscillator voice
        osc1[v].renderNextBuffer(osc1Buffer, startSample, numSamples);

    juce::dsp::AudioBlock<float> osc1Block{ osc1Buffer };
    osc1Gain.process(juce::dsp::ProcessContextReplacing<float>(osc1Block));

    adsr1.applyEnvelopeToBuffer(osc1Buffer, 0, osc1Buffer.getNumSamples());

    filter1.process(osc1Buffer);
    convDist1.process(osc1Buffer);
    reverb1.renderNextBlock(osc1Buffer);


    //Osc2 Audio Bus
    osc2Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2Buffer.clear();

    for (int v = 0; v < numVoicesToProcess; v++) // process each oscillator voice
        osc2[v].renderNextBuffer(osc2Buffer, startSample, numSamples);

    juce::dsp::AudioBlock<float> osc2Block{ osc2Buffer };
    osc2Gain.process(juce::dsp::ProcessContextReplacing<float>(osc2Block));

    adsr1.applyEnvelopeToBuffer(osc2Buffer, 0, osc2Buffer.getNumSamples());


    //OscSub Audio Bus
    oscSubBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    oscSubBuffer.clear();

    juce::dsp::AudioBlock<float> oscSubBlock{ oscSubBuffer };

    for (int v = 0; v < numVoicesToProcess; v++)
        oscSub[v].renderNextBlock(oscSubBlock);

    oscSubGain.process(juce::dsp::ProcessContextReplacing<float>(oscSubBlock));

    adsr1.applyEnvelopeToBuffer(oscSubBuffer, 0, oscSubBuffer.getNumSamples());

    waveShaper1.renderNextBlock(oscSubBlock);


    // Add OSC chains to output buffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, osc1Buffer, channel, 0, numSamples, 0.3f); // Gain on the end for mixer
        outputBuffer.addFrom(channel, startSample, osc2Buffer, channel, 0, numSamples, 0.3f); // Gain on the end for mixer
        outputBuffer.addFrom(channel, startSample, oscSubBuffer, channel, 0, numSamples, 0.3f);

        if (! adsr1.isActive())
            clearCurrentNote();
    }

}

void SynthVoice::updateFilter(const int filterType, const int filterDBOct, const float frequency,
    const float resonance, const float drive, const float envAmt)
{
    float modEnv2 = adsr2.getNextSample();
    filter1.updateParams(filterType, filterDBOct, frequency, resonance, drive, envAmt, modEnv2);
}

void SynthVoice::reset()
{
    osc1Gain.reset();
    osc2Gain.reset();
    oscSubGain.reset();
    adsr1.reset();
    adsr2.reset();
    //filterAdsr.reset();
}