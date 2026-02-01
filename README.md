  <div align="center">

  <h1>🧠 Cortex Neural OS</h1>
  
  <p>
    <b>A Modular, Terminal-Based AI Operating System written in Pure C</b>
  </p>

<p>
  <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/Mahi-Mishra/Cortex-Neural-OS?style=for-the-badge&color=blue" alt="Contributors" />
  </a>
  <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/network/members">
    <img src="https://img.shields.io/github/forks/Mahi-Mishra/Cortex-Neural-OS?style=for-the-badge&color=orange" alt="Forks" />
  </a>
  <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/stargazers">
    <img src="https://img.shields.io/github/stars/Mahi-Mishra/Cortex-Neural-OS?style=for-the-badge&color=yellow" alt="Stars" />
  </a>
  <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/issues">
    <img src="https://img.shields.io/github/issues/Mahi-Mishra/Cortex-Neural-OS?style=for-the-badge&color=red" alt="Issues" />
  </a>
  <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/Mahi-Mishra/Cortex-Neural-OS?style=for-the-badge&color=green" alt="License" />
  </a>
</p>

<h4>
    <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/issues">Report Bug</a>
  <span> · </span>
    <a href="https://github.com/Mahi-Mishra/Cortex-Neural-OS/issues">Request Feature</a>
  </h4>
</div>

<br />

<details>
  <summary><b>Table of Contents</b></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#methodology">Methodology & AI Transparency</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

---

## 💡 About The Project

I've always been curious about how AI *actually* learns. We usually just import libraries and let them do the magic, but I wanted to build the "brain" myself.

**Cortex** is the result of that experiment. It's a simulation of an Operating System where I wrote the raw math for the Neural Network (Matrix Multiplication, Sigmoid Activation, and Backpropagation) using only standard C libraries.

It’s not just a blank console, though. I built a persistent system that "remembers" what it learns by saving weights to `.dat` files, and I wrapped it in a menu-driven interface with four fully functional apps to test the AI in different scenarios.

### 🛠️ Built With

* ![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
* ![GCC](https://img.shields.io/badge/GCC-000000?style=for-the-badge&logo=gnu&logoColor=white)
* ![Shell](https://img.shields.io/badge/Shell_Script-121011?style=for-the-badge&logo=gnu-bash&logoColor=white)

---


🚀 Getting Started

Prerequisites

* GCC Compiler (MinGW for Windows, or standard on Linux/Mac).

Installation & Run

*Option 1: Windows (Easy Mode)*
I have included a script that compiles and runs the code automatically.
1. Open your terminal in the project folder.
2. Type:
   ```sh
   ./run

(Or just double-click `run.bat`)*

<br />

**Option 2: Linux / Mac / Manual**
If you prefer doing it manually:

1. **Clone the repo**
```sh
git clone [https://github.com/Mahi-Mishra/Cortex-Neural-OS.git](https://github.com/Mahi-Mishra/Cortex-Neural-OS.git)

```


2. **Compile**
```sh
gcc main.c nn.c -o cortex

```


3. **Run**
```sh
./cortex

```



```

```


*(Windows users can also just double-click the `build.bat` file included).*

---

## 📱 Usage & Apps

The OS includes 4 distinct AI applications:

### 1. 🧮 Neuro-Calc

A "Neural Adder" that learns math by seeing examples, rather than being programmed with rules. It proves the AI is learning logic (outputting `3.99` for `2+2`).

### 2. 🚑 Doc-AI (Medical)

An emergency triage bot. I added strict safety layers here—it detects "Impossible" inputs (like 0 BPM or boiling body temp) and flags Cardiac Arrest immediately.

### 3. 💪 Fit-Bot

A metabolic analyzer. It calculates TDEE and gives a full health report card (BMI, Deficit/Surplus) instead of just a generic label.

### 4. 🛡️ Spam-Guard

A context-aware security scanner. You can paste an entire email body, and it analyzes the combination of *Keywords + Links + Caps Lock* to catch scams that simple filters miss.

---

## 🔮 Roadmap

* [x] Core Neural Engine (`nn.c`)
* [x] Persistent Memory System (`.dat` saves)
* [x] Context-Aware Spam Filter
* [ ] **GUI Port:** Move from terminal to a visual window using Raylib.
* [ ] **Smarter NLP:** Upgrade Spam-Guard to use Bag-of-Words vectorizer.
* [ ] **Game Mode:** Train the AI to play Snake using Reinforcement Learning.

---

## 🤝 Methodology

**"How did a First-Year Student build this?"**

This project was developed using an **AI-Assisted Engineering** workflow.

* **Architecture & Logic:** Designed by **Mahi Mishra**. I defined the system requirements, the safety protocols (such as the Medical Triage logic), and the application structure.
* **Implementation:** The core C syntax and mathematical algorithms were generated via **Google Gemini** based on my specific architectural prompts and logical constraints.
* **Quality Assurance:** I performed the system testing, debugging, and bias correction (e.g., re-balancing the medical datasets) to ensure the code functions correctly and safely.

This project serves as a demonstration of utilizing LLMs as a pair-programmer to accelerate low-level systems development.

---

## 👤 Contact

**Mahi Mishra** GitHub: [@Mahi-Mishra](https://github.com/Mahi-Mishra)

---

## 📝 License

Distributed under the MIT License. See `LICENSE` for more information.

```



