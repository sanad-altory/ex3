/******************
Name:Sanad Altory
ID:214633703
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
// Prints the name of a car Brand by calling it from brand array.
void PrintBrand(int x) {
    for(int i = 0; i < brands[x][i] != '\0'; i++)
        printf("%c", brands[x][i]);
    //printf(" ");
}
// Prints the Types of cars for the brands by calling it from types array.
void PrintType(int x) {
    for(int i = 0; i < types[x][i] != '\0'; i++)
        printf("%c", types[x][i]);
    //printf(" ");
}
// Sums of all the car types for a specific brand on the given day.
int SumTypes(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand) {
    int sum = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++)
        sum += cube[day][brand][i];
    return sum;
}
// Sums of all the car brands on the given day.
int SumBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int sum = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        sum += SumTypes(cube, day, i);
    return sum;
}
// Prints all the sales data for a specific brand over the over all the days.
void AllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int Brand , int Days) {
    for (int i = 0; i < Days; i++) {
        printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", i+1,cube[i][Brand][0],cube[i][Brand][1],cube[i][Brand][2],cube[i][Brand][3]);
    }
}
// Calculates the Average Delta Metric in sales between consecutive days for a brand.
void Avg_Delta_Metric (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brand) {
    int temp;
    float Avg = 0;
    for(int i = 0; i < days-1; i++) {
        temp = SumTypes(cube, i+1, brand);
        if(SumTypes(cube,i,brand) < temp)
            Avg += temp-SumTypes(cube,i,brand);
        else if (SumTypes(cube,i,brand) > temp)
            Avg += temp-SumTypes(cube,i,brand);
    }
    //here don't count the first day.
    Avg = (float)Avg/(days-1);
    printf("Brand: ");
    PrintBrand(brand);
    printf(", Average Delta: %.6f\n",Avg);
}
// Finds the brand with the highest sales for a given day
int BestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int TempNumber = 0;
    int max = 0;
    int bestBrand = -1;//Track the best type.
    // It goes over all brands and determine the maximum.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        TempNumber = SumTypes(cube, day, i);// Get the sales for the brand in the given day.
        if (TempNumber > max) {
            max = TempNumber;
            bestBrand =i;// Store the type index of the best-selling type.
        }
    }
    return bestBrand;
}
// Finds the type with the best sales in specific brand for a given day.
int BestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand) {
    int TempNumber = 0;
    int max = 0;
    int bestType = -1; // Track the best type index .
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        TempNumber = cube[day][brand][i]; // Get the sales for the type on the given brand and day
        if (TempNumber > max) {
            max = TempNumber;
            bestType = i; // Store the type index of the best-selling type
        }
    }
    return bestType;
}
// Search for the brands without data and print their names.
void MissingData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int Day) {
    printf("No data for brands ");
    int foundMissing = 0; // Flag to track if any brands have missing data

    // Loop over all brands to check for missing data
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        int MissingData = 0;
        // Check if any type of data for this brand is missing
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[Day][i][j] == -1) {
                MissingData = 1;
                break;
            }
        }
        // If there's missing data, print the brand name
        if (MissingData) {
            PrintBrand(i);
            printf(" ");
            foundMissing = 1;
        }
    }
    // If there was any missing data, prompt the user
    if (foundMissing)
        printf("\nPlease complete the data\n");
}
// Asks the user to insert data for a specific brand.
int AddOne(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int Brand, SUV, Sedan, Coupe, GT;
    scanf("%d %d %d %d %d", &Brand, &SUV, &Sedan, &Coupe, &GT);
    // Check that the brand the user insert exist if not then return 0.
    if (Brand < 0 || Brand >= NUM_OF_BRANDS) {
        printf("This brand is not valid\n");
        //That the user didn't insert a valid brand.
        return 0;
    } else {
        arr[day][Brand][0] = SUV;
        arr[day][Brand][1] = Sedan;
        arr[day][Brand][2] = Coupe;
        arr[day][Brand][3] = GT;
        return 1;
    }
}

void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
        "1.Enter Daily Data For A Brand\n"
        "2.Populate A Day Of Sales For All Brands\n"
        "3.Provide Daily Stats\n"
        "4.Print All Data\n"
        "5.Provide Overall (simple) Insights\n"
        "6.Provide Average Delta Metrics\n"
        "7.exit\n");
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days = 0;
    // Set all the indexes in array cube equal to -1.
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
    int choice;
    printMenu();
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
            case addOne: {
                //...
                break;
            }
            // Populate A Day Of Sales For All Brands.
            case 2: {
                // Counter for the num brands that the user entered.
                int counter = 1;
                // The loop will continue until the user insert data for the 5 brands.
                while (counter <= NUM_OF_BRANDS) {
                    MissingData(cube, days);
                    // Check if the user entered a valid brand.
                    if (AddOne(cube, days) != 0)
                        counter++;
                }
                days++;
                break;
            }
            // Provide Daily Stats.
            case 3: {
                int Day;
                // Prompt the user do enter a day to analyze, and validate the day that the user entered is in range of days.
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &Day);
                    if (Day <= 0 || Day >= days+1)
                        printf("Please enter a valid day.\n");
                } while (Day <= 0 || Day >= days+1);
                // in the code days are between 0-364 but for the user 1-365 because of that we write Days-1.
                // Initialize the variable Best_Brand with BestBrand in the given day.
                int Best_Brand = BestBrand(cube, Day-1);
                int Best_Type = 0;
                int temp = 0;
                // Determine the best-selling type for the given day by summing sales across brands.
                for(int i = 0; i < NUM_OF_TYPES; i++) {
                    int sum = 0;
                    for (int j = 0; j < NUM_OF_BRANDS; j++)
                        sum += cube[Day-1][j][i];
                    if (temp < sum) {
                        temp = sum;
                        Best_Type = i;
                    }
                }
                printf("In day number %d:\n", Day);
                printf("The sales total was %d\n", SumBrands(cube,Day-1));
                printf("The best sold brand with %d sales was ",SumTypes(cube,Day-1,Best_Brand));
                PrintBrand(Best_Brand);
                printf("\nThe best sold type with %d sales was ", temp );
                PrintType(Best_Type);
                printf("\n");
                break;
            }
            case 4: {
                printf("*****************************************\n");
                for (int i = 0; i < NUM_OF_BRANDS ;i++) {
                    printf("Sales for ");
                    PrintBrand(i);
                    printf(":\n");
                    AllData(cube,i,days);
                }
                printf("*****************************************\n");
                break;
            }
            case 5: {
                int sum2 = 0;
                int Profitable_Brand = 0;
                int Profitable_Type = 0;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int sum1 = 0;
                    for (int j = 0; j < days; j++)
                        sum1 += SumTypes(cube,j,i);
                    if(sum1 >= sum2 ) {
                        sum2 = sum1;
                        Profitable_Brand = i;
                    }
                }
                int sum4 = 0;
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    int sum3 = 0;
                    for (int j = 0; j < days; j++) {
                        for (int k = 0; k < NUM_OF_BRANDS; k++) {
                            sum3 += cube[j][k][i];
                        }
                    }
                    if (sum3 >= sum4) {
                        sum4 = sum3;
                        Profitable_Type = i;
                    }
                }
                int sum = 0;
                int index = 0;
                for (int j = 0; j < days; j++) {
                    int temp = SumBrands(cube,j);
                    if (sum < temp) {
                        sum = temp;
                        index = j;
                    }
                }
                printf("The best-selling brand overall is ");
                PrintBrand(Profitable_Brand);
                printf(": %d$\n",sum2);
                printf("The best-selling type of car is ");
                PrintType(Profitable_Type);
                printf(": %d$\n",sum4);
                printf("The most profitable day was day number %d: %d$\n",index+1 ,sum);
                break;
            }
            case 6: {
                for (int i = 0; i < NUM_OF_BRANDS; i++)
                    Avg_Delta_Metric(cube,days,i);
                break;
            }
            default: {
                printf("Invalid input\n");
                break;
            }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}