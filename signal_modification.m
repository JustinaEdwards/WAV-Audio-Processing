%% Justina Edwards
%% CPE 381 Project01
%% Program Name: justina_edwards_cpe381_project01.m
%% Charger ID: jle0025
%% UAH E-mail: jle0025@uah.edu
%% Description: This program replaces the signa; from t=8s to t=16s with
%% altered left and right channels. The left channel will have sine wave at
%% f = 2310 Hz, amplitude equal to 10% of the maximum possible amplitude of
%% the signal, and initial phase of p/4. The right channel will have sine 
%% wave at f = 2300 Hz, amplitude equal to 10% of the maximum possible 
%% amplitude of the signal, and initial phase of 3p/4.

%% Initial Variable Values
t=8; % time where audio starts to get modified

% left channel data
frequency_left = 2310; % 2,310 Hz for the left sine wave
initial_phase_left=(pi)/4;
% right channel data
frequency_right = 2300; % 2,300 Hz for the left sine wave
initial_phase_right=(3*pi)/4;

%% Process the original .wav file
% read in the .wav file using the file path
wav_input_filename = input("Enter the original input .wav file path: ", "s");
if ~contains(wav_input_filename, '.wav')
    error('Error: The text does not contain the extension .wav');
end
if exist(wav_input_filename, 'file') ~= 2
    error('Error: The input file does not exist or can not be opened.');
end
% pulls the audio data and sampling rate from the original audio file
[y, Fs] = audioread(wav_input_filename);

% Calculate the amplitude in the signal
max_amplitude_10 = 0.1*(max(abs(y(:)))); % Ten percent of the maximum signal

% user inputs output file name for modified audio
wav_output_filename = input("Enter the output for the modified .wav file path: ", "s");
if ~contains(wav_output_filename, '.wav')
    error('Error: The text does not contain the extension .wav');
end
% Defines the left and right channels in the .wav file
left_channel = y(:, 1);
right_channel = y(:, 2);

% total time divided by sampling rate of the audio
time_total = (0:(length(y) - 1)) / Fs;
% time array after 8 seconds
index_t_8 = find(time_total >= 8, 1);

%% Calculates left channel
left_channel_modified=left_channel;
left_channel_modified(index_t_8:length(left_channel), 1) = max_amplitude_10 * sin(2 * pi * frequency_left * time_total(index_t_8:length(left_channel))' + initial_phase_left);

%% Calculates right channel
right_channel_modified=right_channel;
right_channel_modified(index_t_8:length(right_channel), 1) = max_amplitude_10 * sin(2 * pi * frequency_right * time_total(index_t_8:length(right_channel))' + initial_phase_right);

% Combines the left and right channel into a singular stereo signal
modified_signal = [left_channel_modified, right_channel_modified];

% Write the modified signal to a new WAV file
audiowrite(wav_output_filename, modified_signal, Fs);

disp(['The modified audio was successfully written to ', wav_output_filename]);

%% Plot signal changes for report/debugging (comment out before turning in project)
%{
subplot(4, 1, 1);
plot(time_total, y, 'b');
xlabel('Time (s)');
ylabel('Amplitude');
title('Original Audio');

% Plotting the left channel
subplot(4, 1, 2);
plot(time_total, left_channel_modified, 'r');
xlabel('Time (s)');
ylabel('Amplitude');
title('Modified Left Channel');

% Plotting the right channel
subplot(4, 1, 3);
plot(time_total, right_channel_modified, 'b');
xlabel('Time (s)');
ylabel('Amplitude');
title('Modified Right Channel');

% Plotting the combined stereo signal
subplot(4, 1, 4);
% Plotting the combined signal
plot(time_total, modified_signal(:, 2), 'm'); % Right channel
hold on;
plot(time_total, modified_signal(:, 1), 'g'); % Left channel with a thicker line
hold off;
xlabel('Time (s)');
ylabel('Amplitude');
title('Modified Stereo Signal');
legend('Right Channel', 'Left Channel');
%}
