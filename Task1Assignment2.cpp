#include<stdio.h>
int main(){
	int seats[100][100];
	int rows,seatsPerRow;
	int i,j,k;
	int available,totalAvailable=0;
	int middle,distance,row;
	int count,startSeat;
	int found=0;
	
	//input and validation of number of rows
	printf("Enter number of rows(1-100): ");
	scanf("%d",&rows);
	if(rows < 1 || rows > 100){
		printf("Invalid Rows Number\n");
	}
	//input and validation of seats per row
	printf("Enter number of seats per row(1-100): ");
	scanf("%d",&seatsPerRow);
	if(seatsPerRow<1 || seatsPerRow>100){
		printf("Invalid Seats Number\n");
	}
	//input seating status:1 is booked and 0 is available
	printf("Enter Seating Status(0=Available,1=Booked): ");
	for(i=0;i<rows;i++){
		for(j=0;j<seatsPerRow;j++){
			do{
				printf("Row %d,Seat %d:",i,j);
				scanf("%d",&seats[i][j]);
				if(seats[i][j]!=0 && seats[i][j]!=1){
					printf("Enter only 0 and 1\n");
				}
			}while(seats[i][j]!=0 && seats[i][j]!=1);
		}
	}
	//display the initial seating arrangement
	printf("Seating Arrangement\n");
	for(j=0;j<seatsPerRow;j++){
		printf("%3d",j);
	}
	printf("\n");
	for(i=0;i<rows;i++){
		printf("Row %d",i);
		for(j=0;j<seatsPerRow;j++){
			//display underscore for available seats and X for booked seats
			if(seats==0){
				printf("%3c",'_');
			}
			else{
				printf("%3c",'X');
			}
			printf("\n");
	   }
	}
	//count available seats in each row and in entire hall
	printf("Seat Availability Report\n");
	for(i=0;i<rows;i++){
		available=0;
		for(j=0;j<seatsPerRow;j++){
			if(seats[i][j]==0){
				available++;
			}
		}
		printf("Row %d:%d available seats\n", i, available);
        totalAvailable += available;
	}
	printf("Total Available seats in the Hall=%d\n",totalAvailable);
	printf("Enter number of customers: ");
	scanf("%d",&k);
	if(k<=0 || k>seatsPerRow){
		printf("Invalid Group Size");
	}
	//find the middle row from which the search will begin
	middle=rows/2;
	//search for consecutive available seats,starting from middle  row
	for(distance=0;distance<rows && !found;distance++){
		for(i=0;i<2 && !found;i++){
			if(i==0){
				row=middle-distance;
			}
			else{
				row=middle+distance;
			}
			if(distance==0 && i==1){
				continue;
			}
			if(row<0 || row>=rows){
				continue;
			}
			count=0;
			//search for consecutive available seats in the selected row
			 for(j=0;j<seatsPerRow;j++){
			 	if(seats[row][j]==0){
			 		count++;
			 		//check whether required number of consecutive seat is found
			 		if(count==k){
			 			startSeat=j-k+1;
			 			found=1;
			 			break;
					 }
				 }
				 else{
				 	count=0;
				 }
			 }
		}
	}
	//allocate seat if suitable block is found 
	if(found){
		printf("\nBooking Successful");
		printf("Allocated Row:%d\n",row);
		printf("Allocated Seat Numbers: ");
		for(j=startSeat;j<startSeat+k;j++){
			printf("%d",j);
			seats[row][j]=1;//mark allocated seat as booked 
		}
		printf("\n");
		totalAvailable -= k;
		printf("Updated Seating Arrangement\n");
		for(j=0;j<seatsPerRow;j++){
			printf("%3d",j);
		}
		printf("\n");
		for(i=0;i<rows;i++){
			printf("Row %d",i);
			for(j=0;j<seatsPerRow;j++){
				if(seats[i][j]==0){
					printf("%3c",'_');
				}
				else{
					printf("%3c",'X');
				}
			}
			printf("\n");
		}
		printf("Remaining available seats:%d\n",totalAvailable);
	}
	else{
		//display an unsuccessful msg if no seats are found 
		printf("\nBooking Unsuccessful\n");
        printf("No row contains %d consecutive available seats\n", k);
        printf("The seating plan remains unchanged\n");
	}
	return 0;
}
