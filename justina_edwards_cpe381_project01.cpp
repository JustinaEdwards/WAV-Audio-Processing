/*
Justina Edwards
CPE 381 Project01
Program Name: justina_edwards_cpe381_project01.m
Charger ID: jle0025
UAH E-mail: jle0025@uah.edu
Description: This program will read the WAV file that was previously modified 
by the MATLAB program. It processes the audio sample by sample and rewrites the 
output using the equation:
out(t) = in(t) + 0.01 * rn(t) - 0.005 * Amax
in(t) is the input from the WAV file at time t, rn(t) is random noise that is constrained
 by Amax, and Amax is the maximum amplitude. After modifying the WAV file the program will
  write my name, file name, number of channels, the sampling frequency, number of bits sampled,
   the length of the record, maximum amplitude in each channel, and the program’s execution time.
*/
//C++ Standard Libraries
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
// Struct that parses the WAV header file
struct WAV_Header {
    char chunkID[4];			// contains letters RIFF in ASCII
    uint32_t chunkSize;			// The size of the entire file in bytes
    char format[4];				// contains letters WAVE big-endian form
    char subChunk1ID[4];		// contains letters fmt big-endian form
    uint32_t subChunk1Size;		// 16 for PCM
    uint16_t audioFormat;		// PCM=1 else there is some form of compression
    uint16_t numChannels;		// mono=1, stereo=2
    uint32_t sampleRate;		// sample rate in Hz
    uint32_t byteRate;			// (SampleRate * NumChannels * BitsPerSample)/8
    uint16_t blockAlign;		// (NumChannels * BitsPerSample)/8
    uint16_t bitsPerSample;		// number of bits per sample
    char subChunk2ID[4];		//contains letters data big-endian form
    uint32_t subChunk2Size;		// (NumSamples * NumChannels * BitsPerSample)/8
} WavHeader;

bool hasWavExtension(const string& filename) {
    // Find the position of the dot before the file extension
    size_t dotPosition = filename.find_last_of('.');
    
    if (dotPosition != string::npos) {
        // Get the file extension
        string extension = filename.substr(dotPosition);

        // Compare the extension with ".wav"
        if (extension == ".wav") {
            return true;
        }
    }

    //return false;
    return false;
}

bool hasTxtExtension(const string& filename) {
    // Find the position of the dot before the file extension
    size_t dotPosition = filename.find_last_of('.');
    
    if (dotPosition != string::npos) {
        // Get the file extension
        string extension = filename.substr(dotPosition);

        // Compare the extension with ".wav"
        if (extension == ".txt") {
            return true;
        }
    }

    //return false;
    return false;
}

// Function that writes aspects of the WAV file to a summary text file
void writeToSummaryFile(const string& name, const string& filename, uint16_t numChannels,int samplingFrequency, int numBitsSampled, int recordLength, const string& textfile, int maxAmplitudeLeft, int maxAmplitudeRight, clock_t start) 
{
    ofstream file(textfile); // Creates an output file to write to (overwrite old data)

    if (file.is_open()) { // Check if the file was opened
        file << "(a) Name: " << name<<endl; // Writes data to text file
        file << "(b) File Name: " << filename<<endl; // Writes data to text file
        file << "(c) Number of Channels: " << numChannels <<" Channels"<<endl; // Writes data to text file
        file << "(d) Sampling Frequency: " << samplingFrequency<<" Hz"<<endl; // Writes data to text file
        file << "(e) Number of Bits Sampled: " << numBitsSampled<<"-bit audio per sample"<<endl; // Writes data to text file
        file << "(f) Record Length (seconds): " << recordLength<<" seconds"<<endl; // Writes data to text file
        file << "(g) Maximum Absolute Value of Left Channel: " << maxAmplitudeLeft << endl;		// Writes data to text file
        file << "    Maximum Absolute Value of Right Channel: " << maxAmplitudeRight << endl;	// Writes data to text file
        clock_t end = clock();	//ends execution time
        double elapsed_time = double(end - start) / CLOCKS_PER_SEC * 1000.0;	//calculates total time milliseconds
        file << "(h) Execution Time of Program: " << elapsed_time<< " milliseconds" << endl;	// Writes data to text file
        file.close(); // Closes the file
        cout << "Content written to " << textfile << " successfully." << endl;	//success message
    } else {
        cerr << "Error: Unable to open and write to the file: " << textfile << endl; //error message
	}
}

int main() 
{
	//define starting values
	int maxAmplitudeLeft = 0; // maximum amplitude that will be used in calculations
	int maxAmplitudeRight = 0; // maximum amplitude that will be used in calculations
	int modifiedLeftSignal, modifiedRightSignal;
   
    random_device rd;
    mt19937 gen_left(rd());	//generate random number using mt19937
    mt19937 gen_right(rd());	//generate random number using mt19937
	
	string inFile; // justina_edwards_cpe381_project01_modified_matlab.wav
    string outFile; //justina_edwards_cpe381_project01_modified_c.wav
    string textfile; // justina_edwards_cpe381_project01_summary.txt
    cout<<"Enter the file name that the C++ program will modify: ";
	getline(cin,inFile); //processes user's input
	cout<<endl;
	ifstream inputFile(inFile, ios::binary);
    if (!inputFile) //checks input file is valid
	{
        cerr << "Error: Unable to open input file." << endl;
        return -1;
    }
	if(!hasWavExtension(inFile)) //checks extension
	{
		cerr << "Error: File inputted does not have .wav extension.";
		return -1;
	}
	
	cout<<"Enter the output WAV file name to write to: ";
	getline(cin,outFile); //processes user's input
	cout<<endl;
	hasWavExtension(outFile);
	if(!hasWavExtension(outFile))	//checks extension
	{
		cerr << "Error: File inputted does not have .wav extension.";
		return -1;
	}
	
	cout<<"Enter the name of the summary text file: ";
	getline(cin,textfile); //processes user's input
	cout<<endl;
	if(!hasTxtExtension(textfile)) //checks extension
	{
		cerr << "Error: File inputted does not have .txt extension.";
		return -1;
	}
	clock_t start = clock();	//starts timing program execution time
    // Read the header
    WAV_Header WavHeader;	//defines the header
    inputFile.read(reinterpret_cast<char*>(&WavHeader), sizeof(WAV_Header));	//reads the input file sample by sample

    // Modify the samples for each channel (gets data from header)
    const int bytesPerSample = WavHeader.bitsPerSample / 8;
    const int samplesPerChannel = WavHeader.subChunk2Size / (bytesPerSample * WavHeader.numChannels);
    vector<char> buffer(WavHeader.subChunk2Size);
    inputFile.read(buffer.data(), WavHeader.subChunk2Size);
    
	// Iterate through the audio samples
	for (int i = 0; i < WavHeader.subChunk2Size; i += bytesPerSample * WavHeader.numChannels) {
	    // Finds absolute value for the left sample
	    short* leftSample = reinterpret_cast<short*>(&buffer[i]);
	    int absoluteLeftSample = abs(*leftSample);
	
	    if (absoluteLeftSample > maxAmplitudeLeft) {
	        maxAmplitudeLeft = absoluteLeftSample;
	    }
	
	    // Finds absolute value for the right sample
	    short* rightSample = reinterpret_cast<short*>(&buffer[i + bytesPerSample]);
	    int absoluteRightSample = abs(*rightSample);
	
	    if (absoluteRightSample > maxAmplitudeRight) {
	        maxAmplitudeRight = absoluteRightSample;
	    }
	}
	//sets boundaries for left and right samples' random numbers between -maxAmplitude and maxAmplitude
    uniform_int_distribution<> dis_left(-maxAmplitudeLeft, maxAmplitudeLeft);
    uniform_int_distribution<> dis_right(-maxAmplitudeRight, maxAmplitudeRight);

	//reiterates through WAV file to modify output
	for (int i = 0; i < WavHeader.subChunk2Size; i += bytesPerSample * WavHeader.numChannels) 
	{	
		int leftRandom = dis_left(gen_left);	//random number
		int rightRandom = dis_right(gen_right);	//random number

		// Modify left channel (channel 1)
	    short* leftSample = reinterpret_cast<short*>(&buffer[i]);
	    
		modifiedLeftSignal = static_cast<int>(*leftSample)+0.01*leftRandom-0.005*maxAmplitudeLeft; // Modify the left channel sample cast as int to take care of overflow
		if (modifiedLeftSignal > numeric_limits<short>::max()) 	//checks if it exceeds the limit of the max short int
		{
			modifiedLeftSignal = numeric_limits<short>::max();	//sets to max value
		} 
		else if (modifiedLeftSignal < numeric_limits<short>::min()) //checks if it exceeds the limit of the negative max short int
		{
		    modifiedLeftSignal = numeric_limits<short>::min();	//sets to min value
		}
		*leftSample = static_cast<short>(modifiedLeftSignal);	//casts back to short int
	    // Move to the next sample for the right channel (channel 2)
	    short* rightSample = reinterpret_cast<short*>(&buffer[i + bytesPerSample]);
		
		modifiedRightSignal = static_cast<int>(*rightSample) + 0.01*rightRandom-0.005*maxAmplitudeRight;; // Modify the right channel sample cast as int to take care of overflow

		if (modifiedRightSignal > numeric_limits<short>::max()) 	//checks if it exceeds the limit of the max short int
		{
		    modifiedRightSignal = numeric_limits<short>::max();	//sets to max value
		} 
		else if (modifiedRightSignal < numeric_limits<short>::min()) //checks if it exceeds the limit of the negative max short int
		{
		    modifiedRightSignal = numeric_limits<short>::min();	//sets to min value
		}
	*rightSample = static_cast<short>(modifiedRightSignal);	//casts back to short int
	}
    // Write to the output file
    ofstream outputFile(outFile, ios::binary);
    if (!outputFile) 
	{
        cerr << "Error: Unable to open output file." << endl;
        return -1;
    }

    // Write the WavHeader and modified samples to the output file
    outputFile.write(reinterpret_cast<const char*>(&WavHeader), sizeof(WAV_Header));
    outputFile.write(buffer.data(), WavHeader.subChunk2Size);

    // Close files
    inputFile.close();
    outputFile.close();

 
	// Gathers the needed information from the WAV header files for summary file
	string name = "Justina Edwards";	// part (a) summary file
    string filename = ".wav";	// part (b) summary file
    int numChannels = WavHeader.numChannels;	// part (c) summary file
    int samplingFrequency = WavHeader.sampleRate;	// part (d) summary file
    int numBitsSampled = WavHeader.bitsPerSample;	// part (e) summary file
	int numSamples = (WavHeader.subChunk2Size*8)/(numChannels*numBitsSampled);
	int recordLength = (numSamples)/samplingFrequency;
	
	//write data to summary file
	writeToSummaryFile(name, outFile, numChannels, samplingFrequency, numBitsSampled, recordLength, textfile, maxAmplitudeLeft, maxAmplitudeRight, start);
	
    return 0;
}

