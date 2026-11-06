#include<stdio.h>
//function to calculate sum of all proper divisors of a number 
int sumproperdivisors(int num){
	int i,sum=0;
	//check all numbers from 1 to half of the given number 
	for(i=1;i<=num/2;i++){
		if(num%i==0){
			sum=sum+i;//add the divisor to the sum
		}
	}
	return sum;
}
int main(){
	int n,i;
	int sum1,sum2;
	int paircount=0;
	printf("Enter the limit: ");
	scanf("%d",&n);
	if(n<1){
		printf("Please Enter a positive number");
		return 0;
	}
	printf("\nAmicable pairs up to %d:\n",n);
	//check every number from 2 up to the given limit
	for(i=2;i<=n;i++){
		sum1=sumproperdivisors(i);//calculate the sum of  divisors of i
		if(sum1>i && sum1<=n){
			sum2=sumproperdivisors(sum1);//calculate divisor sum of second number 
			//two numbers are amicable if their divisor sum equal each other 
			if(sum2==i){
				printf("(%d,%d)\n",i,sum1);
				paircount++;//increase the count of amicable pair 
			}
		}
	}
	if(paircount==0){
		printf("\nNo Amicable pairs found");
	}
	else{
		printf("Total Amicable pairs found are %d\n",paircount);
	}
}
