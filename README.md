# 🐍 Snake Game — C + GTK3

Hey! This is a classic Snake game built from scratch using **C** and **GTK3** for graphics. Control a snake, eat food, grow longer, and try not to crash into yourself or the walls. Built by a group of 6 first year students as our IC group project.

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| `↑ ↓ ← →` or `W A S D` | Move |
| `P` | Pause / Unpause |
| `R` | Restart |
| `Q` / `Escape` | Quit |

Each food dot = **10 points**. Beat your high score!

---

## 📁 Project Structure

```
snake-game/
├── snake.h    ← The "dictionary" — all shared definitions 
├── structs.c  ← The "setup crew" — game init & food placement
├── logic.c    ← The "brain" — movement, collisions, scoring 
├── ui.c       ← The "artist" — draws everything on screen 
├── input.c    ← The "ears" — keyboard input handling 
├── main.c     ← The "main door" — GTK window setup & entry point 
└── Makefile   ← Shortcut to compile everything
```

---

## 🛠️ Setup & Run

**Linux:**
```bash
sudo apt install libgtk-3-dev gcc
```

**Windows** — Install [MSYS2](https://www.msys2.org), open MSYS2 MINGW64 terminal:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk3 mingw-w64-x86_64-pkg-config
```

**macOS:**
```bash
brew install gtk+3
```

**Compile & Run:**
```bash
gcc main.c structs.c logic.c ui.c input.c -o snake_game $(pkg-config --cflags --libs gtk+-3.0)
./snake_game
```
Or just: `make && ./snake_game`

---

## 🧠 How It Works

- **Game Loop** — GTK calls `game_tick()` every 140ms. Each tick: move → check collisions → redraw. Like a flipbook animation.
- **Direction Buffering** — Key presses are saved in `next_dir` and applied next tick, preventing the snake from reversing into itself.
- **Snake Body** — Stored as an array of (x, y) points. `memmove()` shifts all segments forward each tick, new head placed at front.
- **Drawing** — Screen redrawn in 8 layers every tick: background → grid → food → snake → overlays.

---

## 👥 Team — Low Key Serpents 🐍

| Member | File | Role |
|--------|------|------|
| Aravind | `snake.h` | Header — structs, constants, prototypes |
| Tushar | `structs.c` | Game init and food placement |
| Bhargav | `logic.c` | Game loop, movement, collision detection |
| Umesh Chandra | `ui.c` | Cairo graphics and rendering |
| Randhir | `input.c` | Keyboard input handling |
| Subramanyam | `main.c` | GTK window setup and entry point |

---

## 📚 Libraries

- **GTK3** — Game window and event handling
- **Cairo** — 2D drawing (shapes, text, gradients)
- **GLib** — Timer, boolean types (bundled with GTK3)

---

## ⚠️ Known Limitations

- High score resets on exit (no file saving yet)
- Fixed window size, no fullscreen
- No sound effects

---
