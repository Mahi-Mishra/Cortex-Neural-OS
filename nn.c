#include "nn.h"

// --- Activation Functions ---

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// --- Lifecycle Management ---

NeuralNetwork* create_network(int input, int hidden, int output) {
    NeuralNetwork* nn = malloc(sizeof(NeuralNetwork));
    nn->input_nodes = input;
    nn->hidden_nodes = hidden;
    nn->output_nodes = output;

    // Allocate Weight Matrices (Input -> Hidden)
    nn->hidden_weights = malloc(input * sizeof(double*));
    for(int i = 0; i < input; i++) {
        nn->hidden_weights[i] = malloc(hidden * sizeof(double));
    }

    // Allocate Weight Matrices (Hidden -> Output)
    nn->output_weights = malloc(hidden * sizeof(double*));
    for(int i = 0; i < hidden; i++) {
        nn->output_weights[i] = malloc(output * sizeof(double));
    }

    // Allocate Biases
    nn->hidden_biases = malloc(hidden * sizeof(double));
    nn->output_biases = malloc(output * sizeof(double));

    return nn;
}

void init_network(NeuralNetwork* nn) {
    // Randomize Hidden Weights (-1.0 to 1.0)
    for(int i = 0; i < nn->input_nodes; i++) {
        for(int j = 0; j < nn->hidden_nodes; j++) {
            nn->hidden_weights[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
    // Randomize Output Weights (-1.0 to 1.0)
    for(int i = 0; i < nn->hidden_nodes; i++) {
        for(int j = 0; j < nn->output_nodes; j++) {
            nn->output_weights[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
    // Initialize Biases to 0
    for(int i = 0; i < nn->hidden_nodes; i++) nn->hidden_biases[i] = 0.0;
    for(int i = 0; i < nn->output_nodes; i++) nn->output_biases[i] = 0.0;
}

// --- Neural Network Operations ---

double* predict(NeuralNetwork* nn, double* inputs) {
    // 1. Hidden Layer Activation
    double* hidden_layer = malloc(nn->hidden_nodes * sizeof(double));
    for(int i = 0; i < nn->hidden_nodes; i++) {
        double sum = 0.0;
        for(int j = 0; j < nn->input_nodes; j++) {
            sum += inputs[j] * nn->hidden_weights[j][i];
        }
        sum += nn->hidden_biases[i];
        hidden_layer[i] = sigmoid(sum);
    }

    // 2. Output Layer Activation
    double* outputs = malloc(nn->output_nodes * sizeof(double));
    for(int i = 0; i < nn->output_nodes; i++) {
        double sum = 0.0;
        for(int j = 0; j < nn->hidden_nodes; j++) {
            sum += hidden_layer[j] * nn->output_weights[j][i];
        }
        sum += nn->output_biases[i];
        outputs[i] = sigmoid(sum);
    }
    
    free(hidden_layer);
    return outputs;
}

void train(NeuralNetwork* nn, double* inputs, double* targets, double learning_rate) {
    /* --- Forward Pass --- */
    
    // Compute Hidden Layer
    double* hidden_layer = malloc(nn->hidden_nodes * sizeof(double));
    for(int i = 0; i < nn->hidden_nodes; i++) {
        double sum = 0.0;
        for(int j = 0; j < nn->input_nodes; j++) {
            sum += inputs[j] * nn->hidden_weights[j][i];
        }
        sum += nn->hidden_biases[i];
        hidden_layer[i] = sigmoid(sum);
    }

    // Compute Output Layer
    double* outputs = malloc(nn->output_nodes * sizeof(double));
    for(int i = 0; i < nn->output_nodes; i++) {
        double sum = 0.0;
        for(int j = 0; j < nn->hidden_nodes; j++) {
            sum += hidden_layer[j] * nn->output_weights[j][i];
        }
        sum += nn->output_biases[i];
        outputs[i] = sigmoid(sum);
    }

    /* --- Backpropagation --- */
    
    // 1. Calculate Output Gradients (Error * Derivative)
    double* output_deltas = malloc(nn->output_nodes * sizeof(double));
    for(int i = 0; i < nn->output_nodes; i++) {
        double error = targets[i] - outputs[i];
        output_deltas[i] = error * sigmoid_derivative(outputs[i]);
    }

    // 2. Calculate Hidden Gradients
    double* hidden_deltas = malloc(nn->hidden_nodes * sizeof(double));
    for(int i = 0; i < nn->hidden_nodes; i++) {
        double error = 0.0;
        for(int j = 0; j < nn->output_nodes; j++) {
            error += output_deltas[j] * nn->output_weights[i][j];
        }
        hidden_deltas[i] = error * sigmoid_derivative(hidden_layer[i]);
    }

    // 3. Update Output Weights & Biases
    for(int i = 0; i < nn->output_nodes; i++) {
        for(int j = 0; j < nn->hidden_nodes; j++) {
            nn->output_weights[j][i] += learning_rate * output_deltas[i] * hidden_layer[j];
        }
        nn->output_biases[i] += learning_rate * output_deltas[i];
    }

    // 4. Update Hidden Weights & Biases
    for(int i = 0; i < nn->hidden_nodes; i++) {
        for(int j = 0; j < nn->input_nodes; j++) {
            nn->hidden_weights[j][i] += learning_rate * hidden_deltas[i] * inputs[j];
        }
        nn->hidden_biases[i] += learning_rate * hidden_deltas[i];
    }

    // Cleanup
    free(hidden_layer);
    free(outputs);
    free(output_deltas);
    free(hidden_deltas);
}

// --- Persistence (I/O) ---

void save_network(NeuralNetwork* nn, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    // Header: Topology
    fwrite(&nn->input_nodes, sizeof(int), 1, file);
    fwrite(&nn->hidden_nodes, sizeof(int), 1, file);
    fwrite(&nn->output_nodes, sizeof(int), 1, file);

    // Body: Weights
    for(int i = 0; i < nn->input_nodes; i++) {
        fwrite(nn->hidden_weights[i], sizeof(double), nn->hidden_nodes, file);
    }
    for(int i = 0; i < nn->hidden_nodes; i++) {
        fwrite(nn->output_weights[i], sizeof(double), nn->output_nodes, file);
    }
        
    // Body: Biases
    fwrite(nn->hidden_biases, sizeof(double), nn->hidden_nodes, file);
    fwrite(nn->output_biases, sizeof(double), nn->output_nodes, file);

    fclose(file);
    printf("Model successfully saved to '%s'\n", filename);
}

NeuralNetwork* load_network(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: File '%s' not found.\n", filename);
        return NULL;
    }

    int input, hidden, output;
    fread(&input, sizeof(int), 1, file);
    fread(&hidden, sizeof(int), 1, file);
    fread(&output, sizeof(int), 1, file);

    NeuralNetwork* nn = create_network(input, hidden, output);

    for(int i = 0; i < nn->input_nodes; i++) {
        fread(nn->hidden_weights[i], sizeof(double), nn->hidden_nodes, file);
    }
    for(int i = 0; i < nn->hidden_nodes; i++) {
        fread(nn->output_weights[i], sizeof(double), nn->output_nodes, file);
    }
        
    fread(nn->hidden_biases, sizeof(double), nn->hidden_nodes, file);
    fread(nn->output_biases, sizeof(double), nn->output_nodes, file);

    fclose(file);
    printf("Model successfully loaded from '%s'\n", filename);
    return nn;
}