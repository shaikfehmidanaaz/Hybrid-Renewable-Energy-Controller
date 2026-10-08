#include <iostream>
using namespace std;

class HybridRenewableEnergyController {
private:
    double solarPower;
    double windPower;
    double loadDemand;
    double batteryCapacity;
    double batteryLevel;

public:
    HybridRenewableEnergyController(double solar, double wind,
                                    double load, double capacity,
                                    double battery) {
        solarPower = solar;
        windPower = wind;
        loadDemand = load;
        batteryCapacity = capacity;
        batteryLevel = battery;
    }

    void controlEnergy() {
        double renewablePower = solarPower + windPower;

        cout << "----- Hybrid Renewable Energy Controller -----" << endl;
        cout << "Solar Power       : " << solarPower << " kW" << endl;
        cout << "Wind Power        : " << windPower << " kW" << endl;
        cout << "Renewable Power   : " << renewablePower << " kW" << endl;
        cout << "Load Demand       : " << loadDemand << " kW" << endl;
        cout << "Battery Level     : " << batteryLevel << " kWh" << endl;

        if (renewablePower >= loadDemand) {
            double excessPower = renewablePower - loadDemand;

            cout << "\nLoad supplied by renewable energy." << endl;
            cout << "Excess Power      : " << excessPower << " kW" << endl;

            // Charge battery with excess energy
            double availableBatterySpace =
                batteryCapacity - batteryLevel;

            double chargingPower;

            if (excessPower <= availableBatterySpace)
                chargingPower = excessPower;
            else
                chargingPower = availableBatterySpace;

            batteryLevel += chargingPower;

            cout << "Battery Charging  : " << chargingPower << " kWh" << endl;
        }
        else {
            double shortage = loadDemand - renewablePower;

            cout << "\nRenewable energy is insufficient." << endl;
            cout << "Power Shortage    : " << shortage << " kW" << endl;

            // Use battery to meet shortage
            if (batteryLevel >= shortage) {
                batteryLevel -= shortage;
                cout << "Battery Used      : " << shortage << " kWh" << endl;
                cout << "Load supplied using battery." << endl;
            }
            else {
                double batteryUsed = batteryLevel;
                double remainingShortage = shortage - batteryUsed;

                batteryLevel = 0;

                cout << "Battery Used      : " << batteryUsed << " kWh" << endl;
                cout << "Remaining Shortage: "
                     << remainingShortage << " kW" << endl;
                cout << "External/Grid Power Required." << endl;
            }
        }

        cout << "Final Battery Level: "
             << batteryLevel << " kWh" << endl;
    }
};

int main() {

    double solarPower = 40;       // kW
    double windPower = 30;        // kW
    double loadDemand = 50;       // kW
    double batteryCapacity = 100; // kWh
    double batteryLevel = 40;     // kWh

    HybridRenewableEnergyController controller(
        solarPower,
        windPower,
        loadDemand,
        batteryCapacity,
        batteryLevel
    );

    controller.controlEnergy();

    return 0;
}
