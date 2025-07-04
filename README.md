# 🧩 Rubik's Cube Solver

This project implements a solver for the 3×3 Rubik's Cube using clean **object-oriented design** and advanced **graph search algorithms**, including:

- 🔍 **Breadth-First Search (BFS)**
- 🧠 **Depth-First Search (DFS)**
- ⏱️ **Iterative Deepening DFS (IDDFS)**
- 🎯 **IDA\*** (Iterative Deepening A*) — *Korf's Algorithm*

---

## 🧱 Cube State Representations

The cube is represented in three different formats for benchmarking memory and performance tradeoffs:

- 🧊 **3D Array**
- 📦 **1D Array**
- 💡 **Bitboard** (bitwise representation for efficiency)

---

## 🔧 Features

- ✅ Clean **OOP-based architecture**
- 🔁 Multiple cube state representations
- 🔬 Solver comparison across different algorithms
- ⭐ Advanced **IDA\*** implementation with **pattern database heuristics**
- 📂 Corner pattern database for efficient solving
- 🖥️ Terminal-based interactive interface

---

## 🎯 IDA\* (Korf's Algorithm) — Optimal Solver

This project includes a sophisticated implementation of the IDA\* algorithm based on Richard Korf's seminal 1997 paper:

> **"Finding Optimal Solutions to Rubik's Cube Using Pattern Databases"**  
> 📖 [Read paper](https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf)

### 🧠 Key Features of IDA\*:

- **Iterative Deepening A\***: Combines memory efficiency of DFS with optimality of A*
- **Corner Pattern Database**: Provides admissible heuristics using precomputed data
- **Memory Efficient**: O(d) space complexity (where d = solution depth)
- **Guaranteed Optimality**: Always finds the shortest possible solution

---

## 🗂️ Pattern Database Heuristic

The **corner pattern database** stores the minimum moves to solve corners from any configuration.

- 🔢 **88,179,840** total corner configurations
- 📦 Stored using compact `NibbleArray` (4-bit storage)
- ⚡ Provides **admissible**, fast heuristics
- 💾 Saved to disk for persistent use

---


