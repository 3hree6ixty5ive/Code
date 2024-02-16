#include <stdio.h>
#include <stdlib.h>

int main() {
    ///////////////Variable initialization/////////////////
    //Input file and output file pointers
    FILE *payloadFile = NULL;
    FILE *oreFile = NULL;
    //Dimensions of storage arrays
    int rows = 1, cols = 3;
    //Global loop variables
    int i, j;

    /////////////////////////Creating the input file named payload/////////////////
    //Opening in write mode
    payloadFile = fopen("payload.txt", "w");
    //If file creation fails, exit program
    if (payloadFile == NULL) { printf("Payload file not created."); return 0;}

    //Save required data to payload file
    fprintf(payloadFile,
                   "7\n"
                         "5434 0.06\n"
                         "6182 0.05\n"
                         "5877 0.04\n"
                         "4895 0.05\n"
                         "5665 0.06\n"
                         "5164 0.03\n"
                         "5376 0.04");
    //Close input File
    fclose(payloadFile);
    /////////////////////////////////////////////////////////////////////////////

    ////////////////////File opening for input and output/////////////////////
    //Opening input file in read mode, exiting program if opening fails
    payloadFile = fopen("payload.txt", "r");
    if (payloadFile == NULL) { printf("Payload file not created."); return 0;}

    //Opening output file in write mode, exiting program if opening fails
    oreFile = fopen("ores.txt", "w");
    if (oreFile == NULL) { printf("Output file not created"); return 0;}

    //Adding initial headers/titles to the console
    printf("Payload Data:\n");
    printf("Total Mass / Grade / Ore Value\n");

    //Adding initial headers/titles to the output file
    fprintf(oreFile, "Sorted Payload Data:\n");
    fprintf(oreFile, "Total Mass / Grade / Ore Value\n");

    //Reading input file to find number of payloads, exiting if number is 0
    fscanf(payloadFile, "%d", &rows);
    if (rows == 0) { printf("No payloads in file."); return 0;}

    //Declaring main 2d storage array
    float** storage = (float**)malloc(rows * sizeof(float*));
    //Declaring secondary temp storage array allowing for sorting
    float* tempStorage = (float*)malloc(cols * sizeof(float));

    /////////////////Begin looping through all inputted payloads/////////////////////
    for (i = 0; i < rows; i++) {
        //Expand row of storage array wide enough to contain all data
        storage[i] = (float*) malloc(cols * sizeof(float));

        //Loop through input file and store the two input values in tempStorage
        for (j = 0; j < 2; ++j) {
            fscanf(payloadFile, "%f", &tempStorage[j]);
        }

        //Set the third value of tempStorage to the calculated ore value
        tempStorage[2] = tempStorage[0] * tempStorage[1] * 8500;

        //Output payload information to console
        printf("   %.0f      %.2f    $%.0f\n", tempStorage[0], tempStorage[1], tempStorage[2]);

        ///////////////Sorting function/////////////////////
        //Loop backwards through currently saved payloads in storage
        for (j = i; j > 0; j--) {
            //Check if new payload is greater than saved payload
            if (tempStorage[2] > storage[j-1][2]) {
                //If it is greater, move the saved one up a row
                storage[j][0] = storage[j-1][0];
                storage[j][1] = storage[j-1][1];
                storage[j][2] = storage[j-1][2];
            }
            //Exit once correct place is found for new payload information
            else {
                break;
            }
        }
        //Save new payload info into storage
        storage[j][0] = tempStorage[0];
        storage[j][1] = tempStorage[1];
        storage[j][2] = tempStorage[2];
    }

    //Output complete sorted payload info to output file
    for (i = 0; i < rows; i++) {
        fprintf(oreFile, "   %.0f      %.2f    $%.0f\n", storage[i][0], storage[i][1], storage[i][2]);
    }
    
    ///////////////////Close all open files, and nullify/free all pointers/////////////////////
    fclose(payloadFile);
    fclose(oreFile);
    for (i = 0; i < rows; i++) {
        free(storage[i]);
    }
    free(tempStorage);
    free(storage);
    payloadFile = NULL;
    oreFile = NULL;

    //Exit
    return 0;
}