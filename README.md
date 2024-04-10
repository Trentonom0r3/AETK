
# Adobe After Effects Plugin Standard Library Toolkit (AETK)

Welcome to the Adobe After Effects Plugin Standard Library (AETK), a modern C++ framework designed to revolutionize the way developers create plugins for Adobe After Effects. Aimed at both newcomers and seasoned plugin developers, AETK provides an extensive suite of tools and abstractions that streamline the development process, enabling more focus on creativity and innovation.

## Features

- **Modern C++ Design**: Leveraging modern C++ features for a clean, robust, and efficient codebase.
- **Comprehensive Suite Handling**: Simplified interactions with After Effects' diverse suites, from item management to rendering.
- **Automatic Memory Management**: AETK Handles disposing AEGP handles as necessary, so you can focus on writing plugins!
- **Object-Oriented Approach**: AETK's design revolves around intuitive object-oriented principles, making plugin development more accessible and maintainable.
- **Efficient Asset Management**: Tools for importing, handling, and manipulating assets within After Effects projects.
- **Rendering and Composition**: Advanced support for rendering options, composition items, and layer management to create sophisticated visual effects.
- **Error Handling and Debugging**: Built-in mechanisms for error reporting and debugging to ensure stability and reliability.
- **Abstracted Plugin Design**: Use templated classes to structure your AEGP plugin in a more intuitive way, getting rid of the complex AE details.

## Getting Started

Dive into AETK with detailed documentation and examples to kickstart your plugin development. See docs [here](https://github.com/Trentonom0r3/AETK/blob/main/docs/AETK.pdf).

```cpp
#include "AETK/AEGP/AEGP.hpp"

// Example: Simplified access to After Effects functionalities
AE::App app;
app.Alert("Welcome to AETK!");
```

## Sample Projects

To help you get started with AETK, we've provided some sample projects that demonstrate the capabilities and best practices of AETK plugin development. These projects range from simple examples for beginners to more complex plugins for advanced users.

### AEGP Skeleton

This project demonstrates the basic structure for creating AEGP Plugins with AETK.

- **Project Repository**: [Skeleton](https://github.com/Trentonom0r3/AETK/tree/main/AEGP/Skeleton)
- **Features Demonstrated**: Object-oriented plugin design.
- **Level**: Beginner

### Grabba

A recreation of the original 'Grabba' Sample Project from the vanila SDK.

- **Project Repository**: [Grabba](https://github.com/Trentonom0r3/AETK/tree/main/AEGP/Grabba)
- **Features Demonstrated**: Object-oriented plugin design, retrieving and saving frames from compositions.
- **Level**: Beginner
- 
### LayerDumper

An intermediate project showcasing how to interract with layers and their properties using AETK.

- **Project Repository**: [LayerDumper](https://github.com/Trentonom0r3/AETK/tree/main/AEGP/LayerDumper)
- **Features Demonstrated**: Object-oriented plugin design, Efficient asset management, layer/property manipulation.
- **Level**: Intermediate

### TaskScheduler

A simple project showcasing advanced Ideas such as Scheduling AE tasks from threads. 

- **Project Repository**: [TaskScheduler](https://github.com/Trentonom0r3/AETK/tree/main/AEGP/TaskScheduler)
- **Features Demonstrated**: Object-oriented plugin design, AE execution from a threaded plugin. 
- **Level**: Intermediate

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

## License

Distributed under the MIT License. See `LICENSE` for more information.
