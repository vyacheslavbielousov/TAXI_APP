# TAXI_APP version 0.0.1

A C++ console application for calculating taxi trip costs with various pricing factors, discounts, and detailed breakdowns.

## Features

- **Dynamic Pricing Calculation** based on:
  - Distance traveled (km)
  - Trip duration (minutes)
  - Car type (Standard, Comfort, Business, Minivan)
  - Time of day (Day, Night, Morning, Evening)
- **Promo Code System** with discount options:
  - TAXI10: 10% discount (max 100 UAH)
  - TAXI20: 20% discount (max 100 UAH)
  - TAXI50: 50% discount (max 100 UAH)
- **Car Type Comparison** to help users choose the best option
- **Detailed Calculation Breakdown** showing all cost components
- **Input Validation** with default fallback values

## Pricing Structure

### Base Rates
- Base fare: 25.0 UAH
- Per kilometer: 8.0 UAH/km
- Per minute: 2.0 UAH/min

### Car Type Multipliers
| Car Type | Multiplier |
|----------|------------|
| Standard | 1.0x |
| Comfort | 1.3x |
| Business | 1.8x |
| Minivan | 2.0x |

### Time of Day Multipliers
| Time Period | Multiplier |
|-------------|------------|
| Day | 1.0x |
| Night | 1.2x |
| Morning | 1.1x |
| Evening | 1.15x |

## Requirements

- C++ compiler with C++11 support
- Standard Library (`iostream`, `string`, `cmath`, `map`)

## Usage

1. Run the compiled executable:
```bash
./taxi_calculator
```

2. Follow the prompts to enter:
   - Trip distance in kilometers
   - Estimated trip time in minutes
   - Preferred car type
   - Time of day for the trip
   - Promo code (optional)

3. View the detailed cost breakdown and comparison between car types

## Example Output

```
=== TRIP COST CALCULATION ===
Enter trip distance (km): 10
Enter estimated trip time (min): 20
Available car types: standard, comfort, business, minivan
Select car type: comfort
Select time of day (day/night/morning/evening): day

Initial cost: 261.0 UAH

=== CAR TYPE COMPARISON ===
standard: 201 UAH
comfort: 261.3 UAH
business: 361.8 UAH
minivan: 402 UAH

Do you have a promo code? (y/n): y
Enter promo code: TAXI10
Applied 10% discount (max 100 UAH): -26.1 UAH

=== DETAILED CALCULATION BREAKDOWN ===
Distance: 10 km
Time: 20 min
Car type: comfort (coefficient 1.3)
Time of day: day (coefficient 1.0)
Base rate: 25 UAH
Distance cost: 10 km * 8 UAH/km = 80 UAH
Time cost: 20 min * 2 UAH/min = 40 UAH
--------------------------------
FINAL COST: 234.9 UAH
```

## Input Validation

- Invalid distances or times (≤0) default to 5 km and 15 minutes respectively
- Invalid car types default to "standard"
- Invalid time of day defaults to "day"
- Case-insensitive input handling for car types and time periods

## Code Structure

- **`enterDistance()`** - Handles distance input with validation
- **`enterTime()`** - Handles time input with validation
- **`selectCarType()`** - Car type selection with case normalization
- **`selectTimeOfDay()`** - Time period selection with case normalization
- **`calculateTripCost()`** - Main calculation logic
- **`applyPromoCode()`** - Discount application with limits
- **`printCalculationDetails()`** - Detailed cost breakdown
- **`compareCarTypes()`** - Side-by-side car type comparison
- **`processCalculation()`** - Main orchestration function

## Notes

- All currency values are in Ukrainian Hryvnia (UAH)
- Calculations are estimates and may vary based on actual route conditions
- Promo code discounts are capped at 100 UAH maximum savings
- The application supports multiple calculations per session

## License

This project is open source and available under the MIT License.
