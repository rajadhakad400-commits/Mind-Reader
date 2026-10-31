# 🧠 Mind Reader – Number Prediction Using C++

A C++17-based number prediction game that identifies a user's secret number between **1 and 99** using nine Yes/No questions. The project demonstrates binary encoding, bitwise operations, ROM-based lookup, and Finite State Machine (FSM) design.

## 📌 Project Overview

Mind Reader is a logic-based number prediction system inspired by digital hardware architecture.

The program asks the user nine Yes/No questions. On each screen, it displays a specific set of numbers. Based on the user's answers, the program generates a unique 9-bit code and matches it against a predefined code table to predict the selected number.

The project models fundamental digital electronics concepts through a software implementation in C++.

## ✨ Features

- **Number Prediction:** Predicts any number from 1 to 99 using nine Yes/No questions.
- **Binary Encoding:** Uses unique 9-bit codes to represent all 99 numbers.
- **ROM-Based Lookup:** Stores predefined binary codes in a constant array.
- **Bitwise Operations:** Uses bit shifting and bitwise OR to construct the answer code.
- **Finite State Machine:** Implements three states: IDLE, ASK, and DONE.
- **Input Validation:** Accepts Yes/No responses and handles invalid inputs.
- **Error Detection:** Identifies answer combinations that do not match any stored number.
- **Automated Testing:** Tests all 99 possible numbers automatically.
- **Replay Option:** Allows users to play multiple rounds.

## 🛠️ Technologies & Concepts Used

- **Programming Language:** C++17
- **Compiler:** GCC / G++
- **Standard Libraries:** `<array>`, `<bitset>`, `<cstdint>`, `<iostream>`, `<string>`
- **Core Concepts:** Binary Encoding, Bitwise Operations, ROM-Based Lookup, Finite State Machine (FSM)
- **Testing:** Automated Self-Testing and Input Validation
- **Build:** G++ Compiler

## ⚙️ Working Principle

1. **Initialization:** The game initializes the accumulator, screen counter, and FSM state.
2. **Display Numbers:** The program displays numbers whose corresponding bit is set in the current screen.
3. **Collect Answers:** The user responds with Yes or No for each of the nine screens.
4. **Generate Binary Code:** Each Yes response sets the corresponding bit in a 9-bit accumulator using bitwise OR and left-shift operations.
5. **Predict Number:** The accumulated code is compared against the predefined ROM table to identify the selected number.

## 🧩 Core Concepts Implemented

### 1. Binary Encoding
Each number from 1 to 99 is assigned a unique 9-bit code. Each bit represents whether the number appears on a particular screen.

### 2. ROM (Read-Only Memory)
A predefined constant array named `CODE_ROM` stores the 9-bit codes corresponding to all 99 numbers.

### 3. Finite State Machine (FSM)
The game uses three states to manage execution:

| State | Description |
|---|---|
| IDLE | Initial state before starting the game |
| ASK | Displays screens and collects answers |
| DONE | Completes the prediction process |

### 4. Bitwise Operations
The following expression updates the accumulator:

```cpp
acc_ |= static_cast<uint16_t>(1u << screen_);
```

- `1u << screen_` shifts a bit to the current screen position.
- `|=` sets the corresponding bit in the accumulator.
- A Yes answer sets the bit to 1, while a No answer leaves it at 0.

### 5. ROM Lookup
After collecting all nine answers, the `found()` function searches the ROM table for a matching code and returns the corresponding number.

## 📂 Project Structure

```text
Mind-Reader/
├── mind_reader.cpp
└── README.md
```

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting C++17
- GCC / G++
- VS Code or any C++ IDE

### 1. Clone the Repository

Replace `your-username` with your GitHub username:

```bash
git clone https://github.com/your-username/mind-reader.git
```

### 2. Navigate to the Project Directory

```bash
cd mind-reader
```

### 3. Compile the Program

```bash
g++ -std=c++17 -O2 -o mind_reader mind_reader.cpp
```

### 4. Run the Game

**Linux / macOS:**

```bash
./mind_reader
```

**Windows (Command Prompt):**

```bash
mind_reader.exe
```

## 🧪 Automated Testing

The project includes a self-testing mode that automatically verifies the prediction mechanism for all 99 possible numbers.

Run:

```bash
./mind_reader --test
```

On Windows:

```bash
mind_reader.exe --test
```

Expected successful output:

```text
ALL 99 NUMBERS PREDICTED CORRECTLY
```

The test checks that every secret number is correctly predicted when the answers are consistent with the displayed screens.

## 📊 Complexity Analysis

Let N represent the number of possible numbers (99).

| Operation | Time Complexity |
|---|---|
| Initialize game | O(1) |
| Check whether a number appears on a screen | O(1) |
| Update accumulator | O(1) |
| Search ROM for matching code | O(N) |
| Display one screen | O(N) |
| Test all 99 numbers | O(9 × N²) |

**Space Complexity:** O(N) for the predefined code table, with O(1) additional working space during an individual game.

## 🎯 Learning Outcomes

- Implementing binary encoding and bitwise operations in C++.
- Understanding Finite State Machine design.
- Working with ROM-like lookup structures.
- Managing program states and validating user input.
- Writing automated tests for all possible valid inputs.
- Connecting software programming concepts with digital electronics.

## 🔮 Future Improvements

- Develop a graphical user interface (GUI).
- Implement the same design using Verilog HDL.
- Extend the number prediction range.
- Optimize the number lookup mechanism.
- Explore an FPGA hardware implementation.

## 👨‍💻 Author

**Raja Dhakad**  
B.Tech – Electrical and Computer Engineering  
Manipal University Jaipur


