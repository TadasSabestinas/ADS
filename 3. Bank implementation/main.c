#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "big_int.h"
#include "queue.h"
#include <time.h>

#define MAXSIZE 9999

FILE* readFile();
void assign_variables_from_file(FILE *input, int *probability, big_int **shift_time, int *analysisTime, int *total_apprentice_cashiers, int *total_experienced_cashiers, int *apprentice_min_time, int *apprentice_max_time, int *experienced_min_time, int *experienced_max_time);
void print_results_end_of_shift(double total_waiting_time, double waiting_time_counter, double total_apprentice_productivity, double ap_productivity_counter,double total_experienced_productivity, double exp_productivity_counter,int max_waiting_time, struct Queue *customerQueue);
void print_results_certain_time(double total_waiting_time, double waiting_time_counter, double total_apprentice_productivity, double ap_productivity_counter,double total_experienced_productivity, double exp_productivity_counter, int max_waiting_time, struct Queue *customerQueue);

int main()
{

    // Variable declarations
    time_t current_time;

    int total_apprentice_cashiers, apprentice_min_time, apprentice_max_time;
    int total_experienced_cashiers, experienced_min_time, experienced_max_time;
    int all_customers_during_shift = 0;
    int probability, time_cash;
    int analysisTime, timeStep = 0;
    int max_waiting_time = 0;

    big_int *one = NULL;
    big_int *shift_time = NULL;
    assign_int(&one,"1");
    FILE *input = NULL;

    // File handling
    input = readFile(input);
    assign_variables_from_file(input, &probability, &shift_time,&analysisTime, &total_apprentice_cashiers, &total_experienced_cashiers, &apprentice_max_time, &apprentice_min_time, &experienced_max_time, &experienced_min_time);

    // Probability calculations
    int certain_probability = probability / 100;
    int uncertain_probability = probability % 100;

    // Queue initialization
    struct Queue *customerQueue = createQueue(MAXSIZE);
    int *dequeuedCustomers = (int*)calloc(MAXSIZE,sizeof(int));

    // Cashier and productivity tracking variables, random time generation
    int *apprentice_cashier_desks = (int*)calloc(total_apprentice_cashiers,sizeof(int));
    int *experienced_cashier_desks = (int*)calloc(total_experienced_cashiers,sizeof(int));
    srand((unsigned) time(&current_time));
    double total_waiting_time = 0, waiting_time_counter = 0;
    double total_apprentice_productivity = 0, total_experienced_productivity = 0, exp_productivity_counter = 0, ap_productivity_counter = 0;

    // Main simulation loop
    while(shift_time -> number != 0)
    {
        int enqueuedCustomers = 0;

        if(analysisTime == timeStep)
        {
            // Perform analysis when the specified time is reached
            print_results_certain_time(total_waiting_time,waiting_time_counter,total_apprentice_productivity,ap_productivity_counter,total_experienced_productivity,exp_productivity_counter,max_waiting_time, customerQueue);
        }

        // Generate random number and enqueue customers based on probabilities
        int randomNumber = rand() % 101;

        while(enqueuedCustomers < certain_probability)
        {
            all_customers_during_shift++;
            enqueue(customerQueue,0);
            enqueuedCustomers++;
        }

        if(randomNumber <= uncertain_probability)
        {
            all_customers_during_shift++;
            enqueue(customerQueue,0);
        }

            // Process customers by apprentice and experienced cashiers
            for (int i = 0; i < total_apprentice_cashiers; ++i)
            {
                    if(apprentice_cashier_desks[i] == 0 && queue_size(customerQueue) != 0)
                    {
                        // Serve customer at an apprentice cashier
                        randomNumber = rand() % (apprentice_max_time - apprentice_min_time +1) + apprentice_min_time;
                        apprentice_cashier_desks[i] = randomNumber;

                        int max = dequeue(customerQueue);
                        total_waiting_time = total_waiting_time + max;
                        waiting_time_counter++;

                        // Find the longest waiting time
                        if(max > max_waiting_time)
                        {
                            max_waiting_time = max;
                        }
                    }
            }

            for(int i = 0; i < total_experienced_cashiers; ++i)
            {
                    if(experienced_cashier_desks[i] == 0 && queue_size(customerQueue) != 0)
                    {
                        // Serve customer at an experienced cashier
                        randomNumber = rand() % (experienced_max_time - experienced_min_time +1) + experienced_min_time;
                        experienced_cashier_desks[i] = randomNumber;

                        int max = dequeue(customerQueue);
                        total_waiting_time = total_waiting_time + max;
                        waiting_time_counter++;

                        // Find the longest waiting time
                        if(max > max_waiting_time)
                        {
                            max_waiting_time = max;
                        }

                    }
            }

        // Decrease remaining time for each apprentice desk
        double total_remaining_time_apprentice = 0;
        for(int i = 0; i <total_apprentice_cashiers; ++i)
        {
            if(apprentice_cashier_desks[i] != 0)
            {
                apprentice_cashier_desks[i]--;
                total_remaining_time_apprentice++;
            }

        }

        total_apprentice_productivity = total_apprentice_productivity + total_remaining_time_apprentice / (double)total_apprentice_cashiers;
        ap_productivity_counter++;

        // Decrease remaining time for each experienced desk
        double total_remaining_time_experienced = 0;

        for(int i = 0; i < total_experienced_cashiers; ++i)
        {
            if(experienced_cashier_desks[i] != 0)
            {
                experienced_cashier_desks[i]--;
                total_remaining_time_experienced++;
            }

        }

        total_experienced_productivity = total_experienced_productivity + total_remaining_time_experienced / (double)total_experienced_cashiers;
        exp_productivity_counter++;

        // Re-enqueue customers in the original order
        int i = 0;
        while(queue_size(customerQueue) != 0)
        {
            dequeuedCustomers[i] = dequeue(customerQueue) + 1;
            i++;
        }

        for(int j = 0; j < i; ++j)
        {
            enqueue(customerQueue, dequeuedCustomers[j]);
        }

        timeStep++;
        // Decrement remaining time
        shift_time = subtract_int(shift_time, one);
    }

    // Perform analysis at the end of the simulation
    print_results_end_of_shift(total_waiting_time,waiting_time_counter,total_apprentice_productivity,ap_productivity_counter,total_experienced_productivity,exp_productivity_counter,max_waiting_time, customerQueue);
    return 0;
}

// Function to open a file for reading
FILE* readFile()
{
    FILE* fp = NULL;
    char fileName[256];

    while (1)
    {
        printf("Enter the name of the file: ");
        scanf("%255s", fileName);

        fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            printf("Error while opening the file. Please make sure you entered the name correctly.\n");
        }
        else
        {
            printf("File opened successfully.\n");
            break;
        }
    }

    return fp;
}

// Function to read data from the file and assign values to variables
void assign_variables_from_file(FILE *input, int *probability, big_int **shift_time, int *analysisTime, int *total_apprentice_cashiers, int *total_experienced_cashiers, int *apprentice_min_time, int *apprentice_max_time, int *experienced_min_time, int *experienced_max_time)
{
    char number[3];
    char dash;
    char letter;

    fscanf(input, "%d", total_apprentice_cashiers); //apprentice cashiers
    fscanf(input, "%d", total_experienced_cashiers); //experienced cashiers

    fscanf(input, "%d%c%d", apprentice_max_time,&dash,apprentice_min_time); // Apprentice cashier time that takes to serve a customer
    fscanf(input, "%d%c%d", experienced_max_time,&dash, experienced_min_time); //Experienced cashier time that takes to serve a customer

    fscanf(input, "%d", probability); //Probability of a customer arriving at the bank during a given time interval.
    fscanf(input, "%s", number);

    assign_int(shift_time, number);

    printf("Write the time till which you want to collect the data 0 - 360 in minutes\n");
    while(1)
    {
        if(scanf("%d%c", analysisTime, &letter) !=2 || letter != '\n')
        {
            scanf("%*[^\n]");
            printf("Write the time till which you want to collect the data 0 - 360 in minutes, please.\n");
        }
        else
        {
            break;
        }
    }
}

// Functions to analyze and print collected data
void print_results_end_of_shift(double total_waiting_time, double waiting_time_counter, double total_apprentice_productivity, double ap_productivity_counter,double total_experienced_productivity, double exp_productivity_counter,int max_waiting_time, struct Queue *customerQueue)
{
        // Analysis of collected data at the end of the operating time (provided in the text file)
        printf("\n");
        printf("Collected DATA at the end of the operating time (provided in text file)\n");
        printf("\n");
        printf("Average waiting time in queue is %f min \n", total_waiting_time / waiting_time_counter);
        printf("The maximum waiting time in the line: %d min \n", max_waiting_time);
        printf("The percentage of apprentice workers' busyness: %f \n",(total_apprentice_productivity / ap_productivity_counter) * 100.0);
        printf("The percentage of experienced workers' busyness: %f \n", (total_experienced_productivity / exp_productivity_counter) * 100.0);
        printf("People waiting in line %d\n", queue_size(customerQueue));
        printf("\n");
}

void print_results_certain_time(double total_waiting_time, double waiting_time_counter, double total_apprentice_productivity, double ap_productivity_counter,double total_experienced_productivity, double exp_productivity_counter, int max_waiting_time, struct Queue *customerQueue)
{
        // Analysis of collected data from the start until the picked time (entered by the user)
        printf("\n");
        printf("Collected DATA from the start until the picked time (entered by the user)\n");
        printf("\n");
        printf("Average waiting time in queue is %f min \n", total_waiting_time / waiting_time_counter);
        printf("The maximum waiting time in the line: %d min \n", max_waiting_time);
        printf("The percentage of apprentice workers' busyness: %f \n",(total_apprentice_productivity / ap_productivity_counter) * 100.0);
        printf("The percentage of experienced workers' busyness: %f \n", (total_experienced_productivity / exp_productivity_counter) * 100.0);
        printf("People waiting in line %d\n", queue_size(customerQueue));
        printf("\n");
}
