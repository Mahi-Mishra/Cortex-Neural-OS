🧠 Cortex Neural OS (v8.0)

A modular, terminal-based AI Operating System built entirely from scratch in **C**. It features a custom neural network engine (`nn.c`) that powers a suite of real-world applications—from medical triage to cybersecurity—without relying on any external AI libraries like TensorFlow or PyTorch.

💡 About The Project

I've always been curious about how AI *actually* learns. We usually just import libraries and let them do the magic, but I wanted to build the "brain" myself.

**Cortex** is the result of that experiment. It's a simulation of an Operating System where I wrote the raw math for the Neural Network (Matrix Multiplication, Sigmoid Activation, and Backpropagation) using only standard C libraries.

It’s not just a blank console, though. I built a persistent system that "remembers" what it learns by saving weights to `.dat` files, and I wrapped it in a menu-driven interface with four fully functional apps to test the AI in different scenarios.


🚀 Key Features

🧠 The Core Engine

 **Zero Dependencies:** Everything runs on standard C logic (`math.h`, `stdlib.h`).
 **Persistent Memory:** The AI saves its training data (`brain_*.dat`) so it gets smarter every time you run it.
 **Crash-Proof:** Custom input handling ensures the program doesn't break if you type text into a number field.

📱 The App Suite

I built four distinct tools to test the neural net:

1. **🧮 Neuro-Calc:** A "Neural Adder" that learns math by seeing examples, rather than being programmed with rules. It proves the AI is learning logic (outputting `3.99` for `2+2`).
2. **🚑 Doc-AI (Medical):** An emergency triage bot. I added strict safety layers here—it detects "Impossible" inputs (like 0 BPM or boiling body temp) and flags Cardiac Arrest immediately.
3. **💪 Fit-Bot:** A metabolic analyzer. It calculates TDEE and gives a full health report card (BMI, Deficit/Surplus) instead of just a generic label.
4. **🛡️ Spam-Guard:** A context-aware security scanner. You can paste an entire email body, and it analyzes the combination of *Keywords + Links + Caps Lock* to catch scams that simple filters miss.

⚙️ How It Works

The project is split into three main layers:

1. **The Kernel (`nn.c`):** This is the brain. It defines the `NeuralNetwork` struct, manages memory, and handles the Forward/Backward propagation algorithms.
2. **The Interface (`main.c`):** This acts as the OS. It manages the user menu, screen clearing, and routes data between the user and the specific AI model.
3. **The Storage (`.dat` files):** Binary files where the AI stores its "knowledge" (weights and biases).


💻 Getting Started

You can run this on any machine with a C compiler (GCC).

Prerequisites

GCC (MinGW for Windows, or standard on Linux/Mac).

Installation & Run

1. **Clone the repo**
```sh
git clone https://github.com/Mahi-Mishra/Cortex-Neural-OS.git

```


2. **Compile**
```sh
gcc main.c nn.c -o cortex

```


3. **Run**
```sh
./cortex

```


*(Windows users can also just double-click the `build.bat` file included).*


🔮 Future Improvements

This project is stable, but I have a few ideas for v9.0:

 [ ] **GUI Port:** Move from the terminal to a visual window using Raylib to show the neurons firing in real-time.
 [ ] **Smarter NLP:** Upgrade Spam-Guard from simple keyword counting to a proper Bag-of-Words vectorizer.
 [ ] **Game Mode:** Train the AI to play Snake using Reinforcement Learning.


👤 Author

**Mahi Mishra**

 **GitHub:** [Mahi-Mishra](https://github.com/Mahi-Mishra)

If you find this code interesting or have ideas on how to optimize the backpropagation math, feel free to reach out or open a pull request!

*Built with C, Logic, and a lot of debugging.*

🤝 Acknowledgments & Methodology

This project was developed using an **AI-Assisted Engineering** workflow.

**Architecture & Logic:** Designed by **Mahi Mishra**. I defined the system requirements, the safety protocols (such as the Medical Triage logic), and the application structure.
**Implementation:** The core C syntax and mathematical algorithms were generated via **Google Gemini** based on my specific architectural prompts and logical constraints.
**Quality Assurance:** I performed the system testing, debugging, and bias correction (e.g., re-balancing the medical datasets) to ensure the code functions correctly and safely.

This project serves as a demonstration of utilizing LLMs as a pair-programmer to accelerate low-level systems development.