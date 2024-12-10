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
// Prints the name of a car Brand by calling it from brands array.
void printBrand(int x) {
    for(int i = 0; brands[x][i] != '\0'; i++)
        printf("%c", brands[x][i]);
}
// Prints the Types of cars for the brands by calling it from types array.
void printType(int x) {
    for(int i = 0; types[x][i] != '\0'; i++)
        printf("%c", types[x][i]);
}
// Sums of all the car types for a specific brand on the given day.
int sumTypes(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand) {
    int sum = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++)
        sum += cube[day][brand][i];
    return sum;
}
// Sums of all the car brands on the given day.
int sumBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int sum = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        sum += sumTypes(cube, day, i);
    return sum;
}
// Prints all the sales data for a specific brand over the over all the days.
void showData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int Brand , int Days) {
    for (int i = 0; i < Days; i++) {
        printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d"
               "\n", i+1,cube[i][Brand][0],cube[i][Brand][1],cube[i][Brand][2],cube[i][Brand][3]);
    }
}
// Calculates the Average Delta Metric in sales between consecutive days for a brand.
void growthOfBrand (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brand) {
    int temp;
    float Avg = 0;
    for(int i = 0; i < days-1; i++) {
        temp = sumTypes(cube, i+1, brand);
        Avg += temp-sumTypes(cube,i,brand);
    }
    //here don't count the first day.
    Avg = (float)Avg/(days-1);
    printf("Brand: ");
    printBrand(brand);
    printf(", Average Delta: %.6f\n",Avg);
}
// Finds the brand with the highest sales for a given day
int bestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int TempNumber = 0;
    int max = 0;
    //Track the best type.
    int bestBrand = -1;
    // It goes over all brands and determine the maximum.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        // Get the sales for the brand in the given day.
        TempNumber = sumTypes(cube, day, i);
        if (TempNumber > max) {
            max = TempNumber;
            // Store the type index of the best-selling type.
            bestBrand =i;
        }
    }
    return bestBrand;
}
// Finds the type with the best sales in specific brand for a given day.
int bestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand) {
    int TempNumber = 0;
    int max = 0;
    // Track the best type index .
    int bestType = -1;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        // Get the sales for the type on the given brand and day.
        TempNumber = cube[day][brand][i];
        if (TempNumber > max) {
            max = TempNumber;
            // Store the type index of the best-selling type
            bestType = i;
        }
    }
    return bestType;
}
// Search for the brands without data and print their names.
void missingData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int Day) {
    printf("No data for brands ");
    // Track if any brands have missing data
    int foundMissing = 0;
    int noData = -1;
    // Loop over all brands to check for missing data
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        int missingData = 0;
        // Check if any type of data for this brand is missing
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[Day][i][j] == noData) {
                missingData = 1;
                break;
            }
        }
        // If there's missing data, print the brand name
        if (missingData) {
            printBrand(i);
            printf(" ");
            foundMissing = 1;
        }
    }
    // If there was any missing data, prompt the user
    if (foundMissing)
        printf("\nPlease complete the data\n");
}
// Asks the user to insert data for a specific brand.
int enterData(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int Brand, SUV, Sedan, Coupe, GT;
    int noData = -1;
    scanf("%d", &Brand);
    if ( Brand < 0 || Brand >= NUM_OF_BRANDS || (arr[day][Brand][0] != noData)) {
        printf("This brand is not valid\n");
        return 0;
    }
    scanf("%d %d %d %d", &SUV, &Sedan, &Coupe, &GT);
    // Check that the brand the user insert exist if not then return 0.
        arr[day][Brand][0] = SUV;
        arr[day][Brand][1] = Sedan;
        arr[day][Brand][2] = Coupe;
        arr[day][Brand][3] = GT;
        return 1;
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
            case addAll: {
                // Counter for the num brands that the user entered.
                int counter = 1;
                int enteredData =0;
                int validBrand = 0;
                // The loop will continue until the user insert data for the 5 brands.
                while (counter <= NUM_OF_BRANDS) {
                    missingData(cube, days);
                    // Check if the user entered a valid brand.
                    enteredData = enterData(cube,days);
                    if (enteredData != validBrand)
                        counter++;
                }
                days++;
                break;
            }
            // Provide Daily Stats.
            case stats: {
                int Day;
                int firstDay = 0;
                // Prompt the user to enter a day to analyze, and validate the day that the user entered is in range of days.
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &Day);
                    if (Day <= firstDay || Day >= days+1)
                        printf("Please enter a valid day.\n");
                } while (Day <= firstDay || Day >= days+1);
                // in the code days are between 0-364 but for the user 1-365 because of that I write Days-1.
                // Initialize the variable Best_Brand with BestBrand in the given day.
                int Best_Brand = bestBrand(cube, Day-1);
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
                // because the days for the user from 1-365 and in the code from 0-364 I subtracted the int Day by 1.
                printf("The sales total was %d\n", sumBrands(cube,Day-1));
                printf("The best sold brand with %d sales was ",sumTypes(cube,Day-1,Best_Brand));
                printBrand(Best_Brand);
                printf("\nThe best sold type with %d sales was ", temp );
                printType(Best_Type);
                printf("\n");
                break;
            }
            // Print The Entire Dataset
            case print: {
                printf("*****************************************\n");
                // Loop that go through all the brands and display their data in all the days.
                for (int i = 0; i < NUM_OF_BRANDS ;i++) {
                    printf("\nSales for ");
                    printBrand(i);
                    printf(":\n");
                    showData(cube,i,days);
                }
                printf("\n*****************************************\n");
                break;
            }
            //Provide Overall (simple) Insights.
            case insights: {
                int temp1 = 0;
                int ProfitableBrand = 0;
                int ProfitableType = 0;
                // A loop that go through all the brands and save the index of the most profitable brand overall.
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int temp2 = 0;
                    for (int j = 0; j < days; j++)
                        temp2 += sumTypes(cube,j,i);
                    // check which brand has the most sales overall.
                    if(temp2 >= temp1 ) {
                        temp1 = temp2;
                        ProfitableBrand = i;
                    }
                }
                int temp3 = 0;
                //A loop that go through all the types for the 5 brands and save the index of the most profitable type over all.
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    int temp4 = 0;
                    // Sum a specific type across all the 5 brands in all the days.
                    for (int j = 0; j < days; j++) {
                        for (int k = 0; k < NUM_OF_BRANDS; k++) {
                            temp4 += cube[j][k][i];
                        }
                    }
                    // check which type with the most sales overall.
                    if (temp4 >= temp3) {
                        temp3 = temp4;
                        ProfitableType = i;
                    }
                }
                int sum = 0;
                int ProfitableDay = 0;
                // A loop for that find the day with the most sales for the 5 brands.
                for (int j = 0; j < days; j++) {
                    int temp = sumBrands(cube,j);
                    if (sum < temp) {
                        sum = temp;
                        ProfitableDay = j;
                    }
                }
                printf("The best-selling brand overall is ");
                printBrand(ProfitableBrand);
                printf(": %d$\n",temp1);
                printf("The best-selling type of car is ");
                printType(ProfitableType);
                printf(": %d$\n",temp3);
                // because the user see the days from 1-365 I added 1 to the ProfitableDay.
                printf("The most profitable day was day number %d: %d$\n",ProfitableDay+1 ,sum);
                break;
            }
            // Provide Average Delta Metrics
            case deltas: {
                // A loop that call a function that return that Average Delta Metrics for each brand.
                for (int i = 0; i < NUM_OF_BRANDS; i++)
                    growthOfBrand(cube,days,i);
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