#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <unistd.h>

using namespace std;

// Function to play a note with a specified frequency and duration
void playNote(double frequency, int duration) {
    if (frequency == 0) {
        // If the frequency is 0, it's a rest, so sleep for the duration
        usleep(duration * 1000); // usleep takes microseconds
    } else {
        // Calculate the period of the note
        double period = 1.0 / frequency;
        // Calculate the duration of each half of the period in milliseconds
        int half_period_duration = period * 500;
        // Calculate the number of cycles for the duration
        int num_cycles = duration / (2 * half_period_duration);
        // Generate the note by toggling between sound and silence
        for (int i = 0; i < num_cycles; ++i) {
            // Sound on
            cout << "\a"; // Beep sound
            usleep(half_period_duration * 1000);
            // Sound off
            usleep(half_period_duration * 1000);
        }
    }
}

// Function to play a piano key with a specified frequency
void playPianoKey(char key) {
    switch (key) {
        case 'a':
            playNote(261.63, 500); // Middle C
            break;
        case 's':
            playNote(293.66, 500); // D
            break;
        case 'd':
            playNote(329.63, 500); // E
            break;
        case 'f':
            playNote(349.23, 500); // F
            break;
        case 'g':
            playNote(392.00, 500); // G
            break;
        case 'h':
            playNote(440.00, 500); // A
            break;
        case 'j':
            playNote(493.88, 500); // B
            break;
        case 'k':
            playNote(523.25, 500); // High C
            break;
        default:
            cout << "Invalid key! Press a valid piano key (a-g).\n";
    }
}

int main() {
    // Loop to continuously read input and play piano keys
    char input;
    cout << "Press keys (a-g) to play piano notes. Press 'q' to quit.\n";
    while (true) {
        cin >> input;
        if (input == 'q') {
            break; // Exit the loop if 'q' is pressed
        }
        playPianoKey(input);
    }
    cout << "Exiting...\n";
    return 0;
}
