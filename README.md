# 🌟 BigInt Library

🚀 **A fast and powerful compile-time arbitrary-precision integer library for C++.**

![Stars](https://img.shields.io/github/stars/TigranYavroyan/BigInt?style=social)  
![Last Commit](https://img.shields.io/github/last-commit/TigranYavroyan/BigInt?color=green) 

---

## 🔧 Features

- 📏 **Arbitrary-Precision Arithmetic**: Perform calculations with integers of any size.
- ⚡ **Compile-Time Computation**: Optimized for performance with modern C++ features.
- 💡 **Easy-to-Use API**: Seamless integration with operators like `+`, `-`, `*`, `/`.
- 📄 **Header-Only Library**: Just include the file, no additional dependencies.

---

## 📚 Getting Started

### Prerequisites
- A **C++17 or later** compatible compiler. If you want to fully use the metaprogramming power , use C++20 for compile time string literals.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/TigranYavroyan/BigInt.git
   cd BigInt
   ```

2. Include the header file in your project:
   ```cpp
   #include "BigInt.hpp"
   ```

---

## ⚙️ Usage Example

```cpp
#include <iostream>
#include "BigInt.hpp"

int main() {
    BigInt a = "123456789012345678901234567890";
    BigInt b = "987654321098765432109876543210";

    BigInt sum = a + b;
    BigInt product = a * b;

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}
```

### 🔨 Compile
```bash
g++ -std=c++2a -o bigint_example test.cpp
./bigint_example
```

---

## 📂 Folder Structure

---

## 🤝 Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch for your feature: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m 'Add a feature'`.
4. Push to your branch: `git push origin feature-name`.
5. Submit a pull request. 🎉

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

---

## ⭐ Acknowledgements

Special thanks to the C++ community for inspiring modern template-based programming.

---
