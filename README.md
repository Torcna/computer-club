# Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/Torcna/computer-club.git
2. Update and initialize git submodules:
   ```bash
   git submodule update --init --recursive
3. Create two directories: `bin` and `build`:
   ```bash
   mkdir bin && mkdir build
4. Navigate to the build directory and run the project generation:
   ```bash
   cd build && cmake ..
5. Build the project in Release mode:
   ```bash
   cmake --build . --config Release

Done! Now you have a built project.

# Executable Files

After building the project, two executable files will be located in the `bin` directory:

1. **club**  
   This is the main executable file. To run it, you need to provide a single argument — the name of the input data file. Example:
   ```bash
   ./club data_default.txt
Input data should be located in the `files_for_main_task/` directory. You can use the provided files from this directory or add your own.

2. **tests**   
   This is the binary that runs the tests implemented with Google Test. No additional arguments are needed. Simply run the file
   ```bash
   ./tests

Tests will use input data from the `files_for_tests/` directory.

# Project Structure

![heheh](https://github.com/user-attachments/assets/87192843-305d-45cc-9bba-78a5639bc7b9)

