# Synthesizer

This is a open-source **Computer Keyboard based wave table Synthesizer** - that means that it's essentially a Synthesizer engine that run on your machine without need for specific DAW to run it, and the note selected from the computer keyboard. <br/> 

## Built With
This project is built and tested on a WSL-2 environment using modern development tools and libraries:

* C++ (C++23): The synthesizer engine is implemented using the latest C++ standards.
* nlohmann/json (v3.11.2): A widely used JSON library for configuration and data handling in C++.
* PortAudio (portaudio-2.0): A cross-platform audio I/O library for real-time audio synthesis. On Ubuntu, install it with:
```
sudo apt-get install portaudio19-dev
```
* CMake (v3.12+): Used for project configuration and build management.

## Getting Started
Before building the Keyboard Synthesizer, ensure your development environment meets the following prerequisites:

### Prerequisites
* Operating System: Tested on WSL-2 (Ubuntu); instructions may vary on other systems.
* C++ Compiler: Supports C++23.
* CMake: Version 3.12 or later.
* pkg-config: Used for dependency management.
* PortAudio: Required for audio I/O.

On Ubuntu, install with:
```
sudo apt-get install portaudio19-dev
```
Note: nlohmann/json: The JSON library is automatically downloaded using CMake's FetchContent.

### Installation
Clone the Repository:

```
git clone https://github.com/SappirBo/KeyboardSynthesizer.git
cd KeyboardSynthesizer
```

Create a Build Directory and Configure the Project:
```
mkdir build
cd build
cmake ..
```
Note: The CMake script will automatically fetch the nlohmann JSON library and check for PortAudio. If PortAudio is not found, you will see an error message with instructions to install it.

Build the Project:
```
make
```

Run Tests (Optional): If you want to run the tests, execute:
```
ctest
```
Once built, you can run the synthesizer executable from the build directory. For any further configuration or usage details, refer to the Usage section below.

## Usage

## Contributing

## Acknowledgments
* [Readme-Template](https://github.com/othneildrew/Best-README-Template/tree/main)
