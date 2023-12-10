# CPE 381 Project01 C++
## Program Name
signal_modification_project01.cpp
## Contact Me
- **Name**: Justina Edwards
- **Charger ID**: jle0025
- **UAH E-mail**: jle0025@uah.edu
## Contributors
- Justina Edwards
## Description
This program will read the WAV file that was previously modified by the MATLAB program. It processes the audio sample by sample and rewrites the output using the equation:
**out(t) =  in(t) + 0.01  ∗  rn(t)  −  0.005  ∗  Amax**
in(t) is the input from the WAV file at time t, rn(t) is random noise that is constrained by Amax, and Amax is the maximum amplitude.
After modifying the WAV file the program will write my name, file name, number of channels, the sampling frequency, number of bits sampled, the length of the record, maximum amplitude in each channel, and the program's execution time.
## How to Use
1. Open Linux terminal
2.  Download the signal_modification_project01.zip file.
3. Unzip signal_modification_project01.zip and navigate into the signal_modification_project01 directory.
4. Run C++ Program:
- Use the Linux command to compile the program:
 **g++ -std=c++11 signal_modification_project01.cpp -o signal_modification_project01**
 - Execute the C++ file: **./signal_modification_project01** 
5. Input When prompted:
- The modified MATLAB WAV file name
- Input the name for the modified WAV file
- Input the name for the summary text file
## Requirements
This program requires C++ to run.
The program requires that the user uses the C++11 standard compiler flag
## Usage Example
Example C++ Execution:
-  **g++ -std=c++11 signal_modification_project01.cpp -o signal_modification_project01**
- **./signal_modification_project01**
- **Enter the file name that the C++ program will modify:** signal_modification_project01_modified_matlab.wav
- **Enter the output WAV file name to write to:** signal_modification_project01_modified_c.wav
- **Enter the name of the summary text file:** signal_modification_project01.txt

## Outputs
The modified audio will be written to the new WAV file.
## Technologies Used
- ChatGPT 3.5 for generating code snippets and assisting with documentation
- Linux gcc/g++
- C++
