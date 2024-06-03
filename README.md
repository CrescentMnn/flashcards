## FLASHCARDS

This is a personal project in which I've implemented a simple flashcards program. It's designed to help with studying by allowing users to create and review flashcards.

### Installation

To run the flashcards program, you'll need:

- C++ compiler (supporting C++11)
- Basic understanding of the command line interface

#### Dependencies

- None

#### Building from Source

1. **Clone the repository:**

    ```bash
    git clone https://github.com/CrescentMnn/flashcards.git
    ```

2. **Navigate to the project directory:**

    ```bash
    cd flashcards
    ```

3. **Navigate to the appropriate source folder based on your system:**

    - For Linux:
    
    ```bash
    cd src/linux
    ```
    
    - For Windows:
    
    ```bash
    cd src/windows
    ```

4. **Compile the program:**

    -For linux:

    ```bash
    g++ -o flashcards flashcards_lin.cpp
    ```

    -For windows:

    ```bash
    g++ -o flashcards.exe flashcards_win.cpp
    ```

### Usage

#### Creating a New Flashcards File

To create a new flashcards file, follow these steps:

1. **Run the program:**

    ```bash
    ./flashcards
    ```
    or

    ```bash
    flashcards.exe
    ```

1. **Choose the option to create a new file.**
2. **Enter the name for the new file when prompted.**
3. **Input the size of the flashcards and provide questions and answers for each card.**
4. **Once finished, the program will save the session to the file.**

#### Reading an Existing Flashcards File

To read an existing flashcards file, follow these steps:

1. **Run the program:**

    ```bash
    ./flashcards
    ```
    or

    ```bash
    flashcards.exe
    ```

2. **Choose the option to read an existing file.**
3. **Enter the name of the existing file when prompted.**
4. **The program will load the flashcards from the file.**

#### Using the Flashcards

After creating or reading a file, you'll be presented with the main menu. From here, you can choose between a study session or a quiz session.

- **Study Session**: You'll be shown each flashcard question one by one, and you can provide answers. The program will tell you if your answer is correct.
- **Quiz Session**: You'll answer flashcard questions as they come, without immediate feedback. At the end, your grade will be provided based on the number of correct answers.

### Examples

Here's an example of running a study session:

