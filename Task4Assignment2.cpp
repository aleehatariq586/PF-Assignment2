#include<stdio.h>
// Function to input and validate the number of festival days
int getvaliddays(){
	int days;
	do{
		printf("Enter number of festival days(1-7): ");
		scanf("%d",&days);
		// Repeat input if days are not between 1 and 7
		if(days<1 || days>7){
			printf("\nInvalid number of days");
		}
	}while(days<1 || days>7);
	return days;
}
// Function to calculate total sales for one day
float calculatedailysales(int daynumber){
	int orders,i;
	float amount,total=0;
	float highestorder=0;
	float average;
	// Input the number of orders for the current day
	printf("\nDay %d-Number of orders",daynumber);
	scanf("%d",&orders);
	for(i=1;i<=orders;i++){
		do{
			printf("Enter amount for order %d: ",i);
			scanf("%f",&amount);
			// Validate that the order amount is positive
			if(amount<=0){
				printf("Invalid amount");
			}
		}while(amount<=0);
		total+=amount;// Add order amount to daily total
		// Find the highest individual order amount
		if(amount>highestorder){
			highestorder=amount;
		}
	}
	// Calculate average order amount
	average=total/orders;
	// Display daily sales details
	printf("Total sales:Rs.%.2f\n",total);
    printf("Average order amount:Rs.%.2f\n",average);
    printf("Highest order amount:Rs.%.2f\n",highestorder);
	return total;
}
// Function to find the day having the highest sales
int findhighestsalesday(float dailysales[],int numberofdays){
	int i,highestday=1;
	float highestsales=dailysales[0];
	// Compare daily sales to find the highest
	for(i=1;i<numberofdays;i++){
		if(dailysales[i]>highestsales){
			highestsales=dailysales[i];
			highestsales=i+1;
		}
	}
	return highestday;
}
// Function to display a bar chart of daily sales
void displaybarchart(float dailysales[],int numberofdays){
	int i,j;
	printf("\n===Daily Sales  Bar Chart===\n");
	for(i=0;i<numberofdays;i++){
		printf("Day %d: ",i+1);
		// Print one star for every complete Rs.100 in sales
		for(j=1;j<=(int)(dailysales[i]/100);j++)
        {
            printf("*");
        }
        printf("\n");
	}
}
int main(){
	int days,i,highestday;
	float dailysales[7];
	float totalfestivalsales=0;
	// Get the valid number of festival days
	days=getvaliddays();
	// Calculate and store sales for each day
	for(i=0;i<days;i++){
		dailysales[i]=calculatedailysales(i+1);
		totalfestivalsales+=dailysales[i]; // Add daily sales to festival total
	}
	// Find the day with the highest sales
	highestday=findhighestsalesday(dailysales,days);
	// Display the final festival sales summary
	printf("\n===== Festival Sales Summary =====\n");
    printf("Total festival sales:Rs.%.2f\n",totalfestivalsales);
    printf("Day with highest sales:Day %d\n",highestday);
    printf("Highest daily sales:Rs.%.2f\n",dailysales[highestday-1]);
    // Display the daily sales bar chart
	displaybarchart(dailysales,days);
	return 0;
}

