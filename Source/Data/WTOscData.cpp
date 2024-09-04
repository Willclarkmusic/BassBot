/*
  ==============================================================================

    WTOscData.cpp
    Created: 2 Sep 2024 12:39:02pm
    Author:  BB8

  ==============================================================================
*/
#include "WTOscData.h"

WTOscData::WTOscData() : juce::dsp::Oscillator<float>([](float phase) { return 0.0f; }) // Default lambda
{
}

WTOscData::~WTOscData() {}

void WTOscData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 1;

    prepare(spec);
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.8f);
    oscPan.prepare(spec);
    oscPan.setPan(0);

    waveTableBuffer.setSize(outputChannels, samplesPerBlock, false, false, true);
    waveTableBuffer.clear();

    setFrequency(220.0f);

    initialiseOscillator();
}

void WTOscData::loadWaveTableFile(const int& wtIndex, const juce::StringArray& wtArray)
{
    auto& filePath = wtArray[wtIndex];

    // Load the wavetable from a .wav file
    juce::File file(filePath);
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    if (reader == nullptr)
    {
        DBG("Failed to load WT WAV file: " << filePath);
        return;
    }
    
    waveTableBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples, false, false, true);
    if (reader->lengthInSamples == 0)
    {
        DBG("The WT WAV file is empty: " << filePath);
        return;
    }

    reader->read(&waveTableBuffer, 0, (int)reader->lengthInSamples, 0, true, true);

    if (waveTableBuffer.getNumSamples() > 0)
    {
        auto* channelData = waveTableBuffer.getReadPointer(0); // First channel
        wavetableData.assign(channelData, channelData + waveTableBuffer.getNumSamples());

        initialiseOscillator();
        //DBG("WaveTable initialized after reading.");
    }
    else
    {
        DBG("WaveTable buffer is empty after reading.");
    }
}

void WTOscData::initialiseOscillator()
{
    auto* channelData = waveTableBuffer.getReadPointer(0); // Assuming mono for simplicity
    wavetableData.assign(channelData, channelData + waveTableBuffer.getNumSamples());

    // Normalize the data if there's any signal
    float maxAmplitude = *std::max_element(wavetableData.begin(), wavetableData.end(),
        [](float a, float b) { return std::abs(a) < std::abs(b); });

    if (maxAmplitude > 0.0f)
    {
        for (auto& sample : wavetableData)
        {
            sample /= maxAmplitude;
        }
    }

    // Initialise oscillator without interpolation (just using the nearest sample)
    initialise([&](float phase) -> float
        {
            phase -= std::floor(phase); // Ensure phase is always in the range [0, 1)

            if (wavetableData.empty())
            {
                DBG("Error: Wavetable is empty!");
                return 0.0f;
            }

            // Map phase (0.0 to 1.0) to an index in the wavetable
            int index = static_cast<int>(phase * (wavetableData.size() - 1));

            // Return the nearest sample
            if (index >= 0 && index < wavetableData.size())
            {
                return wavetableData[index];
            }

            return 0.0f;
        });
}

void WTOscData::renderNextBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    jassert(audioBlock.getNumSamples() > 0);

    process(context);

    oscGain.process(context);
    oscPan.process(context);
}

void WTOscData::setWaveFrequency(const int midiNoteNumber)
{
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + trans);
    setFrequency(currentFreq);
    lastMidiNoteNum = midiNoteNumber;
}

void WTOscData::updateOscParams(const float& morph, const int& transposition,
    const float& gain, const float& pan, const int& uniVoices, const float& uniWidth,
    const float& uniSpread)
{
    setOscGain(gain);
    setOscPan(pan);
    setOscTrans(transposition);
    spread = uniSpread;

    //uniVoicesParam = uniVoices;

    //for (int index = 0; index < uniVoicesParam; index++)
    //{
    //    uniOscs[index].setUniWidth(index, pan, uniWidth);
    //}
}

void WTOscData::setMorph(float morphValue)
{
    morphPosition = morphValue;
    // Implement morphing logic between multiple wavetables (if applicable)
}

void WTOscData::setOscGain(const float gain)
{
    oscGain.setGainLinear(gain);
}

void WTOscData::setOscPan(const float pan)
{
    oscPan.setPan(pan);
}

void WTOscData::setOscTrans(const int transposition)
{
    trans = transposition;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition));

    //for (int i = 0; i < maxUnisonVoices; i++)
    //{
    //    uniOscs[i].setUniFrequency(i, juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition), spread);
    //}
}

void WTOscData::resetAll()
{
    reset();
    oscGain.reset();
    oscPan.reset();
}