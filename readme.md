# Sorting Algorithm Visualization with SDL2 in CLion

This C++ project demonstrates the visualization of various sorting algorithms using SDL2 library in CLion IDE.

## Prerequisites

- [CLion IDE](https://www.jetbrains.com/clion/)
- C++ compiler
- SDL2 library installed

## Getting Started

1. **Clone the repository:**

    ```bash
    git clone https://github.com/Jonatan-Perret/Cplusplus-sorting-algorithm-showcase.git
    cd sorting-algorithm-visualization-sdl2
    ```

2. **Open the project in CLion:**

    - Open CLion IDE.
    - Go to `File > Open...` and select the `Cplusplus-sorting-algorithm-showcase` directory.

3. **Configure SDL2 in CLion:**

    - Make sure you have SDL2 installed on your system.
    - Set up SDL2 in CLion:
        - Right-click on the project folder in CLion.
        - Navigate to `CMakeLists.txt`.
        - Add the following lines:

        ```cmake
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(your_project_name ${SDL2_LIBRARIES})
        ```

4. **Build and Run the project:**

    - Build the project using the CLion Build button or the following keyboard shortcut: `Ctrl + F9`.
    - Run the program using the Run button or `Shift + F10`.

5. **Usage**

    - Upon running the program, a window will open displaying bars representing an array.
    - Press the following keys to visualize sorting algorithms:
        - `b` key: Bubble Sort
        - `s` key: Selection Sort
        - `i` key: Insertion Sort
        - `r` key: Randomize the array for re-sorting visualization

## Contributing

Contributions are welcome! If you have suggestions, enhancements, or find issues, feel free to create an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- Thanks to SDL2 library for providing a simple way to create graphical applications in C++.
