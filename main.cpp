#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

class Dogs {
private:
    unordered_map<string, int> dogPopulationByCountry;
    int totalDogs;

public:
    Dogs() : totalDogs(0) {}

    void loadDataFromFile(const string& filename) {
        ifstream file(filename);
        string country;
        int population;

        if (!file) {
            throw runtime_error("Unable to open file");
        }

        while (file >> country >> population) {
            dogPopulationByCountry[country] = population;
            totalDogs += population;
        }
        file.close();
    }

    void showTotalDogs() const {
        cout << "Total number of dogs in the world: " << totalDogs << endl;
    }

    void showDogsByCountry(const string& country) const {
        auto it = dogPopulationByCountry.find(country);
        if (it != dogPopulationByCountry.end()) {
            cout << "Number of dogs in " << country << ": " << it->second << endl;
        } else {
            cout << "No data available for " << country << endl;
        }
    }
};

int main() {
    Dogs dogs;
    try {
        dogs.loadDataFromFile("dogs.txt");
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    int choice;
    string country;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. See total number of dogs in the world\n";
        cout << "2. Find out how many dogs are in a country\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                dogs.showTotalDogs();
                break;
            case 2:
                cout << "Enter country name: ";
                cin >> country;
                dogs.showDogsByCountry(country);
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
