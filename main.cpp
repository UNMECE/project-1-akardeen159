#include <iostream>
#include "capacitor.h"  

int main() {
    const double dt = 1e-10;        // Time 
    const double final_time = 5e-6; // Final time
    const int num_steps = static_cast<int>(final_time / dt);
    const double C = 100e-12;       // Capacitance 
    const double I = 1e-2;          // Current 
    const double V0 = 10.0;         // Voltage 
    const double R = 1e3;           // Resistance

    Capacitor cap_current;  // For constant current circuit
    Capacitor cap_voltage;  // For constant voltage circuit

    // Allocate arrays
    cap_current.time = new double[num_steps];
    cap_current.voltage = new double[num_steps];
    cap_current.current = new double[num_steps];
    cap_current.C = C;

    cap_voltage.time = new double[num_steps];
    cap_voltage.voltage = new double[num_steps];
    cap_voltage.current = new double[num_steps];
    cap_voltage.C = C;


    // Initialize arrays
    cap_current.time[0] = 0.0;
    cap_current.voltage[0] = 0.0;
    cap_current.current[0] = I;

    cap_voltage.time[0] = 0.0;
    cap_voltage.voltage[0] = 0.0;
    cap_voltage.current[0] = V0 / R;  // Initial current for constant voltage

    // Simulate constant current circuit
    std::cout << "simulating constant current circuit:\n";
    for (int t = 1; t < num_steps; ++t) {
        cap_current.time[t] = cap_current.time[t-1] + dt;
        cap_current.voltage[t] = cap_current.voltage[t-1] + (cap_current.current[0] * dt / cap_current.C);

        // Print results every 200 steps
        if ((t + 1) % 200 == 0 || t == num_steps - 1) {
            std::cout << "Step " << t + 1 << ": Time = " << cap_current.time[t] 
                      << " s, Current = " << cap_current.current[0] 
                      << " A, Voltage = " << cap_current.voltage[t] << " V\n";
        }
    }

    // Simulate constant voltage circuit
    std::cout << "\nSimulating constant voltage circuit:\n";
    for (int t = 1; t < num_steps; ++t) {
        cap_voltage.time[t] = cap_voltage.time[t-1] + dt;

        // Current calculation
        cap_voltage.current[t] = cap_voltage.current[t-1] - (cap_voltage.current[t-1] * dt / (R * cap_voltage.C));

        // Voltage
        cap_voltage.voltage[t] = V0 - cap_voltage.current[t] * R;

        // Print results every 200 steps
        if ((t + 1) % 200 == 0 || t == num_steps - 1) {
            std::cout << "Step " << t + 1 << ": Time = " << cap_voltage.time[t] 
                      << " s, Current = " << cap_voltage.current[t] 
                      << " A, Voltage = " << cap_voltage.voltage[t] << " V\n";
        }
    }

    // Clean memory
    delete[] cap_current.time;
    delete[] cap_current.voltage;
    delete[] cap_current.current;

    delete[] cap_voltage.time;
    delete[] cap_voltage.voltage;
    delete[] cap_voltage.current;

    return 0;
}
