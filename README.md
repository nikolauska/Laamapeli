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

Optional development tooling:

```sh
cmake --build build --target format      # check formatting
cmake --build build --target fix-format  # apply formatting
cmake -S . -B build-asan "-DUSE_SANITIZER=Address;Undefined"
cmake -S . -B build-tidy -DUSE_STATIC_ANALYZER=clang-tidy
```

Formatting targets use installed `clang-format` and/or `cmake-format`.
Sanitizers require Clang or GCC. Static analyzers may be combined with a
semicolon-separated list of `clang-tidy`, `iwyu`, and `cppcheck`; selected
tools must be installed.
