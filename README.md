# sqlmini

sqlite3 clone

## Building and Running

If you wish to build clox yourself you will need CMake (>=v3.21) and any relatively
recent C compiler. This project has a relatively simple CMake config utilising CMake
presets to control flags and build options.

```sh
cmake -S . -B build --preset=<platform>
cmake --build build
./build/sqlmini
```

Available platforms:

- linux
- linux-dev
- macos
- macos-dev
- win64
- win64-dev
- sanitize : Turns on GCC or Clang compiler instrumentation for sanitizers on Linux
             platforms
- linux-dev-strict : Additional checks made on linux using `clang-tidy` and `cpp-check`

## Testing

### Sanitizers

```sh
cmake -S . -B build/sanitize --preset=sanitize
cmake --build build/sanitize
build/sanitize/sqlmini
```

### Insert Tests with Ruby

```sh
bundle install
bundle binstubs rspec-core
bundle exec rspec
```

