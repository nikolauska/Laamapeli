Laamapeli
=========

Requires CMake 3.20 or newer, a C++ compiler, `pkg-config`, and Allegro 5.2.6
or newer with its main, image, font, TTF, audio, codec, and dialog addons.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target Laamapeli
./build/Laamapeli
```

CMake stages the game assets and initial settings beside the executable.
Multi-configuration generators additionally require `--config Release` when
building; run the executable from that configuration's output directory.
