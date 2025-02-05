#ifndef WASHING_H
#define WASHING_H

#include <cstdlib>
#include <stdexcept>

// Class to simulate customer arrival
class bool_source {
public:
    // Constructor
    bool_source(double p = 0.5) {
        if (p < 0 || p > 1) {
            throw std::invalid_argument("Probability must be between 0 and 1.");
        }
        probability = p;
    }

    // Returns true based on the probability
    bool query() const {
        return (rand() / (RAND_MAX + 1.0)) < probability;
    }

private:
    double probability;
};

// Class to calculate averages
class averager {
public:
    // Constructor
    averager() : total(0), count(0) {}

    // Add a number to the sequence
    void next_number(double value) {
        total += value;
        ++count;
    }

    // Return how many numbers have been processed
    std::size_t how_many_numbers() const { return count; }

    // Calculate the average
    double average() const {
        if (count == 0) {
            throw std::logic_error("No numbers to average.");
        }
        return total / count;
    }

private:
    double total;
    std::size_t count;
};

// Class to simulate the washer
class washer {
public:
    // Constructor
    washer(unsigned int s = 60) : seconds_per_wash(s), wash_time_left(0) {}

    // Simulate one second of washer time
    void one_second() {
        if (wash_time_left > 0) {
            --wash_time_left;
        }
    }

    // Start washing a car
    void start_washing() {
        if (!is_busy()) {
            wash_time_left = seconds_per_wash;
        }
    }

    // Check if the washer is busy
    bool is_busy() const { return wash_time_left > 0; }

private:
    unsigned int seconds_per_wash; // Time required for one wash
    unsigned int wash_time_left;   // Time left until the washer is free
};

#endif
