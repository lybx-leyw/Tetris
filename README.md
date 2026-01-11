# Tetris

This is a Tetris game project I created to **solidify my C programming foundation**. A simple Tetris game implemented based on the ACLLib graphics library, developed using pure C language.

## License Description

This project uses the **GNU General Public License v3.0** license, primarily for:
1.  **Learning and Exchange**: To share with other students learning C language for reference.
2.  **Code Showcase**: To serve as proof of personal programming ability.
3.  **Open Source Contribution**: To contribute a student project to the open-source community.

**Important Note**: This project includes the Zhejiang University ACLLib graphics library, which also follows the GPL v3 license. See [LICENSE](LICENSE) for details.

## Project Structure

```
Tetris/
├── acllib.c
├── acllib.h
├── main.c               # Main game program
├── main.h               # Main header file
├── draw.c               # Graphics drawing module
├── draw.h               # Graphics drawing header file
├── map.c                # Game map and block management
├── map.h                # Map management header file
├── recore.c             # Score recording module
├── recore.h             # Score recording header file
├── Tetris.dev
├── best_record.txt
└── recore.txt
```

## Project Setup Steps
1.  Download and install Dev-C++.
2.  Double-click to open the `Tetris.dev` project file.
3.  Click **Compile & Run** (F11) to start the game.
4.  After modifying the code, recompile to see the effects immediately.

## Algorithm Features
Linear transformation handles block rotation.
```c
// Rotation matrix calculation
void line_change(int* x, int* y, int line[2][3]) {
    int a = *x;
    int b = *y;
    *x = line[0][0]*a + line[0][1]*b + line[0][2];
    *y = line[1][0]*a + line[1][1]*b + line[1][2];
}

// Rotate block
void rotate_block(Blockstate* state) {
    // Calculate rotation matrix
    int rotation_matrix[2][3] = {
        {0, -1, state->x + state->y},
        {1,  0, state->y - state->x}
    };

    // Apply to each block unit
    for (each block unit) {
        line_change(&unit_x, &unit_y, rotation_matrix);
    }
}
```

## Core Game Features

### 1. Score and Level System
```c
// Score calculation formula
Single line clear: +200 points
Double line clear: +800 points (200×2²)
Triple line clear: +1800 points (200×3²)
Tetris (four lines): +3200 points (200×4²)
Soft drop bonus: +10 points per cell
```

### 2. Speed Adjustment Mechanism
-   **Base Speed**: 1000ms/cell (adjustable)
-   **Speed Control**: S key for ×2 acceleration, Q key for ÷2 deceleration
-   **Soft Drop**: Hold Down Arrow key for temporary acceleration

### 3. Special Functions
-   **Clear Chance**: One chance to clear the board per game (C key)
-   **Pause Function**: Pause the game anytime (P key)
-   **Restart**: Reset the game with one key (R key)

## Acknowledgments

-   **Thanks to the ACLLib Team**: For providing an excellent C language graphics library, lowering the learning barrier.
-   **Thanks to teachers and classmates**: For the help and encouragement during the learning process.
-   **Thanks to my persistent self**: For completing the first full programming project.

---

Welcome everyone to submit issues and improvement suggestions.
This project is for learning and exchange purposes only.

---
**Author**: Zhejiang University Student - Lüyibuxi
**Version**: 1.0
**Core Code Completion Date**: August 14, 2025
**Open Source Release Date**: January 3, 2026

---
## Appendix: Game Interface Showcase

<img alt="Pasted image 20260103133309" src="https://github.com/user-attachments/assets/9cd58e30-08f3-4f3b-aa77-afffa6417550" />
*Game Guide Interface*

<img alt="Pasted image 20260103133227" src="https://github.com/user-attachments/assets/c9eef9eb-8ed7-404e-90fc-473fb130a0d5" />
*Normal Game Interface*

<img alt="Pasted image 20260103133403" src="https://github.com/user-attachments/assets/54ec583c-07bb-475a-ba3d-4c796c9dcbda" />
*Single Line Clear Interface*
