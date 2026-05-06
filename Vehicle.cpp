#include <iostream>
using namespace std;

class Vehicle
{
private:
    int vehicle_ID;
    string vehicle_manufacturer;
    string vehicle_model;
    int vehicle_year;

    static int TotalVehicle;

public:
    Vehicle()
    {
        vehicle_ID = 0;
        vehicle_manufacturer = "not set";
        vehicle_model = "not set";
        vehicle_year = 0;
        TotalVehicle++;
    }

    Vehicle(int id, string manufacturer, string model, int year)
    {
        vehicle_ID = id;
        vehicle_manufacturer = manufacturer;
        vehicle_model = model;
        vehicle_year = year;
        TotalVehicle++;
    }

    virtual ~Vehicle()
    {
        TotalVehicle--;
    }

    int getVehicle_id()
    {
        return vehicle_ID;
    }

    virtual void input()
    {
        cout << "Enter Vehicle ID: ";
        cin >> vehicle_ID;
        cin.ignore();

        cout << "Enter Vehicle Manufacturer: ";
        getline(cin, vehicle_manufacturer);

        cout << "Enter Vehicle Model: ";
        getline(cin, vehicle_model);

        cout << "Enter Vehicle Year: ";
        cin >> vehicle_year;
        cin.ignore();
    }

    virtual void Display()
    {
        cout << "\nVehicle ID           : " << vehicle_ID << endl;
        cout << "Vehicle Manufacturer : " << vehicle_manufacturer << endl;
        cout << "Vehicle Model        : " << vehicle_model << endl;
        cout << "Vehicle Year         : " << vehicle_year << endl;
    }
};

int Vehicle::TotalVehicle = 0;

class Car : public Vehicle
{
protected:
    string fuelType;

public:
    Car() : Vehicle()
    {
        fuelType = "not set";
    }

    void input() override
    {
        Vehicle::input();

        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);
    }

    void Display() override
    {
        Vehicle::Display();
        cout << "Fuel Type           : " << fuelType << endl;
    }
};

class ElectricCar : public Car
{
protected:
    int batteryCapacity;

public:
    ElectricCar()
    {
        batteryCapacity = 0;
    }

    void input() override
    {
        Car::input();

        cout << "Enter Battery Capacity: ";
        cin >> batteryCapacity;
        cin.ignore();
    }

    void Display() override
    {
        Car::Display();
        cout << "Battery Capacity    : " << batteryCapacity << " kWh" << endl;
    }
};

class Aircraft
{
protected:
    int flightRange;

public:
    Aircraft()
    {
        flightRange = 0;
    }

    virtual void input()
    {
        cout << "Enter Flight Range: ";
        cin >> flightRange;
        cin.ignore();
    }

    virtual void Display()
    {
        cout << "Flight Range         : " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    void input() override
    {
        Car::input();
        Aircraft::input();
    }

    void Display() override
    {
        Car::Display();
        Aircraft::Display();
    }
};

class SportsCar : public ElectricCar
{
protected:
    int topSpeed;

public:
    SportsCar()
    {
        topSpeed = 0;
    }

    void input() override
    {
        ElectricCar::input();

        cout << "Enter Top Speed: ";
        cin >> topSpeed;
        cin.ignore();
    }

    void Display() override
    {
        ElectricCar::Display();
        cout << "Top Speed           : " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car
{
public:
    void Display() override
    {
        cout << "\n===== Sedan Car =====" << endl;
        Car::Display();
    }
};

class SUV : public Car
{
public:
    void Display() override
    {
        cout << "\n===== SUV Car =====" << endl;
        Car::Display();
    }
};

class VehicleRegistry
{
private:
    Vehicle *Vehicles[100];
    int count;

public:
    VehicleRegistry()
    {
        count = 0;
    }

    void AddVehicle()
    {
        int choice;

        if (count >= 100)
        {
            cout << "Registry is Full!" << endl;
            return;
        }

        cout << "\n1. Car" << endl;
        cout << "2. Electric Car" << endl;
        cout << "3. Flying Car" << endl;
        cout << "4. Sports Car" << endl;
        cout << "5. Sedan" << endl;
        cout << "6. SUV" << endl;

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
            return;
        }
        cin.ignore();

        if (choice == 1)
        {
            Vehicles[count] = new Car();
        }
        else if (choice == 2)
        {
            Vehicles[count] = new ElectricCar();
        }
        else if (choice == 3)
        {
            Vehicles[count] = new FlyingCar();
        }
        else if (choice == 4)
        {
            Vehicles[count] = new SportsCar();
        }
        else if (choice == 5)
        {
            Vehicles[count] = new Sedan();
        }
        else if (choice == 6)
        {
            Vehicles[count] = new SUV();
        }
        else
        {
            cout << "Invalid Choice!" << endl;
            return;
        }

        Vehicles[count]->input();

        cout << "\n===== Vehicle Added Details =====" << endl;
        Vehicles[count]->Display();

        count++;

        cout << "\nVehicle Added Successfully!" << endl;
    }

    void DisplayAll()
    {
        if (count == 0)
        {
            cout << "No Vehicle Found!" << endl;
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << "\n===== Vehicle " << i + 1 << " =====" << endl;
            Vehicles[i]->Display();
        }
    }

    void SearchID()
    {
        int id;

        cout << "Enter Vehicle ID: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (Vehicles[i]->getVehicle_id() == id)
            {
                cout << "\n===== Vehicle Found =====" << endl;
                Vehicles[i]->Display();
                return;
            }
        }

        cout << "Vehicle Not Found!" << endl;
    }

    ~VehicleRegistry()
    {
        for (int i = 0; i < count; i++)
        {
            delete Vehicles[i];
        }
    }
};

int main()
{
    VehicleRegistry Registry;
    int choice;

    do
    {
        cout << "\n---- Vehicle Registry -----" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. View All Vehicle" << endl;
        cout << "3. Search by ID" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
            continue;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            Registry.AddVehicle();
            break;

        case 2:
            Registry.DisplayAll();
            break;

        case 3:
            Registry.SearchID();
            break;

        case 4:
            cout << "Exit..." << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 4);

    return 0;
}