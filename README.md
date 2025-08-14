# Jumpster

Jumpster è un semplice platformer in C++/SDL2 con animazione sprite.

## Compilazione

1. Assicurati di avere installato:
   - SDL2
   - SDL2_image
   - CMake
   - Un compilatore C++ (g++ consigliato)

2. Da terminale, nella root del progetto:

```sh
mkdir build
cd build
cmake ..
make
./jumpster
```

## Struttura delle directory

- `src/`         — Codice sorgente C++ del gioco
- `include/`     — Header file C++
- `resources/`   — Immagini e asset grafici (background, sprite, ecc.)
- `build/`       — Directory di build (creata da CMake)

## Note
- Le immagini devono trovarsi nella cartella `resources/` o essere referenziate come `../resources/` a seconda del punto di esecuzione.
- Il criceto è animato tramite uno sprite sheet PNG da 16 frame.
