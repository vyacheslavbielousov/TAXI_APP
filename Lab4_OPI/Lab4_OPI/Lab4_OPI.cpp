#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <limits> // Для numeric_limits
#include <algorithm> // Для transform

using namespace std;

// Tariff constants
const double BASE_RATE = 25.0;        // Base cost
const double RATE_PER_KM = 8.0;       // Cost per kilometer
const double RATE_PER_MIN = 2.0;      // Cost per minute

// Car types and their coefficients
map<string, double> carTypes = {
    {"standard", 1.0},
    {"comfort", 1.3},
    {"business", 1.8},
    {"minivan", 2.0}
};

// Time of day coefficients
map<string, double> timeCoefficients = {
    {"day", 1.0},
    {"night", 1.2},
    {"morning", 1.1},
    {"evening", 1.15}
};

void displayWelcomeMessage() {
    cout << "Welcome to Taxi App!" << endl;
    cout << "Please enter your travel details:" << endl;
}

double enterDistance() {
    double distance;
    cout << "Enter trip distance (km): ";
    cin >> distance;

    // Input validation
    if (distance <= 0) {
        cout << "Invalid distance. Using default value 5 km." << endl;
        return 5.0;
    }
    return distance;
}
/**
 * Function to input estimated trip time
 * @return time in minutes
 */
double enterTime() {
    double time;
    cout << "Enter estimated trip time (min): ";
    cin >> time;

    // Input validation
    if (time <= 0) {
        cout << "Invalid time. Using default value 15 min." << endl;
        return 15.0;
    }
    return time;
}

/**
 * Function to select car type
 * @return selected car type as string
 */
string selectCarType() {
    string type;
    cout << "Available car types: standard, comfort, business, minivan" << endl;
    cout << "Select car type: ";
    cin >> type;

    // Convert to lowercase for case-insensitive comparison
    for (char& c : type) {
        c = tolower(c);
    }

    return type;
}

/**
 * Function to select time of day
 * @return selected time of day as string
 */
string selectTimeOfDay() {
    string time;
    cout << "Select time of day (day/night/morning/evening): ";
    cin >> time;

    // Convert to lowercase for case-insensitive comparison
    for (char& c : time) {
        c = tolower(c);
    }

    return time;
}

/**
 * Main function to calculate trip cost
 * @param distance - trip distance in km
 * @param time - trip time in minutes
 * @param carType - selected car type
 * @param timeOfDay - selected time of day
 * @return calculated trip cost
 */
double calculateTripCost(double distance, double time, const string& carType, const string& timeOfDay) {
    // Calculate base cost
    double cost = BASE_RATE;

    // Add distance cost
    cost += distance * RATE_PER_KM;

    // Add time cost
    cost += time * RATE_PER_MIN;

    // Apply car type coefficient
    // Note: inputs are already lowercase from selection functions
    if (carTypes.find(carType) != carTypes.end()) {
        double carCoefficient = carTypes[carType];
        cost *= carCoefficient;
    }
    else {
        // Fallback is handled silently here, but logged in printCalculationDetails
        cost *= carTypes["standard"];
    }

    // Apply time of day coefficient
    if (timeCoefficients.find(timeOfDay) != timeCoefficients.end()) {
        double timeCoefficient = timeCoefficients[timeOfDay];
        cost *= timeCoefficient;
    }
    else {
        cost *= timeCoefficients["day"];
    }

    // Round to 2 decimal places
    cost = round(cost * 100) / 100;

    return cost;
}

/**
 * Function to apply promo code discount
 * FIX APPLIED: Added final rounding to 2 decimal places
 * @param price - current price before discount
 * @return price after applying promo code
 */
double applyPromoCode(double price) {
    string promo;
    cout << "Do you have a promo code? (y/n): ";
    cin >> promo;

    if (promo == "y" || promo == "Y") {
        string code;
        cout << "Enter promo code: ";
        cin >> code;

        // Convert to uppercase
        for (char& c : code) {
            c = toupper(c);
        }

        // Check valid promo codes
        if (code == "TAXI10") {
            double discount = price * 0.1;
            price *= 0.9;  // 10% discount
            if (discount > 100) {
                price += (discount - 100);
                discount = 100;
            }
            cout << "Applied 10% discount (max 100 UAH): -" << discount << " UAH" << endl;
        }
        else if (code == "TAXI20") {
            double discount = price * 0.2;
            price *= 0.8;  // 20% discount
            if (discount > 100) {
                price += (discount - 100);
                discount = 100;
            }
            cout << "Applied 20% discount (max 100 UAH): -" << discount << " UAH" << endl;
        }
        else if (code == "TAXI50") {
            double discount = price * 0.5;
            price *= 0.5;  // 50% discount
            if (discount > 100) {
                price += (discount - 100);
                discount = 100;
            }
            cout << "Applied 50% discount (max 100 UAH): -" << discount << " UAH" << endl;
        }
        else {
            cout << "Invalid promo code" << endl;
        }
    }
    
    // FIX: Round result to 2 decimal places to avoid issues like 95.724
    return round(price * 100) / 100;
}

/**
 * Function to display detailed calculation breakdown
 * FIX APPLIED: Logic to detect invalid car/time types and show actual fallback values
 */
void printCalculationDetails(double distance, double time, const string& carType,
    const string& timeOfDay, double finalCost) {
    
    cout << "\n=== DETAILED CALCULATION BREAKDOWN ===" << endl;
    cout << "Distance: " << distance << " km" << endl;
    cout << "Time: " << time << " min" << endl;

    // FIX: Handle Car Type Reporting logic
    if (carTypes.find(carType) != carTypes.end()) {
        cout << "Car type: " << carType << " (coefficient " << carTypes[carType] << ")" << endl;
    } else {
        cout << "Car type: " << carType << " (Invalid - using Standard coeff " << carTypes["standard"] << ")" << endl;
    }

    // FIX: Handle Time of Day Reporting logic
    if (timeCoefficients.find(timeOfDay) != timeCoefficients.end()) {
        cout << "Time of day: " << timeOfDay << " (coefficient " << timeCoefficients[timeOfDay] << ")" << endl;
    } else {
        cout << "Time of day: " << timeOfDay << " (Invalid - using Day coeff " << timeCoefficients["day"] << ")" << endl;
    }

    cout << "Base rate: " << BASE_RATE << " UAH" << endl;
    cout << "Distance cost: " << distance << " km * " << RATE_PER_KM << " UAH/km = " << distance * RATE_PER_KM << " UAH" << endl;
    cout << "Time cost: " << time << " min * " << RATE_PER_MIN << " UAH/min = " << time * RATE_PER_MIN << " UAH" << endl;
    cout << "--------------------------------" << endl;
    cout << "FINAL COST: " << finalCost << " UAH" << endl;
}

/**
 * Function to calculate price for different car types
 * Shows comparison between available options
 */
void compareCarTypes(double distance, double time, const string& timeOfDay) {
    cout << "\n=== CAR TYPE COMPARISON ===" << endl;
    for (const auto& car : carTypes) {
        double cost = calculateTripCost(distance, time, car.first, timeOfDay);
        cout << car.first << ": " << cost << " UAH" << endl;
    }
}

/**
 * Main calculation module function
 * Orchestrates the entire price calculation process
 */
void processCalculation() {
    cout << "\n=== TRIP COST CALCULATION ===" << endl;

    // Input trip parameters
    double distance = enterDistance();
    double time = enterTime();
    string carType = selectCarType();
    string timeOfDay = selectTimeOfDay();

    // Calculate initial cost
    double cost = calculateTripCost(distance, time, carType, timeOfDay);

    // Show initial calculation
    cout << "\nInitial cost: " << cost << " UAH" << endl;

    // Show car type comparison
    compareCarTypes(distance, time, timeOfDay);

    // Apply promo codes
    cost = applyPromoCode(cost);

    // Display final detailed calculation
    printCalculationDetails(distance, time, carType, timeOfDay, cost);

    // Additional information
    cout << "\n=== ADDITIONAL INFORMATION ===" << endl;
    cout << "This calculation is an estimate." << endl;
    cout << "Final cost may vary based on actual route and traffic conditions." << endl;
}

/**
 * Main program entry point
 */
int main() {
    displayWelcomeMessage();

    // Process the calculation
    processCalculation();

    // Option to calculate again
    string again;
    cout << "\nWould you like to calculate another trip? (y/n): ";
    cin >> again;

    if (again == "y" || again == "Y") {
        processCalculation();
    }
    else {
        cout << "Thank you for using Taxi App!" << endl;
    }

    return 0;
}

