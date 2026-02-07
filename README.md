# 📚 Learning C: The K&R Path
> **"The only way to learn a new programming language is by writing programs in it."**

---

### **Overview**
This repository is a **deep-dive** into the foundational logic of the C programming language. I am manually implementing every exercise from the classic **Kernighan and Ritchie (K&R)** text to master the "source code" of computing. 

No IDEs. No shortcuts. Just **Vim**, **GCC**, and **Logic**.

---

### **The Technical Environment**
* **Operating System:** Fedora Linux 
* **Development Editor:** Vim (The power-user's choice)
* **Compiler Stack:** `gcc` with strict flags (`-Wall -Wextra`)
* **Commit Strategy:** Every file is **annotated** to explain memory behavior and pointer logic.

---

### **Core Focus Areas**
1. **Memory Architecture:** Investigating how different data types (char, int, long) occupy space on **64-bit systems**.
2. **String Mechanics:** Deep-diving into the **null-terminator (`\0`)** and manual traversal of memory blocks.
3. **Optimization:** Comparing standard library functions against **custom-built implementations** (like `my_strlen`).
4. **System Integrity:** Writing **defensive code** to prevent memory leaks and logical overflows.



---

### **How to Compile & Run**
To maintain **system integrity**, I compile manually through the terminal:

**1. Compile the Source:**
`gcc -o output filename.c`

**2. Execute the Binary:**
`./output`

---

### **The Philosophy**
**Efficiency** is everything. I treat my brain like a CPU—focusing only on **Localhost** (what I can control) and filtering out the **Noise** (what I cannot).
