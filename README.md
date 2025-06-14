# Discount System

A C++ discount system that implements various discount strategies.

## Features

- Multiple discount strategies (Percentage, Threshold, User Level, etc.)
- Composite discount strategies
- Time-limited discounts
- Factory pattern for strategy creation

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Testing

```bash
cd build
ctest
```

## CI

This project uses GitHub Actions for continuous integration. The CI pipeline:
- Builds the project
- Runs unit tests
- Triggers on push to main and pull requests 
