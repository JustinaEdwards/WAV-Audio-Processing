# CPE 381 Project01 MATLAB
## Program Name
justina_edwards_cpe381_project01.m
## Contact Me
- **Name**: Justina Edwards
- **Charger ID**: jle0025
- **UAH E-mail**: jle0025@uah.edu
## Contributors
- Justina Edwards
## Description
This MATLAB program is used to process the original 16 second introduction audio that starts with an introduction of myself and is followed by music. The modified WAV file will alter the original WAV file by altering the audio after 8 seconds with sine waves. The left channel of the modified WAV file will have a sine wave at 2310 Hz, the amplitude will be equal to 10% of the maximum amplitude of the signal, and will have an initial phase of π/4. The right channel of the modified WAV file will have a sine wave at 2300 Hz, the amplitude will be equal to 10% of the maximum amplitude of the signal, and will have an initial phase of 3π/4. The modified WAV file will contain the original audio until 8 seconds then the audio will be a high pitched noise for the remainder of the audio.

## How to Use
1. Open Linux terminal
2.  Download the justina_edwards_cpe381_project01.zip file.
3. Unzip justina_edwards_cpe381_project01.zip and navigate into the justina_edwards_cpe381_project01 directory.
4. Run MATLAB Program:
- Use the Linux command:
 **matlab -r "run('/path to project/justina_edwards_cpe381_project01/justina_edwards_cpe381_project01.m');"**
 - Replace the path **/path to project/justina_edwards_cpe381_project01/** with the correct path to your MATLAB script.
5. Input When prompted:
- The original WAV file
- Input the name for the modified WAV file
## Requirements
This program requires MATLAB to run.
## Usage Example
Example MATLAB Execution:
- matlab -r "run('/home/student/jle0025/justina_edwards_cpe381_project01/justina_edwards_cpe381_project01.m');"
- **Enter the original input WAV file path:** justina_edwards_cpe381_project01_original.wav
- **Enter the output for the modified WAV file path:** justina_edwards_cpe381_project01_modified_matlab.wav
- **The modified audio was successfully written to justina_edwards_cpe381_project01_modified_matlab.wav**
## Outputs
The modified audio will be written to the new WAV file.
## Technologies Used
- ChatGPT 3.5 for generating code snippets and assisting with documentation
- Linux gcc/g++
- MATLAB R2023a
