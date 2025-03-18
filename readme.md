# Synthesizer

This is a open-source **Computer Keyboard based wave table Synthesizer** - that means that it's essentially a Synthesizer engine that run on your machine without need for specific DAW to run it, and the note selected from the computer keyboard. <br/> 

## Built With
The program built and tested on WSL-2 machine, using the following:
* C++
  * nlohmann
  * portaudio-2.0
* CMake
  
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
