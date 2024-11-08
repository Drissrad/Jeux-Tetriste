# Project Title: Puzzle Game (Tetris-inspired)

## Table of Contents
1. [Introduction](#introduction)
2. [Description](#description)
   - [Game Mechanics](#game-mechanics)
   - [Features](#features)
   - [Gameplay](#gameplay)
3. [Design](#design)
   - [Class Diagram](#class-diagram)
   - [State Diagram](#state-diagram)
4. [Analysis and Discussion](#analysis-and-discussion)
   - [Target Audience](#target-audience)
   - [Strengths](#strengths)
   - [Weaknesses](#weaknesses)
   - [Innovations and Contributions](#innovations-and-contributions)
5. [Conclusion](#conclusion)

---

## Introduction
This project introduces a novel approach to puzzle games inspired by the classic Tetris concept, emphasizing data structures such as singly and doubly linked lists to enhance the user experience with fluid and immersive gameplay.

## Description

### Game Mechanics
- **Piece Generation**: Randomly generates pieces with specific colors and shapes.
- **Piece Insertion**: Players must insert pieces onto the game board, choosing where (left or right) to place them.
- **Piece Removal**: If three consecutive pieces match in color or shape, they are automatically removed from the board.
- **Shifts**: Players can perform left shifts to reposition pieces, creating new opportunities for matches and removals.

### Features
- **Random Piece Generation**: Pieces are created with predefined colors and shapes, providing variety.
- **User Interaction**: Players can insert and shift pieces on the board to maximize their score and clear lines.
- **Automatic Removals**: The system detects consecutive matches and removes pieces accordingly.
- **User Interface**: Provides an engaging and user-friendly visual interface.

### Gameplay
Players insert randomly generated pieces onto the game board with the objective of creating consecutive matching pieces in terms of color or shape. Effective strategy is necessary for anticipating future moves and creating beneficial matches to clear the board and score points.

## Design

### Class Diagram
Illustrates the main classes, their attributes, and relationships, highlighting the structural design of the game.

### State Diagram
Represents the various states of game objects and transitions that occur as players interact with the game.

## Analysis and Discussion

### Target Audience
The primary audience consists of puzzle and strategy game enthusiasts who enjoy mental challenges and planning ahead. This game also appeals to those who prefer a slower-paced, thoughtful approach to gaming.

### Strengths
- **Unique Game Mechanics**: Combines shape manipulation and piece removal in a novel way.
- **Strategic Depth**: Players must carefully plan their moves to create matches while managing board space.
- **Replayability**: Randomized piece generation offers a unique experience for every playthrough.

### Weaknesses
- **Learning Curve**: Initial complexity due to removal and shifting mechanics may be challenging for new players.

### Innovations and Contributions
- Combines shape manipulation and matching mechanics in a fresh puzzle experience.
- The use of circularly linked lists for piece connections adds strategic depth.

## Conclusion
This puzzle game offers a unique blend of shape manipulation and piece-matching mechanics, requiring strategic planning to achieve high scores. Feedback-driven improvements, enhanced visuals, and additional features are planned for future updates to maximize user satisfaction.

---


