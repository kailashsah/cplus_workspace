//#include <bits/stdc++.h>
#include <string>
#include <iostream>

using namespace std;

namespace abstract_car {

	class Car {
	protected:
		bool isSedan;
		string seats;

	public:
		Car(bool isSedan, string seats) {
			this->isSedan = isSedan;
			this->seats = seats;
		}

		bool getIsSedan() {
			return this->isSedan;
		}

		string getSeats() {
			return this->seats;
		}

		virtual string getMileage() = 0;

		void printCar(string name) {
			cout << "A " << name << " is " << (this->getIsSedan() ? "" : "not ")
				<< "Sedan, is " << this->getSeats() << "-seater, and has a mileage of around "
				<< getMileage() << ".\n";
		}
	};

	// Write your code here.

	/**
	*   WagonR class
	**/
	class  WagonR : public Car
	{
	protected:
		int mileage;
	public:
		WagonR(int arg_mileage) : Car(false, "4"), mileage(arg_mileage) {}
		string getMileage()
		{
			return to_string(mileage);
		}
	};

	/**
	*   HondaCity class
	**/
	class  HondaCity : public Car
	{
	protected:
		int mileage;
	public:
		HondaCity(int arg_mileage) : Car(true, "4"), mileage(arg_mileage) {}
		string getMileage()
		{
			return to_string(mileage) + " kmpl";
		}
	};
	/**
	*   InnovaCrysta class
	**/
	class  InnovaCrysta : public Car
	{
	protected:
		int mileage;
	public:
		InnovaCrysta(int arg_mileage) : Car(false, "7"), mileage(arg_mileage) {}
		string getMileage()
		{
			return to_string(mileage);
		}
	};

	int main()
	{
		int carType, carMileage;
		cin >> carType >> carMileage;
		Car *pointer;
		if (carType == 0) {
			WagonR wagonR(carMileage);
			pointer = &wagonR;
			wagonR.printCar("WagonR");
		}

		if (carType == 1) {
			HondaCity hondaCity(carMileage);
			pointer = &hondaCity;
			hondaCity.printCar("HondaCity");
		}

		if (carType == 2) {
			InnovaCrysta innovaCrysta(carMileage);
			pointer = &innovaCrysta;
			innovaCrysta.printCar("InnovaCrysta");
		}


		return 0;
	}
	/*int main()
	{
	abstract_car::main();

	}*/
}