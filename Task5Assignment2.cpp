#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 5
#define MAX_BORROWED 3

// Function to display the main menu of the library system
void displayMenu()
{
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT =====\n");
    printf("1.Register Member\n");
    printf("2.Display Available Books\n");
    printf("3.Borrow a Book\n");
    printf("4.Return a Book\n");
    printf("5.Display Member Record\n");
    printf("6.Exit\n");
    printf("Enter your choice: ");
}
// Function to register a new library member
void registerMember(char name[],int *studentID,int *memberType)
{
    int type;
	printf("\nEnter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do
    {
    	// Validate membership type: 1 for Student and 2 for Faculty
        printf("Enter membership type(1=Student,2=Faculty): ");
        scanf("%d", &type);

        if (type != 1 && type != 2)
            printf("Invalid membership type. Try again.\n");

    } while (type != 1 && type != 2);
	*memberType=type; //Store membership type using pointer
	printf("Member registered successfully.\n");
	// Display borrowing period according to membership type
	if (*memberType==1)
        printf("Allowed borrowing period: 14 days\n");
    else
        printf("Allowed borrowing period: 30 days\n");
}
// Function to display all books and their available copies
void displayBooks(int bookIDs[],char bookTitles[][50],
                  int availableCopies[],int totalBooks)
{
    int i;
	printf("\n%-10s %-30s %-10s\n",
           "Book ID", "Book Title", "Copies");
    // Display the ID, title and available copies of each book
	for(i=0;i<totalBooks;i++)
    {
        printf("%-10d %-30s %-10d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}
// Function to borrow a book
void borrowBook(int bookIDs[],char bookTitles[][50],
                int availableCopies[],int totalBooks,
                int borrowedBookIDs[],int *borrowedCount,
                int memberType)
{
    int id,i,position=-1,days,j;
     //Check if the member has already borrowed the maximum number of books
	 if(*borrowedCount>=MAX_BORROWED)
    {
        printf("You cannot borrow more than 3 books at a time\n");
        return;
    }

    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    // Search for the entered book ID in the inventory
    for(i=0;i<totalBooks;i++)
    {
        if(bookIDs[i]==id)
        {
            position = i;
            break;
        }
    }
     // Check whether the entered book ID exists
	if(position == -1)
    {
        printf("Invalid book ID\n");
        return;
    }
     // Check whether the book has available copies
	if(availableCopies[position] <= 0)
    {
        printf("This book is currently unavailable.\n");
        return;
    }
	printf("Enter intended borrowing days: ");
    scanf("%d",&days);
    // Validate the number of borrowing days
	if(days <= 0)
    {
        printf("Number of days must be positive.\n");
        return;
    }
	 // Check whether the member has already borrowed this book
	for(j=0;j<*borrowedCount;j++)
    {
        if(borrowedBookIDs[j]==id)
        {
            printf("You have already borrowed this book\n");
            return;
        }
    }
    // Store the borrowed book ID and update borrowed book count
	borrowedBookIDs[*borrowedCount]=id;
    (*borrowedCount)++;
    // Decrease the available copies after successful borrowing
    availableCopies[position]--;
	printf("Book borrowed successfully: %s\n", bookTitles[position]);
	// Display borrowing period according to membership type
	if(memberType==1)
        printf("Student borrowing limit: 14 days.\n");
    else
        printf("Faculty borrowing limit: 30 days.\n");
}
// Function to return a book and calculate late fine
float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id,days,allowedDays,extraDays;
    int i,j,position = -1,borrowedPosition=-1;
    char code[30];
    float fine=0,payable=0;
	printf("Enter book ID to return: ");
    scanf("%d",&id);
	// Search for the book ID in the inventory
	for(i=0;i<totalBooks;i++)
    {
        if(bookIDs[i]==id)
        {
            position = i;
            break;
        }
    }
    // Check whether the entered book ID exists
	if(position==-1)
    {
        printf("Invalid book ID.\n");
        return 0;
    }
    // Search for the book in the member's borrowed book list
	for(i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            borrowedPosition = i;
            break;
        }
    }
    // Do not allow return if the member has not borrowed the book
	if(borrowedPosition == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }
	printf("Enter actual number of days the book was kept: ");
    scanf("%d", &days);
    // Validate the actual number of days
	if(days<=0)
    {
        printf("Number of days must be positive. Return not processed.\n");
        return 0;
    }
    // Set the allowed borrowing period according to membership type
	if(memberType==1)
        allowedDays = 14;
    else
        allowedDays = 30;
         // Calculate extra days beyond the allowed borrowing period
		extraDays=days-allowedDays;

    if(extraDays > 0)
    {
    	 // Calculate late fine according to membership type
        if (memberType == 1)
            fine = extraDays * 20.0;
        else
            fine = extraDays * 10.0;

        printf("Late fine before waiver: Rs. %.2f\n", fine);
        
        // Ask for membership code to apply 50% fine waiver
		printf("Enter membership code for 50%% waiver: ");
        scanf("%29s", code);
        
        // Compare entered code with the correct membership code
		if (strcmp(code, "LIB2026") == 0)
        {
            payable = fine * 0.5;
            printf("Correct code. 50%% waiver applied.\n");
        }
        else
        {
            payable = fine;
            printf("Incorrect code. No waiver applied.\n");
        }
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }
     // Update the total fine before waivers
	*totalFine += fine;
	
	 // Remove the returned book ID from the borrowed book list
    for(j=borrowedPosition;j<*borrowedCount-1;j++)
    {
        borrowedBookIDs[j]=borrowedBookIDs[j + 1];
    }

    (*borrowedCount)--; // Decrease the borrowed book count
    // Increase available copies after the book is returned
    availableCopies[position]++;

    printf("Book returned successfully.\n");
    printf("Fine payable for this return: Rs. %.2f\n", payable);

    return payable;
}
// Function to display the complete member record
void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;
	printf("\n===== MEMBER RECORD =====\n");
	// Check whether a member has been registered
	if (studentID == -1)
    {
        printf("Please register a member first.\n");
        return;
    }
     // Display member information
	printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType==1)
        printf("Membership Type: Student\n");
    else
        printf("Membership Type: Faculty\n");
        
    // Display currently borrowed book IDs
	printf("Currently borrowed book IDs: ");

    if(borrowedCount==0)
    {
        printf("None");
    }
    else
    {
        for(i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    // Display total fine before and after waivers
	printf("\nTotal fine before waivers: Rs. %.2f\n", totalFine);
    printf("Final fine payable after waivers: Rs. %.2f\n",
           fineAfterWaiver);
}
int main()
{
	// Initialize book IDs, titles and available copies
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104, 105};
	char bookTitles[MAX_BOOKS][50] = {
        "Programming in C",
        "Data Structures",
        "Artificial Intelligence",
        "Computer Networks",
        "Database Systems"
    };
	int availableCopies[MAX_BOOKS] = {3, 4, 2, 3, 5};
    int borrowedBookIDs[MAX_BORROWED];
    
     // Initialize member information and borrowing count
    char name[50] = "";
    int studentID = -1;
    int memberType = 0;
    int borrowedCount = 0;
    int choice, registered = 0;

    float totalFine = 0;
    float fineAfterWaiver = 0;
    float currentFine;

    // Repeat the menu until the user chooses Exit
    do
    {
        displayMenu();
        scanf("%d", &choice);

        // Perform the operation according to the user's choice
		switch (choice)
        {
            case 1:
            	// Register a member only if no member is already registered
                if (registered)
                {
                    printf("A member is already registered.\n");
                }
                else
                {
                    registerMember(name, &studentID, &memberType);
                    registered = 1;
                }
                break;

            case 2:
            	// Display all available books
                displayBooks(bookIDs, bookTitles,
                             availableCopies, MAX_BOOKS);
                break;

            case 3:
            	// A member must register before borrowing a book
                if (!registered)
                {
                    printf("Please register a member first.\n");
                }
                else
                {
                    borrowBook(bookIDs, bookTitles,
                               availableCopies, MAX_BOOKS,
                               borrowedBookIDs, &borrowedCount,
                               memberType);
                }
                break;

            case 4:
            	// A member must register before returning a book
                if (!registered)
                {
                    printf("Please register a member first.\n");
                }
                else
                {
                	// Calculate fine and update total fine information
                    currentFine = returnBook(
                        bookIDs, availableCopies, MAX_BOOKS,
                        borrowedBookIDs, &borrowedCount,
                        memberType, &totalFine
                    );

                    fineAfterWaiver += currentFine;
                }
                break;

            case 5:
            	 // Display the registered member's complete record
                displayMemberRecord(name, studentID, memberType,
                                    borrowedBookIDs, borrowedCount,
                                    totalFine, fineAfterWaiver);
                break;

            case 6:
            	// Exit the library management system
                printf("Exiting library system. Goodbye!\n");
                break;

            default:
                printf("Invalid menu choice. Please try again.\n");
        }

    } while (choice != 6);
	return 0;
}


