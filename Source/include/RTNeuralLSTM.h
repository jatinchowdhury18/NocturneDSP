/*
  ==============================================================================

    RTNeuralLSTM.h
    Created: 19 Sep 2021 6:32:16pm
    Author:  Stephane P. Pericat

  ==============================================================================
*/

#pragma once
#include <RTNeural/RTNeural.h>
//#include <RTNeural.h>

class RT_LSTM
{
public:
    RT_LSTM() = default;

    void reset();
    void load_json(const char* filename);

    void process(const float* inData, float* outData, int numSamples);

private:
    RTNeural::ModelT<float, 1, 1, RTNeural::LSTMLayerT<float, 1, 32>, RTNeural::DenseT<float, 32, 1>> model;
};