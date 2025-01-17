/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <nlohmann/json.hpp>
#include "NumCpp.hpp"
#include "include/lstm.h"

#define DEFAULT_GAIN 1.f
#define DEFAULT_VOLUME 6.f

//==============================================================================
/**
*/
class NocturneDSPAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    NocturneDSPAudioProcessor();
    ~NocturneDSPAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState state;

    void loadCab(const char *impulse, const int size);
    void loadProfile(const char *jsonFile);
    
    ModelLoader loader;
    lstm LSTM;
    
//    bool boostEnabled;
private:
    juce::dsp::Convolution cab;
    juce::dsp::Gain<float> gain, volume;
    
    bool cabEnabled;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    void updateParams();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NocturneDSPAudioProcessor)
};
