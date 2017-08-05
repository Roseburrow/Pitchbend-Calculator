/*Calculates the deviation of an entered frequency above or below the closest
note.*/

#include <stdio.h>
#include <math.h>

//Gets the midinote closest to a given frequency and returns it.
double getMidi(double frequency, double c0, double semitone_ratio)
{
    frequency = log(frequency / c0) / log(semitone_ratio);
    return frequency;
}

//Gets the frequency of a given midi note and returns it.
double getFrequency(int midinote, double c0, double semitone_ratio)
{
    double closestFreq = c0 * pow(semitone_ratio, midinote);
    return closestFreq;
}

int main()
{
    int closestmidinote, nextclosestnote, percentage; //Stores rounded values.
    double semitone_ratio;
    double c0; //The frequency of midi note 0.
    double c5; //The frequency of middle C.
    double inputfreq, closestnoteUR, closestfreq, nextclosestfreq;
    double benddifference; //The difference between the input and the closest.
    double notedifference; //The difference between the 2 closest notes.
    double percentageUR; //The unrounded percentage.

    //CALCULATE REQUIRED VALUES.
    semitone_ratio = pow(2.0, 1.0/12.0); //Approx 1.0594631.
    c5 = 220.0 * pow(semitone_ratio, 3.0);
    c0 = c5 * pow(0.5, 5.0);
    
    //Get input frequency...
    printf("Please enter a frequency: ");
    scanf("%lf", &inputfreq);

    //Find the closest midinote...
    closestnoteUR = getMidi(inputfreq, c0, semitone_ratio);
    closestmidinote = (int) (closestnoteUR + 0.5); //Round closestnote.    
    
    //Get the frequency of the closest midi note...
    closestfreq = getFrequency(closestmidinote, c0, semitone_ratio);
    nextclosestnote = closestmidinote;
    
    //Determine if the next note should be one higher or lower.
    if (closestfreq > inputfreq)
    {
	nextclosestnote -= 1;
    }
    else nextclosestnote += 1;
    
    //Get the frequency of the next closest midi note.
    nextclosestfreq = getFrequency(nextclosestnote, c0, semitone_ratio);

    //The actual pitchbend calcualtion:

    //Get the difference between the input freq and the closest note freq.
    benddifference = closestfreq - inputfreq;

    //Get the difference between the closest and next closest frequencies.
    notedifference = closestfreq - nextclosestfreq;

    percentageUR = benddifference / notedifference; //Divide the above.
    percentage = (int) (percentageUR * 100); //Round it as a percentage.

    printf("=============================\n"
	   "Closest Midi Note: %d\n"
	   "Midi Note Frequency: %f\n\n"
	   "Next Midi Note: %d\n"
	   "Next Frequency: %f\n\n"
	   "Pitch Bend: "
	   , closestmidinote, closestfreq, nextclosestnote
	   , nextclosestfreq);

    if (closestfreq > inputfreq)
    {
	printf("-");
    }
    else 
    {
	printf("+");
    }

    printf("%%%d\n", percentage);

    return 0;
}
