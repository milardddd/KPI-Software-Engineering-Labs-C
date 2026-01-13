# Programming Fundamentals | Part 1: Core C Constructs

This module contains laboratory works focused on mastering the foundational elements of the C programming language. Each project is organized into its own directory containing the source code and related assets.

## 📑 Laboratory Works Overview

| # | Topic & Directory | Key Features |
|:---:|:---|:---|
| **1** | [roman_converter](./roman_converter) | Roman numeral converter (Cross-platform implementation) |
| **2** | [triangle_calculator](./triangle_calculator) | Geometric formulas and robust input validation |
| **3** | [day_of_week_finder](./day_of_week_finder) | Gregorian Day-of-Week finder using branching logic |
| **4** | [bubble_sort_tool](./bubble_sort_tool) | Optimized sorting with EPSILON-based comparison |
| **5** | [string_pointer_sorter](./string_pointer_sorter) | Case-insensitive sorter using pointers-to-pointers |
| **6** | [slae_iteration_solver](./slae_iteration_solver) | System of Linear Equations solver (Simple Iteration Method) |
| **7** | [nonlinear_equation_solver](./nonlinear_equation_solver) | Root-finding using Bisection and Newton's methods |
| **8** | [complex_impedance_calc](./complex_impedance_calc) | Circuit impedance modeling using complex number structures |
| **9** | [binary_record_manager](./binary_record_manager) | CRUD system for binary files with signature verification |


## 🛠 Technical Implementation Details

* **Memory Management**: Extensive use of dynamic allocation (`malloc`/`free`) and pointer arithmetic for flexible data handling.
* **Numerical Precision**: Implementation of `EPSILON`-based logic for accurate floating-point comparisons in sorting and mathematical solvers.
* **System Integration**: Use of `termios.h` for advanced Unix terminal control and single-character input handling.
* **Code Quality**: All solutions comply with the **C11 standard** and follow the **Coding Style: Adheres to Google's C programming conventions using Clang-Format.**.

## ⚙️ How to Run

Navigate to any laboratory folder and compile the source file using `gcc`:

```bash
cd folder_name
gcc main_file.c -o program -lm
./program