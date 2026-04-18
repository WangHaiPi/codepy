# codepy
[![vcpkg](https://img.shields.io/badge/vcpkg-1.1.0-blue)](https://github.com/microsoft/vcpkg/tree/master/ports/codepy)
[![GitHub stars](https://img.shields.io/github/stars/WangHaiPi/codepy?style=social)](https://github.com/WangHaiPi/codepy)
[![License](https://img.shields.io/badge/license-MIT-green)](https://github.com/WangHaiPi/codepy/blob/main/LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)
[![release](https://img.shields.io/github/v/release/WangHaiPi/codepy)](https://github.com/WangHaiPi/codepy/releases/tag/v1.1.0)
**A header-only C++ library that embeds Python execution.**

---

## 📌 Overview

`codepy` allows you to write and run Python code directly inside C++ using a simple stream-like interface.  
It is designed for **rapid prototyping, scripting integration, and mixed-language workflows** — without leaving your C++ environment.

```cpp
py << "print('Hello from Python')";
py.run();
'''
## ⚙️ Core Features
Feature	Description
Stream-based Python execution	Write Python code using << operator
Single-line execution	py.exec("...") for quick scripts
Multi-line support	Preserves indentation, loops, functions
Python package management	py.pip(), py.pipun(), py.piplist()
Environment detection	has_python(), has_package()
Cross-platform	Windows (MSVC/MinGW), Linux, macOS
Automatic encoding conversion	GBK ↔ UTF-8 (no mojibake)
PyPI mirrors (CN-friendly)	10 built-in mirrors for fast access

## 📦 Installation
Option 1: From GitHub (immediate)
```bash
vcpkg install https://github.com/WangHaiPi/codepy
'''
Option 2: Official vcpkg (after PR merge)
```bash
vcpkg install codepy
'''
Option 3: Manual
```bash
git clone https://github.com/WangHaiPi/codepy.git
# Copy `codepy.h` to your project
'''

## 🧪 Example
```cpp
#include "codepy.h"

int main() {
    // Multi-line Python script
    py << "for i in range(3):";
    py << "    print(f'Value: {i}')";
    py.run();

    // Inline execution
    py.exec("print('Inline execution')");

    // Environment check
    if (py.has_python()) {
        py.exec("print('Python ready')");
    }

    return 0;
}
'''
Output:

```text
Value: 0
Value: 1
Value: 2
Inline execution
Python ready
'''

## 🧠 Design Goals
Header-only – single #include, no build steps

Zero external dependencies – only requires a Python runtime in PATH

Intuitive API – mimics Python's REPL style

Safe by default – uses temporary files, no direct shell injection

## Author
**WangHaiPi** – a 5th-grade student who learns C++ and Python.
- GitHub: [@WangHaiPi](https://github.com/WangHaiPi)
- Project: [codepy](https://github.com/WangHaiPi/codepy)
- First-time contributor to vcpkg
