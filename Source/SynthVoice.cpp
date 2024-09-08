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
    
    ahdsr1.noteOn();
    ahdsr2.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    ahdsr1.noteOff();
    ahdsr2.noteOff();

    if (!allowTailOff || !ahdsr1.isActive())
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

    ahdsr1.setSampleRate(sampleRate);
    ahdsr2.setSampleRate(sampleRate);

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    for (int v = 0; v < numVoicesToProcess; v++)
    {
        osc1[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);
        osc2[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);
        oscSub[v].prepareToPlay(spec, sampleRate, samplesPerBlock, outputChannels);       
    }

    filter1.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    filter2.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    
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
    osc1FXBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    // mod activations
    //ahdsr2.applyEnvelopeToBuffer(outputBuffer, startSample, osc1Buffer.getNumSamples());

    osc1Buffer.clear();
    osc1FXBuffer.clear();

    for (int v = 0; v < numVoicesToProcess; v++) // Voices
        osc1[v].renderNextBuffer(osc1Buffer, startSample, numSamples);

    juce::dsp::AudioBlock<float> osc1Block{ osc1Buffer };

    ahdsr1.applyEnvelopeToBuffer(osc1Buffer, startSample, osc1Buffer.getNumSamples());

    filter1.process(osc1Buffer);

    for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++)
    {
        osc1FXBuffer.copyFrom(ch, 0, osc1Buffer, ch, 0, numSamples);
    }

    convDist1.process(osc1FXBuffer);
    reverb1.renderNextBlock(osc1FXBuffer);

    //Osc2 Audio Bus
    osc2Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2FXBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2Buffer.clear();
    osc2FXBuffer.clear();

    for (int v = 0; v < numVoicesToProcess; v++)
        osc2[v].renderNextBuffer(osc2Buffer, startSample, numSamples);

    juce::dsp::AudioBlock<float> osc2Block{ osc2Buffer };

    ahdsr1.applyEnvelopeToBuffer(osc2Buffer, startSample, osc2Buffer.getNumSamples());

    filter2.process(osc2Buffer);

    for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++)
    {
        osc2FXBuffer.copyFrom(ch, 0, osc2Buffer, ch, 0, numSamples);
    }

    //OscSub Audio Bus
    oscSubBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    oscSubBuffer.clear();

    for (int v = 0; v < numVoicesToProcess; v++)
        oscSub[v].renderNextBuffer(oscSubBuffer);

    ahdsr1.applyEnvelopeToBuffer(oscSubBuffer, startSample, oscSubBuffer.getNumSamples());

    waveShaper1.renderNextBuffer(oscSubBuffer);

    // Add OSC chains to output buffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, osc1FXBuffer, channel, 0, numSamples, 0.2f);
        outputBuffer.addFrom(channel, startSample, osc2FXBuffer, channel, 0, numSamples, 0.4f);
        outputBuffer.addFrom(channel, startSample, oscSubBuffer, channel, 0, numSamples, 0.2f);

        if (! ahdsr1.isActive())
            clearCurrentNote();
    }
}

//void SynthVoice::processSubBus(juce::AudioBuffer& subBuffer)
//{
//
//}

void SynthVoice::updateFilter1(const int filterType, const int filterDBOct, const float frequency,
    const float resonance, const float drive, const float envAmt)
{
    float modEnv2 = ahdsr2.getNextSample();
    filter1.updateParams(filterType, filterDBOct, frequency, resonance, drive, envAmt, modEnv2);
}

void SynthVoice::updateFilter2(const int filterType, const int filterDBOct, const float frequency,
    const float resonance, const float drive, const float envAmt)
{
    float modEnv2 = ahdsr2.getNextSample();
    filter2.updateParams(filterType, filterDBOct, frequency, resonance, drive, envAmt, modEnv2);
}

void SynthVoice::reset()
{
    ahdsr1.reset();
    ahdsr2.reset();
}