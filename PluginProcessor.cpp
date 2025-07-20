#include "PluginProcessor.h"
#include "PluginEditor.h"

JUCEVSTTemplateAudioProcessor::JUCEVSTTemplateAudioProcessor()
    : parameters(*this, nullptr, juce::Identifier("Params"), {
        std::make_unique<juce::AudioParameterFloat>("oscMix", "Oscillator Mix", 0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("filterCutoff", "Filter Cutoff", 20.0f, 20000.0f, 1000.0f),
        std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.01f, 5.0f, 0.1f),
        std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.01f, 5.0f, 0.5f)
    })
{}

void JUCEVSTTemplateAudioProcessor::prepareToPlay(double sr, int) {
    sampleRate = sr;
    filter.reset();
    filter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sr, *parameters.getRawParameterValue("filterCutoff"));
}

void JUCEVSTTemplateAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] *= 0.5f; // simple gain for test
        }
    }
}

void JUCEVSTTemplateAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    juce::MemoryOutputStream stream(destData, true);
    parameters.state.writeToStream(stream);
}

void JUCEVSTTemplateAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        parameters.replaceState(tree);
    }
}