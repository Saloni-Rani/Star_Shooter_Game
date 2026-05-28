# Star_Shooter_Game
# Advanced Star Shooter Game

A simple yet exciting **2D Space Shooter Game** built using **C++** and **OpenGL/GLUT**.
Control your spaceship, destroy star enemies, and achieve the highest score before time runs out!

---

# 🕹️ Controls

| Key           | Action        |
| ------------- | ------------- |
| ⬅ Left Arrow  | Move Left     |
| ➡ Right Arrow | Move Right    |
| Spacebar      | Shoot Bullets |
| R             | Restart Game  |
| ESC           | Exit Game     |

---

# 🛠️ Technologies Used

* **C++**
* **OpenGL**
* **GLUT (OpenGL Utility Toolkit)**

---

# ▶️ How to Run

## 💻 Windows (CodeBlocks / VS Code / Dev-C++)

### Install:

* MinGW Compiler
* OpenGL Libraries
* FreeGLUT

### Compile Command

bash
g++ main.cpp -o game -lfreeglut -lopengl32 -lglu32

### Run
bash
./game

---

## 🍎 macOS

### Install GLUT

GLUT is usually pre-installed on macOS.

### Compile Command
bash
g++ main.cpp -framework OpenGL -framework GLUT -o game

### Run
bash
./game

---

## 🐧 Linux (Ubuntu)

### Install Dependencies
bash
sudo apt update
sudo apt install freeglut3-dev

### Compile Command

bash
g++ main.cpp -o game -lGL -lGLU -lglut

### Run

bash
./game


# 🎯 Gameplay Rules

* Shoot enemies to increase your score.
* Each successful hit increases:

  * Score
  * Hit Counter
* Missing shots still increase shot count.
* Game ends after **50 seconds**.
* Highest score is stored during runtime.

---

# 📸 Game Preview

Features included in gameplay:

* Smooth enemy movement
* Real-time bullet collision detection
* Dynamic score updates
* Restartable gameplay

---

# 🔥 Future Improvements

Possible upgrades for the game:

* 👾 Different enemy types
* 🔊 Sound effects & music
* 🏅 Permanent high score saving
* ⚡ Power-ups and boosters


