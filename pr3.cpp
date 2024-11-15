#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base Class: Vehicle
class Vehicle {
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    Vehicle(int id, string manu, string mod, int yr) : vehicleID(id), manufacturer(manu), model(mod), year(yr) {
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    static int getTotalVehicles() {
        return totalVehicles;
    }

    int getVehicleID() const { return vehicleID; }
    string getManufacturer() const { return manufacturer; }
    string getModel() const { return model; }
    int getYear() const { return year; }

    virtual void display() const {
        cout << "ID: " << vehicleID << ", Manufacturer: " << manufacturer
             << ", Model: " << model << ", Year: " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

// Derived Class: Car (Single Inheritance)
class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car(int id, string manu, string mod, int yr, string fuel)
        : Vehicle(id, manu, mod, yr), fuelType(fuel) {}

    void display() const override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Derived Class: ElectricCar (Multilevel Inheritance from Car)
class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar(int id, string manu, string mod, int yr, string fuel, int battery)
        : Car(id, manu, mod, yr, fuel), batteryCapacity(battery) {}

    void display() const override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// Base Class: Aircraft
class Aircraft {
protected:
    int flightRange;

public:
    Aircraft(int range) : flightRange(range) {}

    void display() const {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

// Derived Class: FlyingCar (Multiple Inheritance from Car and Aircraft)
class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int id, string manu, string mod, int yr, string fuel, int range)
        : Car(id, manu, mod, yr, fuel), Aircraft(range) {}

    void display() const override {
        Car::display();
        Aircraft::display();
    }
};

// Derived Class: SportsCar (Multilevel Inheritance from ElectricCar)
class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar(int id, string manu, string mod, int yr, string fuel, int battery, int speed)
        : ElectricCar(id, manu, mod, yr, fuel, battery), topSpeed(speed) {}

    void display() const override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};


class Sedan : public Car {
public:
    Sedan(int id, string manu, string mod, int yr, string fuel) : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        cout << "Sedan - ";
        Car::display();
    }
};

class SUV : public Car {
public:
    SUV(int id, string manu, string mod, int yr, string fuel) : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        cout << "SUV - ";
        Car::display();
    }
};

// VehicleRegistry Class
class VehicleRegistry {
private:
    vector<Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* v) {
        vehicles.push_back(v);
    }

    void displayAllVehicles() const {
        for (const auto& vehicle : vehicles) {
            vehicle->display();
            cout << "-------------------------" << endl;
        }
    }

    void searchVehicleByID(int id) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle->getVehicleID() == id) {
                vehicle->display();
                return;
            }
        }
        cout << "Vehicle with ID " << id << " not found!" << endl;
    }

    ~VehicleRegistry() {
        for (auto& vehicle : vehicles) {
            delete vehicle;
        }
    }
};

// Main Function
int main() {
    VehicleRegistry registry;
    int choice;

    do {
        cout << "--- Vehicle Registry Menu ---" << endl;
        cout << "1. Add New Vehicle" << endl;
        cout << "2. Display All Vehicles" << endl;
        cout << "3. Search Vehicle by ID" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, year, battery = 0, range = 0, speed = 0;
            string manu, model, fuel;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter Manufacturer: ";
            cin >> manu;
            cout << "Enter Model: ";
            cin >> model;
            cout << "Enter Year: ";
            cin >> year;

            cout << "Select Vehicle Type:\n1. Car\n2. Electric Car\n3. Flying Car\n4. Sports Car\n5. Sedan\n6. SUV\n";
            int type;
            cin >> type;

            if (type == 1) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new Car(id, manu, model, year, fuel));
            } else if (type == 2) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity: ";
                cin >> battery;
                registry.addVehicle(new ElectricCar(id, manu, model, year, fuel, battery));
            } else if (type == 3) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Flight Range: ";
                cin >> range;
                registry.addVehicle(new FlyingCar(id, manu, model, year, fuel, range));
            } else if (type == 4) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity: ";
                cin >> battery;
                cout << "Enter Top Speed: ";
                cin >> speed;
                registry.addVehicle(new SportsCar(id, manu, model, year, fuel, battery, speed));
            } else if (type == 5) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new Sedan(id, manu, model, year, fuel));
            } else if (type == 6) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new SUV(id, manu, model, year, fuel));
            }
        } else if (choice == 2) {
            registry.displayAllVehicles();
        } else if (choice == 3) {
            int id;
            cout << "Enter Vehicle ID to search: ";
            cin >> id;
            registry.searchVehicleByID(id);
        }

    } while (choice != 4);

    cout << "Exiting the system. Goodbye!" << endl;
    return 0;
}
