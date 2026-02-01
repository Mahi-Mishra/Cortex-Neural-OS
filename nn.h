#ifndef NN_H
#define NN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Feedforward Neural Network (Input -> Hidden -> Output)
typedef struct {
    int input_nodes;
    int hidden_nodes;
    int output_nodes;

    // Weights
    double** hidden_weights;
    double** output_weights;

    // Biases
    double* hidden_biases;
    double* output_biases;
} NeuralNetwork;

// --- Lifecycle ---
NeuralNetwork* create_network(int input, int hidden, int output);
void init_network(NeuralNetwork* nn);
void free_network(NeuralNetwork* nn);

// --- Operations ---
double* predict(NeuralNetwork* nn, double* inputs);
void train(NeuralNetwork* nn, double* inputs, double* targets, double learning_rate);

// --- Persistence ---
void save_network(NeuralNetwork* nn, const char* filename);
NeuralNetwork* load_network(const char* filename);

#endif