#include <iostream>
#include <cstdlib>
#include <string>
#include "washing.h"
#include "queue.h"

using namespace std;

void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time) {
    // Array of car colors for output variety
    string car_colors[] = { "Red", "Blue", "Yellow", "Green", "White" };
    int color_count = sizeof(car_colors) / sizeof(car_colors[0]);

    // Output simulation parameters in the new format
    cout << "It takes " << wash_time << " seconds to wash a car (" << wash_time / 60 << " mins)" << endl;
    cout << "This is the arrival probability: " << arrival_prob << endl;
    cout << "The total time that the car wash is gonna be open is " << total_time << " seconds ("
        << total_time / 60 << " mins)" << endl;

    // Initialize components
    bool_source customer_source(arrival_prob);
    averager wait_times;
    washer car_washer(wash_time);
    Queue<unsigned int> customer_queue;

    // Simulation variables
    unsigned int current_time = 0;
    unsigned int customers_served = 0;

    // Introduce a random delay for the first customer's arrival
    unsigned int next_customer_time = rand() % 10 + 1; // First car arrives between 1 and 10 seconds

    for (current_time = 0; current_time < total_time; ++current_time) {
        // Stop the simulation after serving 5 cars
        if (customers_served >= 5) {
            break;
        }

        // Check if a new customer arrives at the designated arrival time
        if (current_time == next_customer_time || (current_time > next_customer_time && customer_source.query())) {
            customer_queue.enqueue(current_time);

            // Set the next customer arrival time
            next_customer_time = current_time + (rand() % 10 + 1); // Next car arrives 1-10 seconds later
        }

        // Process the next customer if the washer is free
        if (!car_washer.is_busy() && !customer_queue.is_empty()) {
            unsigned int arrival_time = customer_queue.front();
            customer_queue.dequeue();

            unsigned int wait_time = current_time - arrival_time;
            wait_times.next_number(wait_time);
            car_washer.start_washing();

            // Output car details
            string car_color = car_colors[customers_served % color_count]; // Rotate through car colors
            cout << "\n" << car_color << " Car (Car #" << (customers_served + 1) << "):" << endl;
            cout << "  Arrived at: " << arrival_time << " seconds" << endl;
            cout << "  Wait time: " << wait_time << " seconds" << endl;
            cout << "  Service completed at: " << current_time + wash_time << " seconds" << endl;

            ++customers_served;
        }

        // Simulate one second of washing
        car_washer.one_second();
    }

    // Output results
    cout << "\nSimulation Results:" << endl;
    cout << "Total customers served: " << customers_served << endl;
    if (wait_times.how_many_numbers() > 0) {
        cout << "Average waiting time: " << wait_times.average() << " seconds" << endl;
    }
    else {
        cout << "Average waiting time: N/A (no customers waited)" << endl;
    }
}

int main() {
    // Input simulation parameters
    unsigned int wash_time;
    double arrival_prob;
    unsigned int total_time;

    cout << "Enter wash time per car (seconds): ";
    cin >> wash_time;
    cout << "Enter customer arrival probability (0 to 1): ";
    cin >> arrival_prob;
    cout << "Enter total simulation time (seconds): ";
    cin >> total_time;

    // Run the simulation
    car_wash_simulate(wash_time, arrival_prob, total_time);

    return 0;
}
