#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class JUCEVSTTemplateAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JUCEVSTTemplateAudioProcessorEditor (JUCEVSTTemplateAudioProcessor&);
    ~JUCEVSTTemplateAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCEVSTTemplateAudioProcessor& proc;
    juce::Slider oscMixSlider, filterCutoffSlider;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> attachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCEVSTTemplateAudioProcessorEditor)
};