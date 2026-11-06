#include <stdio.h>
#define MAX_SENSORS 100
#define MAX_HOURS 100
//function to take temperature
void inputReadings(float temp[][MAX_HOURS],int sensors,int hours)
{
    int i,j;
    //input reading sensor by sensor 
	for(i=0;i<sensors;i++)
    {
        printf("\nEnter readings for Sensor %d:\n",i + 1);
		for(j=0;j<hours;j++)
        {
            printf("Hour %d: ",j + 1);
            scanf("%f",&temp[i][j]);
        }
    }
}
void analyzeSensor(float readings[],int hours,int sensorNo,
                   float *average,float *total)
{
    int i;
    int highest,lowest;
    int critical=0,warning=0;
    int currentStreak=0,longestStreak=0;
    //initialize total,smallest and lowest readings 
	*total = 0;
    highest=readings[0];
    lowest=readings[0];
	for(i=0;i<hours;i++)
    {
        *total+=readings[i];//add each reading to total
        //highest temperature
		if(readings[i] > highest)
            highest = readings[i];
        //lowest temperature    
		if(readings[i] < lowest)
            lowest = readings[i];
        // Count readings of 40 degrees or above as critical
		if(readings[i] >= 40)
            critical++;
        // Count readings from 35 to 39 as warning
        if(readings[i] >= 35 && readings[i] <= 39)
            warning++;
         // Count consecutive readings of 35 degrees or above
        if(readings[i] >= 35)
        {
            currentStreak++;
            // Update the longest consecutive streak
			if (currentStreak > longestStreak)
                longestStreak = currentStreak;
        }
        else
        {
        	// Reset streak when temperature falls below 35
            currentStreak = 0;
        }
    }
     // Calculate average temperature
	*average = *total / hours;
	 // Display the report for the current sensor
	printf("\n----- Sensor %d Report -----\n", sensorNo);
    printf("Total temperature: %.2f\n", *total);
    printf("Average temperature: %.2f C\n", *average);
    printf("Highest temperature: %d C\n", highest);
    printf("Lowest temperature: %d C\n", lowest);
    printf("Critical readings: %d\n", critical);
    printf("Warning readings: %d\n", warning);
    printf("Longest streak at 35 C or above: %d hours\n",
           longestStreak);
}
// Function to find the sensor which have the highest average temperature
int findHighestAverageSensor(float temp[][MAX_HOURS],
                             int sensors, int hours)
{
    int i,j,highestSensor=0;
    float total,average,highestAverage=-1;
     // Calculate the average temperature of each sensor
	 for(i=0;i<sensors;i++)
    {
        total=0;
		for(j=0;j<hours;j++)
        {
            total+=temp[i][j];
        }

        average= total / hours;
        // Update the sensor number if a higher average is found
		if(average > highestAverage)
        {
            highestAverage = average;
            highestSensor = i;
        }
    }
	return highestSensor;
}
int main()
{
    float temp[MAX_SENSORS][MAX_HOURS];
    float average, total;
    int sensors, hours, i;
    int highestSensor;
    float highestTotal=0,highestAverage=0;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);

    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);
    // Validate the number of sensors and readings
	if (sensors < 1 || sensors > MAX_SENSORS ||
        hours < 1 || hours > MAX_HOURS)
    {
        printf("Invalid number of sensors or readings.\n");
        return 0;
    }
    // Call function to input all temperature readings
	inputReadings(temp, sensors, hours);
	 // Analyze and display the report for every sensor
	for(i=0;i<sensors;i++)
    {
        analyzeSensor(temp[i],hours,i + 1,&average,&total);
    }
    // Find the sensor with the highest average temperature
    highestSensor=findHighestAverageSensor(temp,sensors,hours);
    // Calculate the total temperature of the highest-average sensor
	for (i = 0; i < hours; i++)
    {
        highestTotal += temp[highestSensor][i];
    }
	highestAverage = highestTotal / hours;
	// Display the final report
	printf("\n===== Final Report =====\n");
    printf("Sensor with highest average: %d\n", highestSensor + 1);
    printf("Highest average temperature: %.2f C\n", highestAverage);
	return 0;
}


