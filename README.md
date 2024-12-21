# Advanced Calculator in C

## Description

This project is an **Advanced Calculator** built using C with a graphical interface based on the Windows API. The original calculator design was taken as a base, and I have added several new features and functionalities to enhance its usability and versatility.

## Features

### Original Features:
- **Basic arithmetic operations**:
  - Addition (+)
  - Subtraction (-)
  - Multiplication (*)
  - Division (/)

### New Features Added:
1. **Mathematical Constants**:
   - π (Pi): Displays the value of Pi (\(3.14159...\)).
   - φ (Golden Ratio): Displays the value of the Golden Ratio (\(1.618...\)).

2. **Advanced Operations**:
   - \(x^2\): Computes the square of the input.
   - \(x^3\): Computes the cube of the input.
   - Trigonometric functions:
     - Sine (\(\sin\))
     - Cosine (\(\cos\))
     - Tangent (\(\tan\))
   - Inverse trigonometric functions:
     - Arc-sine (\(\arcsin\))
     - Arc-cosine (\(\arccos\))
     - Arc-tangent (\(\arctan\))

3. **Improved Interface**:
   - Buttons are neatly arranged in an ergonomic layout.
   - The display is updated dynamically to reflect input and results.

## How to Run

### Prerequisites
- A C compiler, such as `gcc` (MinGW recommended for Windows).
- Basic understanding of running and compiling C programs.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/advanced-calculator.git
   cd src
   gcc main.c -o calculator -lgdi32 -lm
   ./calculator

![image](https://github.com/user-attachments/assets/fb04170c-4831-4483-9165-829038cd1f2d)


