
/*
 *
 * Simulation of Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include "simlib.h"

/*******************************************************************************/

/*
 * Simulation Parameters
 */

//#define RANDOM_SEED 400122166

#define NUMBER_TO_SERVE 50e6

#define MAX_QUEUE_SIZE 10

//#define SERVICE_TIME 30
//#define ARRIVAL_RATE 0.1

#define BLIP_RATE 10000

/*******************************************************************************/

/*
 * main() uses various simulation parameters and creates a clock variable to
 * simulate real time. A loop repeatedly determines if the next event to occur
 * is a customer arrival or customer departure. In either case the state of the
 * system is updated and statistics are collected before the next
 * iteration. When it finally reaches NUMBER_TO_SERVE customers, the program
 * outputs some statistics such as mean delay.
 */

int main()
{
  
  int random_nums[160];
  double arrival_rates[16] = {0.20, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95}; 
  //double arrival_rates[6] =  {0.005, 0.01, 0.015, 0.020, 0.025, 0.030};
  
  for(int j=0; j<160; j++){

    random_nums[j] = rand()%((999999+1)-100000); // Generate 50 random numbers to use as RANDOM_SEED values
    //printf("%d\n",random_nums[j]);

  }

  for(int k=0; k<16; k++){
    //for(int k=0; k<6; k++){
      
      double ARRIVAL_RATE = arrival_rates[k];
      
	    //double ARRIVAL_RATE = 0.95 +0.005*k; // Change k<9 to approach asymptote

      //double ARRIVAL_RATE = 1.1; //Q3 
      double sum =0;
      double average =0;
  
      for(int i=0+10*k; i<10+10*k; i++) { // Q2 stuff
      
      //for(int i=0+1; i<10; i++) {  // Q2 stuff

      //for(int i=0; i<10; i++) {  

        
        double clock = 0; /* Clock keeps track of simulation time. */

        /* System state variables. */
        int number_in_system = 0;
        double next_arrival_time = 0;
        double next_departure_time = 0;

        /* Data collection variables. */
        long int total_served = 0;
        long int total_arrived = 0;

        double total_busy_time = 0;
        double integral_of_n = 0;
        double last_event_time = 0;

        int RANDOM_SEED = random_nums[i];
        int rejected = 0;
        
        
        

        printf("Pass #%d \n",i+1); // List the pass # in terminal for debugging. 
        
        /* Set the seed of the random number generator. */
        random_generator_initialize(RANDOM_SEED);
        double SERVICE_TIME = exponential_generator(1.0);

        /* Process customers until we are finished. */
        while (total_served < NUMBER_TO_SERVE) {

          /* Test if the next event is a customer arrival or departure. */
        if((number_in_system == 0 || next_arrival_time < next_departure_time){

          /*
            * A new arrival is occurring.
            */

          if(number_in_system<=MAX_QUEUE_SIZE){
            clock = next_arrival_time;
            next_arrival_time = clock + exponential_generator((double) 1/ARRIVAL_RATE);

            /* Update our statistics. */
            integral_of_n += number_in_system * (clock - last_event_time);
            last_event_time = clock;

            number_in_system++;
            total_arrived++;

            /* If this customer has arrived to an empty system, start its
          service right away. */
            if(number_in_system == 1) next_departure_time = clock + SERVICE_TIME;

        } else {

          rejected++;

        }

        } else {

          /*
            * A customer departure is occuring. 
            */

          clock = next_departure_time;

          /* Update our statistics. */
          integral_of_n += number_in_system * (clock - last_event_time);
          last_event_time = clock;

          number_in_system--;
          total_served++;
          total_busy_time += SERVICE_TIME;

          /* 
            * If there are other customers waiting, start one in service
            * right away.
            */

          if(number_in_system > 0) next_departure_time = clock + SERVICE_TIME;

          /* 
            * Every so often, print an activity message to show we are active. 
            */

          if (total_served % BLIP_RATE == 0)
            printf("Customers served = %ld (Total arrived = %ld)\r",
              total_served, total_arrived);
        }

        }

        /* Output final results. */
        
        /*printf("\nUtilization = %f\n", total_busy_time/clock);
        printf("Fraction served = %f\n", (double) total_served/total_arrived);
        printf("Mean number in system = %f\n", integral_of_n/clock);*/
        printf("Mean delay = %f\n", integral_of_n/total_served);
        
        sum = sum + integral_of_n/total_served;

        /* Halt the program before exiting. */
        /*printf("Hit Enter to finish ... \n");
        getchar();*/ 

        

      }
      
      average = sum/10;
    
      printf("***** Average mean delay for %lf = %lf *****\n",ARRIVAL_RATE,average);
      
  }
  
  printf("Hit Enter to finish ... \n");
  getchar();
  
  return 0;
}






