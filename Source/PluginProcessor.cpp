/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BeastySynth1AudioProcessor::BeastySynth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams()),
                        presetManager(apvts)
#endif
{
    synth.addSound(new SynthSound());

    // Polyphony
    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
    }

    //OSC 1
    apvts.addParameterListener("OSC1WAVETYPE", this);

    //OSC 2
    apvts.addParameterListener("OSC2WAVETABLE", this);
    apvts.addParameterListener("OSC2MORPH", this);
    apvts.addParameterListener("OSC2TRANS", this);
    apvts.addParameterListener("OSC2GAIN", this);
    apvts.addParameterListener("OSC2PAN", this);
    apvts.addParameterListener("OSC2UNI", this);
    apvts.addParameterListener("OSC2WIDTH", this); 

    // Convolusion distortion
    apvts.addParameterListener("IRLOAD1", this);
    apvts.addParameterListener("CDWET1", this);
    apvts.addParameterListener("CDGAIN1", this);

    // MS processor
    apvts.addParameterListener("MIDSGAIN", this);
    apvts.addParameterListener("SIDESGAIN", this);

}

BeastySynth1AudioProcessor::~BeastySynth1AudioProcessor()
{
    //OSC 1
    apvts.removeParameterListener("OSC1WAVETYPE", this);

    //OSC 2
    apvts.removeParameterListener("OSC2WAVETABLE", this);
    apvts.removeParameterListener("OSC2MORPH", this);
    apvts.removeParameterListener("OSC2TRANS", this);
    apvts.removeParameterListener("OSC2GAIN", this);
    apvts.removeParameterListener("OSC2PAN", this);
    apvts.removeParameterListener("OSC2UNI", this);
    apvts.removeParameterListener("OSC2WIDTH", this);

    // Conv Dist 1
    apvts.removeParameterListener("IRLOAD1", this);
    apvts.removeParameterListener("CDWET1", this);
    apvts.removeParameterListener("CDGAIN1", this);

    // MS Processing
    apvts.removeParameterListener("MIDSGAIN", this);
    apvts.removeParameterListener("SIDESGAIN", this);
}

//==============================================================================
const juce::String BeastySynth1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BeastySynth1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BeastySynth1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BeastySynth1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BeastySynth1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BeastySynth1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BeastySynth1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void BeastySynth1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BeastySynth1AudioProcessor::getProgramName (int index)
{
    return {};
}

void BeastySynth1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BeastySynth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    for (int v = 0; v < synth.getNumVoices(); v++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(v)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());

            auto& osc2 = voice->getOscillator2();
            for (int ch = 0; ch < getTotalNumOutputChannels(); ch++)
            {
                auto& osc2WaveChoice = *apvts.getRawParameterValue("OSC2WAVETABLE");
                osc2[ch].loadWaveTableFile(static_cast<int>(osc2WaveChoice), getWaveTableFiles());
            }
        }
    }        
    MSCompressor.prepareToPlay(spec, sampleRate, samplesPerBlock, getTotalNumInputChannels());
}

void BeastySynth1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BeastySynth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BeastySynth1AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    auto playHead = this->getPlayHead();


    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // OSC1
            auto& osc1 = voice->getOscillator1();

            auto& osc1WaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& osc1Macro = *apvts.getRawParameterValue("OSC1MACRO");
            auto& osc1Trans = *apvts.getRawParameterValue("OSC1TRANS");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc1Pan = *apvts.getRawParameterValue("OSC1PAN");
            auto& osc1UniVoices = *apvts.getRawParameterValue("OSC1UNI");
            auto& osc1UniWidth = *apvts.getRawParameterValue("OSC1WIDTH");
            auto& osc1UniSpread = *apvts.getRawParameterValue("OSC1SPREAD");

            for (int i = 0; i < getTotalNumOutputChannels(); i++)
            {
                osc1[i].updateOscParams(osc1WaveChoice, osc1Macro, osc1Trans, osc1Gain, osc1Pan, 
                    osc1UniVoices, osc1UniWidth, osc1UniSpread);
            }

            // OSC2
            auto& osc2 = voice->getOscillator2();

            auto& osc2Morph = *apvts.getRawParameterValue("OSC2MORPH");
            auto& osc2Trans = *apvts.getRawParameterValue("OSC2TRANS");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc2Pan = *apvts.getRawParameterValue("OSC2PAN");
            auto& osc2UniVoices = *apvts.getRawParameterValue("OSC2UNI");
            auto& osc2UniWidth = *apvts.getRawParameterValue("OSC2WIDTH");
            auto& osc2UniSpread = *apvts.getRawParameterValue("OSC2SPREAD");

            for (int i = 0; i < getTotalNumOutputChannels(); i++)
            {
                 osc2[i].updateOscParams(osc2Morph, osc2Trans, osc2Gain, osc2Pan,
                    osc2UniVoices, osc2UniWidth, osc2UniSpread);
            }

            // ADSR 1
            auto& ahdsr1 = voice->getAHDSR1();
            auto& attack1 = *apvts.getRawParameterValue("ATT1");
            auto& hold1 = *apvts.getRawParameterValue("HOLD1");
            auto& decay1 = *apvts.getRawParameterValue("DEC1");
            auto& sustain1 = *apvts.getRawParameterValue("SUS1");
            auto& release1 = *apvts.getRawParameterValue("REL1");
            ahdsr1.updateParams(attack1.load(), hold1.load(), decay1.load(), sustain1.load(), release1.load());

            // Filter1 Params
            auto& filterType1 = *apvts.getRawParameterValue("FILTERTYPE1");
            auto& DBOct1 = *apvts.getRawParameterValue("DBOCT1");
            auto& cuttoff1 = *apvts.getRawParameterValue("CUTOFF1");
            auto& res1 = *apvts.getRawParameterValue("RES1");
            auto& fDrive1 = *apvts.getRawParameterValue("FDRIVE1");
            auto& fEnv1 = *apvts.getRawParameterValue("FENV1");

            voice->updateFilter1(filterType1.load(), DBOct1.load(), cuttoff1.load(), res1.load(),
                fDrive1.load(), fEnv1.load());

            // Filter1 Params
            auto& filterType2 = *apvts.getRawParameterValue("FILTERTYPE2");
            auto& DBOct2 = *apvts.getRawParameterValue("DBOCT2");
            auto& cuttoff2 = *apvts.getRawParameterValue("CUTOFF2");
            auto& res2 = *apvts.getRawParameterValue("RES2");
            auto& fDrive2 = *apvts.getRawParameterValue("FDRIVE2");
            auto& fEnv2 = *apvts.getRawParameterValue("FENV2");

            voice->updateFilter2(filterType2.load(), DBOct2.load(), cuttoff2.load(), res2.load(),
                fDrive2.load(), fEnv2.load());

            // AHDSR 2
            auto& ahdsr2 = voice->getAHDSR2();
            auto& attack2 = *apvts.getRawParameterValue("ATT2");
            auto& hold2 = *apvts.getRawParameterValue("HOLD2");
            auto& decay2 = *apvts.getRawParameterValue("DEC2");
            auto& sustain2 = *apvts.getRawParameterValue("SUS2");
            auto& release2 = *apvts.getRawParameterValue("REL2");
            ahdsr2.updateParams(attack2.load(), hold2.load(), decay2.load(), sustain2.load(), release2.load());

            // Conv Distortion

            // Reverb 1
            auto& reverb1 = voice->getReverb1();
            auto& size1 = *apvts.getRawParameterValue("SIZE1");
            auto& damp1 = *apvts.getRawParameterValue("DAMP1");
            auto& width1 = *apvts.getRawParameterValue("WIDTH1");
            auto& wet1 = *apvts.getRawParameterValue("WET1");
            auto& dry1 = *apvts.getRawParameterValue("DRY1");
            reverb1.updateParams(size1, damp1, width1, wet1, dry1);

            // OSC Sub
            auto& oscSub = voice->getSubOscillator();
            auto& oscSubWaveChoice = *apvts.getRawParameterValue("OSCSUBWAVETYPE");
            auto& oscSubMacro = *apvts.getRawParameterValue("OSCSUBMACRO");
            auto& oscSubTrans = *apvts.getRawParameterValue("OSCSUBTRANS");
            auto& oscSubGain = *apvts.getRawParameterValue("OSCSUBGAIN");

            for (int i = 0; i < getTotalNumOutputChannels(); i++)
            {
                oscSub[i].updateOscParams(oscSubWaveChoice, oscSubMacro, oscSubTrans, oscSubGain);
            }

            // Wave Shapper 1
            auto& waveshaper1 = voice->getWaveshaper1();
            auto& type1 = *apvts.getRawParameterValue("WSTYPE1");
            auto& input1 = *apvts.getRawParameterValue("WSINPUT1");
            auto& output1 = *apvts.getRawParameterValue("WSOUTPUT1");
            waveshaper1.updateParams(input1, output1, type1);

            // MS processing
            auto& midsGain = *apvts.getRawParameterValue("MIDSGAIN");
            auto& sidesGain = *apvts.getRawParameterValue("SIDESGAIN");
            MSCompressor.updateMSCompParams(midsGain, sidesGain);
        }
    }    

    
    // Master Bus routing
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

void BeastySynth1AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // Osc 2
            if (parameterID == "OSC2WAVETABLE")
            {
                auto& osc2 = voice->getOscillator2();
                auto& osc2WaveChoice = *apvts.getRawParameterValue("OSC2WAVETABLE");
                for (int i = 0; i < getTotalNumOutputChannels(); i++)
                {
                    osc2[i].loadWaveTableFile(static_cast<int>(osc2WaveChoice), getWaveTableFiles());
                }
            }

            // Convolution Distortion
            if (parameterID == "IRLOAD1" || "CDWET1" || "CDGAIN1")
            {
                // Convolution Distortion
                auto& convDist1 = voice->getConvDist1();
                auto& cdIRType1 = *apvts.getRawParameterValue("IRLOAD1");
                auto& cdDryWet1 = *apvts.getRawParameterValue("CDWET1");
                auto& cdGain1 = *apvts.getRawParameterValue("CDGAIN1");
                convDist1.updateParams(static_cast<int>(cdIRType1), getIRDistFiles(), cdDryWet1, cdGain1);
            }

            // MS multiband Compressor
            if (parameterID == "MIDSGAIN" || "SIDESGAIN")
            {

            }
        }
    }
}

//==============================================================================
bool BeastySynth1AudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* BeastySynth1AudioProcessor::createEditor()
{
    return new BeastySynth1AudioProcessorEditor (*this);
}

//==============================================================================
void BeastySynth1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    const auto state = apvts.copyState();
    const auto xml = state.createXml();
    copyXmlToBinary(*xml, destData);
}

void BeastySynth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    const auto xmlState = getXmlFromBinary(data, sizeInBytes);
    if (xmlState == nullptr)
        return;
    const auto newTree = juce::ValueTree::fromXml(*xmlState);
    apvts.replaceState(newTree);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BeastySynth1AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout BeastySynth1AudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Osc 1 controlls Wavetype, trans, Gain
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sin", "Saw", "Squ" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1MACRO", "Osc 1 Macro", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1TRANS", "Osc 1 Transposition", -24, 24, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Osc 1 Gain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1PAN", "Osc 1 Pan", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1UNI", "Osc 1 Unison Voices", 0, 8, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1WIDTH", "Osc 1 Unison Width", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1SPREAD", "Osc 1 Unison Spread", juce::NormalisableRange<float> {-2.0f, 2.0f, 0.01f}, 0.0f));

    // Osc 2 Wavetable 
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2WAVETABLE", "Osc 2 Wave Table", getWaveTableFiles(), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2MORPH", "Osc 2 Macro", juce::NormalisableRange<float> {0.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2TRANS", "Osc 2 Transposition", -24, 24, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Osc 2 Gain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2PAN", "Osc 2 Pan", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2UNI", "Osc 2 Unison Voices", 0, 6, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2WIDTH", "Osc 2 Unison Width", juce::NormalisableRange<float> {-1.0f, 1.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2SPREAD", "Osc 2 Unison Spread", juce::NormalisableRange<float> {-2.0f, 2.0f, 0.01f}, 0.0f));

    // AHDSR 1
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATT1", "Attack1", juce::NormalisableRange<float> {0.0f, 5.0f, 0.01f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HOLD1", "Hold1", juce::NormalisableRange<float> {0.0f, 5.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEC1", "Decay1", juce::NormalisableRange<float> {0.01f, 5.0f, 0.01f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUS1", "Sustain1", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REL1", "Release1", juce::NormalisableRange<float> {0.01f, 5.0f, 0.01f}, 0.5f));

    // AHDSR 2
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATT2", "Attack1", juce::NormalisableRange<float> {0.0f, 5.0f, 0.01f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HOLD2", "Hold1", juce::NormalisableRange<float> {0.0f, 5.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEC2", "Decay1", juce::NormalisableRange<float> {0.01f, 5.0f, 0.01f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUS2", "Sustain1", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REL2", "Release1", juce::NormalisableRange<float> {0.01f, 5.0f, 0.01f}, 0.5f));

    // filter 1
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE1", "Filter 1 Type", juce::StringArray{ "Lpf", "Bpf", "Hpf" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("DBOCT1", "Filter 1 DB oct", juce::StringArray{"12db/oct", "24db/oct"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF1", "Filter 1 Cutoff Frequency", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.4f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RES1", "Filter 1 Resonance", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FDRIVE1", "Filter 1 Drive", juce::NormalisableRange<float> {1.0f, 10.0f, 0.01f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FENV1", "Filter 1 Envelope", juce::NormalisableRange<float> {-10000.0f, 10000.0f, 0.01f, 0.4f, true}, 0.0f));

    // filter 2
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE2", "Filter 2 Type", juce::StringArray{ "Lpf", "Bpf", "Hpf" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("DBOCT2", "Filter 2 DB oct", juce::StringArray{"12db/oct", "24db/oct"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF2", "Filter 2 Cutoff Frequency", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.4f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RES2", "Filter 2 Resonance", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FDRIVE2", "Filter 2 Drive", juce::NormalisableRange<float> {1.0f, 10.0f, 0.01f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FENV2", "Filter 2 Envelope", juce::NormalisableRange<float> {-10000.0f, 10000.0f, 0.01f, 0.4f, true}, 0.0f));

    // Convolution Distortion
    params.push_back(std::make_unique<juce::AudioParameterChoice>("IRLOAD1", "Conv Dist IR choice", getIRDistFiles(), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CDWET1", "Conv Dist dry wet", juce::NormalisableRange<float> {0.0f, 1.0f, 0.1f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CDGAIN1", "Conv Dist gain", juce::NormalisableRange<float> {-24.0f, 24.0f, 0.0f}, 0.0f));

    // Reverb 1
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SIZE1", "Reverb 1 Size", juce::NormalisableRange<float> {0.0f, 1.0f, 0.0f}, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DAMP1", "Reverb 1 Damping", juce::NormalisableRange<float> {0.0f, 1.0f, 0.0f}, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WIDTH1", "Reverb 1 Width", juce::NormalisableRange<float> {0.0f, 1.0f, 0.0f}, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WET1", "Reverb 1 Wet", juce::NormalisableRange<float> {0.0f, 1.0f, 0.0f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRY1", "Reverb 1 Dry", juce::NormalisableRange<float> {0.0f, 1.0f, 0.0f}, 1.0f));

    // Bottom row
    // Osc 2 controlls
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSCSUBWAVETYPE", "Osc Sub Wave Type", juce::StringArray{ "Sin", "Squ" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCSUBMACRO", "Osc Sub Macro", juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCSUBTRANS", "Osc Sub Transposition", juce::NormalisableRange<float> {-24.0f, 36.0f, 12.0f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCSUBGAIN", "Osc Sub Gain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f}, 0.8f));

    // WaveShaper Sub osc
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WSTYPE1", "WS Type 1", juce::StringArray{ "Tan", "Sin", "Cos" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WSINPUT1", "WS Input Gain 1", juce::NormalisableRange<float> {-24.0f, 24.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WSOUTPUT1", "WS Ouput Gain 1", juce::NormalisableRange<float> {-24.0f, 24.0f, 0.01f}, 0.0f));

    // MS multiband Compressor
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIDSGAIN", "Mids Gain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.1f}, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SIDESGAIN", "Sides Gain", juce::NormalisableRange<float> {0.0f, 1.0f, 0.1f}, 0.5f));

    return { params.begin(), params.end() };
}


juce::StringArray BeastySynth1AudioProcessor::getIRDistFiles()
{
    //juce::File projectDir = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory();
    //juce::File resourcesFolder = projectDir.getChildFile("Source").getChildFile("Resources").getChildFile("IRDistortion");

    juce::File resourcesFolder =  juce::File::getSpecialLocation(
                                     juce::File::SpecialLocationType::userDocumentsDirectory)
                                     .getChildFile(ProjectInfo::companyName)
                                     .getChildFile(ProjectInfo::projectName)
                                     .getChildFile("IR Distortion");  // PresetDirectory

    juce::StringArray irFiles;

    juce::Logger::writeToLog("Checking directory: " + resourcesFolder.getFullPathName());

    if (resourcesFolder.isDirectory())
    {
        juce::Array<juce::File> files;
        resourcesFolder.findChildFiles(files, juce::File::findFiles, false, "*.wav");

        for (const auto& file : files)
        {
            irFiles.add(file.getFullPathName());
        }
    }
    else
    {
        juce::Logger::writeToLog("IR Distortion folder not found.");
    }

    return irFiles;
}

juce::StringArray BeastySynth1AudioProcessor::getWaveTableFiles()
{
    //juce::File projectDir = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory();
    //juce::File resourcesFolder = projectDir.getChildFile("Source")
    //    .getChildFile("Resources").getChildFile("WaveTables");

    juce::File resourcesFolder = juce::File::getSpecialLocation(
        juce::File::SpecialLocationType::userDocumentsDirectory)
        .getChildFile(ProjectInfo::companyName)
        .getChildFile(ProjectInfo::projectName)
        .getChildFile("WaveTables");  // PresetDirectory

    juce::StringArray waveTableFiles;

    juce::Logger::writeToLog("Checking directory: " + resourcesFolder.getFullPathName());

    if (resourcesFolder.isDirectory())
    {
        juce::Array<juce::File> files;
        resourcesFolder.findChildFiles(files, juce::File::findFiles, false, "*.wav");

        for (const auto& file : files)
        {
            waveTableFiles.add(file.getFullPathName());
        }
    }
    else
    {
        juce::Logger::writeToLog("WaveTable folder not found.");
    }
    return waveTableFiles;
}