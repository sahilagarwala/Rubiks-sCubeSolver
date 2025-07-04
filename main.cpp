
#include "BFSSolver.h"
#include "DFSSolver.h"
#include "IDDFSSolver.h"
#include "IdastarSolver.cpp"
#include "CornerDBMaker.h"
#include "RubiksCube1dArray.cpp"
#include "RubiksCube3dArray.cpp"
#include "RubiksCubeBitboard.cpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printMoves(const vector<RubiksCube::MOVE> &moves, T &cube) {
  for (auto move : moves) {
    cout << RubiksCube::getMove(move) << " ";
    cube.move(move);
  }
  cout << endl;
  assert(cube.isSolved());
}

int main() {
  srand(time(NULL));
  int shuffleCount = 7; // Increased for proper shuffling
  int choice;

  cout << "Choose a representation and solver:\n";
  cout << "1. 1D + BFS\n";
  cout << "2. 1D + DFS\n";
  cout << "3. 1D + IDDFS\n";
  cout << "4. 3D + BFS\n";
  cout << "5. 3D + DFS\n";
  cout << "6. 3D + IDDFS\n";
  cout << "7. Bitboard + BFS\n";
  cout << "8. Bitboard + DFS\n";
  cout << "9. Bitboard + IDDFS\n";
  cout << "10. 1D + IDA* (Korf Algorithm)\n";
  cout << "11. 3D + IDA* (Korf Algorithm)\n";
  cout << "12. Bitboard + IDA* (Korf Algorithm)\n";
  cout << "13. Generate Corner Pattern Database\n";
  cout << "Enter your choice (1-13): ";
  cin >> choice;

  cout << "==============================\n";

  switch (choice) {
  case 1: {
    cout << "1D + BFS\n";
    RubiksCube1dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting BFS solve...\n";
    BFSSolver<RubiksCube1dArray, Hash1d> solver(cube);
    auto moves = solver.solve();
    cout << "Solution found with " << moves.size() << " moves: ";
    printMoves(moves, cube);
    break;
  }
  case 2: {
    cout << "1D + DFS\n";
    RubiksCube1dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting DFS solve (max depth 7)...\n";
    DFSSolver<RubiksCube1dArray, Hash1d> solver(cube, 7);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 3: {
    cout << "1D + IDDFS\n";
    RubiksCube1dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting IDDFS solve (max depth 7)...\n";
    IDDFSSolver<RubiksCube1dArray, Hash1d> solver(cube, 7);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 4: {
    cout << "3D + BFS\n";
    RubiksCube3dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting BFS solve...\n";
    BFSSolver<RubiksCube3dArray, Hash3d> solver(cube);
    auto moves = solver.solve();
    cout << "Solution found with " << moves.size() << " moves: ";
    printMoves(moves, cube);
    break;
  }
  case 5: {
    cout << "3D + DFS\n";
    RubiksCube3dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting DFS solve (max depth 7)...\n";
    DFSSolver<RubiksCube3dArray, Hash3d> solver(cube, 7);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 6: {
    cout << "3D + IDDFS\n";
    RubiksCube3dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    for (int i = 0; i < shuffleCount; i++)
      cube.move(RubiksCube::MOVE(rand() % 18));
    cout << "Starting IDDFS solve (max depth 7)...\n";
    IDDFSSolver<RubiksCube3dArray, Hash3d> solver(cube, 7);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 7: {
    cout << "Bitboard + BFS\n";
    RubiksCubeBitboard cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    cout << "Starting BFS solve...\n";
    BFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube);
    auto moves = solver.solve();
    cout << "Solution found with " << moves.size() << " moves: ";
    printMoves(moves, cube);
    break;
  }
  case 8: {
    cout << "Bitboard + DFS\n";
    RubiksCubeBitboard cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    cout << "Starting DFS solve (max depth 8)...\n";
    DFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, 8);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 9: {
    cout << "Bitboard + IDDFS\n";
    RubiksCubeBitboard cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    cout << "Starting IDDFS solve (max depth 8)...\n";
    IDDFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube, 8);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 10: {
    cout << "1D + IDA* (Korf Algorithm)\n";
    RubiksCube1dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    
    // Try to load corner database
    CornerDBMaker dbMaker;
    CornerPatternDatabase* cornerDB = nullptr;
    if (dbMaker.loadFromFile("corner_db.dat")) {
      cornerDB = &dbMaker.getDatabase();
      cout << "Corner pattern database loaded successfully.\n";
    } else {
      cout << "Corner pattern database not found. Running without heuristic.\n";
    }
    
    cout << "Starting IDA* solve (max depth 15)...\n";
    IdastarSolver<RubiksCube1dArray, Hash1d> solver(cube, cornerDB, 15);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 11: {
    cout << "3D + IDA* (Korf Algorithm)\n";
    RubiksCube3dArray cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    
    // Try to load corner database
    CornerDBMaker dbMaker;
    CornerPatternDatabase* cornerDB = nullptr;
    if (dbMaker.loadFromFile("corner_db.dat")) {
      cornerDB = &dbMaker.getDatabase();
      cout << "Corner pattern database loaded successfully.\n";
    } else {
      cout << "Corner pattern database not found. Running without heuristic.\n";
    }
    
    cout << "Starting IDA* solve (max depth 15)...\n";
    IdastarSolver<RubiksCube3dArray, Hash3d> solver(cube, cornerDB, 15);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 12: {
    cout << "Bitboard + IDA* (Korf Algorithm)\n";
    RubiksCubeBitboard cube;
    cout << "Shuffling cube with " << shuffleCount << " moves...\n";
    vector<RubiksCube::MOVE> shuffleMoves;
    for (int i = 0; i < shuffleCount; i++) {
      RubiksCube::MOVE move = RubiksCube::MOVE(rand() % 18);
      shuffleMoves.push_back(move);
      cube.move(move);
      cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\nCube solved after shuffling? " << (cube.isSolved() ? "YES" : "NO") << "\n";
    
    // Try to load corner database
    CornerDBMaker dbMaker;
    CornerPatternDatabase* cornerDB = nullptr;
    if (dbMaker.loadFromFile("corner_db.dat")) {
      cornerDB = &dbMaker.getDatabase();
      cout << "Corner pattern database loaded successfully.\n";
    } else {
      cout << "Corner pattern database not found. Running without heuristic.\n";
    }
    
    cout << "Starting IDA* solve (max depth 15)...\n";
    IdastarSolver<RubiksCubeBitboard, HashBitboard> solver(cube, cornerDB, 15);
    auto moves = solver.solve();
    if (moves.empty()) {
      cout << "No solution found within depth limit.\n";
    } else {
      cout << "Solution found with " << moves.size() << " moves: ";
      printMoves(moves, cube);
    }
    break;
  }
  case 13: {
    cout << "Generate Corner Pattern Database\n";
    cout << "Warning: This may take a very long time (hours/days) and require significant memory!\n";
    cout << "Continue? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
      CornerDBMaker dbMaker;
      dbMaker.generateDatabase();
      dbMaker.saveToFile("corner_db.dat");
      cout << "Corner database generated and saved to corner_db.dat\n";
    } else {
      cout << "Database generation cancelled.\n";
    }
    break;
  }
  default:
    cout << "Invalid choice. Please run again and choose a number between "
            "1-13.\n";
  }

  return 0;
}
