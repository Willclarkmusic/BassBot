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
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 1;

    currentSampleRate = sampleRate;

    prepare(spec);
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.8f);
    oscPan.prepare(spec);
    oscPan.setPan(0);

    wavBuffer.clear();

    setFrequency(440.0f);

    initialiseOscillator();

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].prepareToPlay(spec, i);
    }

    resetAll();
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
    
    wavBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples, false, false, true);
    if (reader->lengthInSamples == 0)
    {
        DBG("The WT WAV file is empty: " << filePath);
        return;
    }

    reader->read(&wavBuffer, 0, (int)reader->lengthInSamples, 0, true, false);

     //Read Buffer into vector
    if (wavBuffer.getNumSamples() > 0)
    {
        auto* channelData = wavBuffer.getReadPointer(0); // First channel
        wavetableData.assign(channelData, channelData + wavBuffer.getNumSamples());
        
        initialiseOscillator();
        DBG("WaveTable initialized after reading.");
    }
    else
    {
        DBG("WaveTable buffer is empty after reading.");
    }
}

void WTOscData::initialiseOscillator()
{
    auto waveFunc = [&](float phase) -> float
        {
            int index = static_cast<int>(phase * (wavetableSize - 1));
            int morph = static_cast<int>(morphPosition * (wavetableData.size() - wavetableSize));

            if (index >= 0 && index < wavetableSize)
            {
                return wavetableData[index + morph];
            }
            return 0.0f;
        };

    initialise(waveFunc);

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].initialise(waveFunc);
    }
}

void WTOscData::renderNextBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    jassert(audioBlock.getNumSamples() > 0);

    process(context);
    
    for (int i = 0; i < uniVoicesParam; i++)
    {
        uniOscs[i].renderNextBuffer(buffer, startSample, numSamples);
    }

    oscGain.process(context);
    oscPan.process(context);
}

void WTOscData::setWaveFrequency(const int midiNoteNumber)
{
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + trans);
    setFrequency(currentFreq);
    lastMidiNoteNum = midiNoteNumber;

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

void WTOscData::updateOscParams(const float& morph, const int& transposition,
    const float& gain, const float& pan, const int& uniVoices, const float& uniWidth,
    const float& uniSpread)
{
    setMorph(morph);
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

void WTOscData::setMorph(float morphValue)
{
    morphPosition = morphValue;
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

    for (int i = 0; i < maxUnisonVoices; i++)
    {
        uniOscs[i].setUniFrequency(i, juce::MidiMessage::getMidiNoteInHertz(lastMidiNoteNum + transposition), spread);
    }
}

void WTOscData::resetAll()
{
    reset();
    oscGain.reset();
    oscPan.reset();
}


/////With cubic interpolation
//void WTOscData::initialiseOscillator()
//{
//    auto* channelData = waveTableBuffer.getReadPointer(0); // Assuming mono for simplicity
//    wavetableData.assign(channelData, channelData + waveTableBuffer.getNumSamples());
//
//    float maxAmplitude = *std::max_element(wavetableData.begin(), wavetableData.end(),
//        [](float a, float b) { return std::abs(a) < std::abs(b); });
//
//    if (maxAmplitude > 0.0f)  // Normalize the data if there's any signal
//    {
//        for (auto& sample : wavetableData)
//        {
//            sample /= maxAmplitude;
//        }
//    }
//
//    auto cubicInterpolation = [&](float x, float y0, float y1, float y2, float y3) -> float
//        {
//            float a = y3 - y2 - y0 + y1;
//            float b = y0 - y1 - a;
//            float c = y2 - y0;
//            float d = y1;
//            return a * (x * x * x) + b * (x * x) + c * x + d;
//        };
//
//    initialise([&](float phase) -> float
//        {
//            phase -= std::floor(phase); // Ensure phase is always in the range [0, 1)
//
//            if (wavetableData.empty())
//            {
//                DBG("Error: Wavetable is empty!");
//                return 0.0f;
//            }
//
//            float index = phase * (wavetableData.size() - 1);
//            int index0 = static_cast<int>(index);
//            float frac = index - index0;
//
//            // Ensure we have enough samples for cubic interpolation
//            int index1 = (index0 + 1) % wavetableData.size();
//            int indexM1 = (index0 - 1 + wavetableData.size()) % wavetableData.size();
//            int index2 = (index0 + 2) % wavetableData.size();
//
//            if (index0 >= 0 && index0 < wavetableData.size())
//            {
//                float sample = cubicInterpolation(frac, wavetableData[indexM1], wavetableData[index0],
//                    wavetableData[index1], wavetableData[index2]);
//                return sample;
//            }
//            return 0.0f;
//        });
//
////}


//////ORiginal
//void WTOscData::initialiseOscillator()
//{
//    auto* channelData = waveTableBuffer.getReadPointer(0); // Assuming mono for simplicity
//    wavetableData.assign(channelData, channelData + waveTableBuffer.getNumSamples());
//
//    // Normalize the data if there's any signal
//    float maxAmplitude = *std::max_element(wavetableData.begin(), wavetableData.end(),
//        [](float a, float b) { return std::abs(a) < std::abs(b); });
//
//    if (maxAmplitude > 0.0f)
//    {
//        for (auto& sample : wavetableData)
//        {
//            sample /= maxAmplitude;
//        }
//    }
//
//    // Initialise oscillator without interpolation (just using the nearest sample)
//    initialise([&](float phase) -> float
//        {
//            phase -= std::floor(phase); // Ensure phase is always in the range [0, 1)
//
//            if (wavetableData.empty())
//            {
//                DBG("Error: Wavetable is empty!");
//                return 0.0f;
//            }
//
//            // Map phase (0.0 to 1.0) to an index in the wavetable
//            int index = static_cast<int>(phase * (wavetableData.size() - 1));
//
//            // Return the nearest sample
//            if (index >= 0 && index < wavetableData.size())
//            {
//                return wavetableData[index];
//            }
//
//            return 0.0f;
//        });
//}



//// Custom fully
//void WTOscData::initialiseOscillator()
//{
//    for (int i = 0; i < wavBuffer.getNumSamples(); i += wavetableSize)
//    {
//        juce::AudioBuffer<float> wavetableCycle;
//        wavetableCycle.setSize(wavBuffer.getNumChannels(), wavetableSize);
//        wavetableCycle.copyFrom(0, 0, wavBuffer, 0, i, wavetableSize);
//
//        // Store this cycle as a wavetable
//        wavetables.push_back(wavetableCycle);
//    }
//}

//
//float WTOscData::getNextSample()
//{
//    // 1. Calculate the current phase position
//    float phaseIncrement = frequency / currentSampleRate;  // Frequency relative to sample rate
//    phase += phaseIncrement;                        // Increment the phase
//
//    // Wrap phase in the range [0.0, 1.0]
//    if (phase >= 1.0f)
//        phase -= 1.0f;
//
//    // 2. Determine the current wavetable index based on the phase
//    int tableIndex = static_cast<int>(phase * (wavetableSize - 1));
//    float frac = (phase * (wavetableSize - 1)) - tableIndex;  // Fractional part for interpolation
//
//    // 3. Fetch samples from the current wavetable (using linear interpolation)
//    float sample1 = wavBuffer.getSample(0, tableIndex);  // Current sample
//    float sample2 = wavBuffer.getSample(0, (tableIndex + 1) % wavetableSize);  // Next sample
//
//    // Linear interpolation between the two samples
//    float interpolatedSample = (1.0f - frac) * sample1 + frac * sample2;
//
//    return interpolatedSample;
//}