# AutoDrip: A Low-Cost Dengue Fluid Management System

## Overview
AutoDrip is a low-cost, gravity-driven automated controller designed to calculate required flow rates and regulate clinical flow rates for Group B dengue patients[cite: 1]. The device ensures accurate, safe, and standardized intravenous (IV) fluid delivery in resource-constrained healthcare environments[cite: 1]. 

## System Architecture
The system integrates four primary components[cite: 1]:
*   A flow calculator based on national dengue guidelines[cite: 1].
*   A non-contact infrared (IR) drop sensor[cite: 1].
*   A stepper-actuated flow regulator (Nema 17)[cite: 1].
*   A binary search-based feedback algorithm[cite: 1].

## Hardware Requirements
*   Microcontroller (e.g., ESP32 / Arduino)
*   Nema 17 Stepper Motor (17HS4401S)[cite: 1]
*   Non-contact IR Sensor (LED emitter and photodiode receiver)[cite: 1]
*   Standard Dial Flow Meter[cite: 1]
*   3D Printed Parts: Conical Coupler and Fixer (Files located in `/CAD`)[cite: 1]

## Software Installation
1. Clone this repository.
2. Open the `/firmware` directory in your preferred IDE.
3. Flash the firmware to the microcontroller. 

## Citation
If this project aids your research, please cite the original ICME 2025 paper:
> Ahasan, M. M., Shaikh, N. A., Himel, S. S., & Ahmed, M. T. (2025). *AutoDrip: A Low-Cost Dengue Fluid Management System*. 15th International Conference on Mechanical Engineering (ICME 2025).[cite: 1]
