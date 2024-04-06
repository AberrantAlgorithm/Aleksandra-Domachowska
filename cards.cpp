#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class PokemonCard {
public:
    std::string type;
    std::string generation;
    std::string name;
    std::string serialNumber;

    PokemonCard(std::string t, std::string g, std::string n, std::string s) : type(t), generation(g), name(n), serialNumber(s) {}

    void exportToCSV(std::ofstream& file) {
        file << type << "," << generation << "," << name << "," << serialNumber << "\n";
    }
};

class PokemonCardCollection {
private:
    std::vector<PokemonCard*> cards;

public:
    PokemonCardCollection() {}

    ~PokemonCardCollection() {
        for (PokemonCard* card : cards) {
            delete card;
        }
    }

    void addCard(PokemonCard* card) {
        cards.push_back(card);
    }

    bool exportToCSV(std::string filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        file << "Type,Generation,Name,Serial Number\n";
        for (PokemonCard* card : cards) {
            card->exportToCSV(file);
        }
        file.close();
        std::cout << "Cards exported to " << filename << std::endl;
        return true;
    }
};

int main() {
    int choice;
    PokemonCardCollection collection;

    while (true) {
        std::cout << "\nPokemon Card Collector\n"
                  << "--------------------\n"
                  << "1. Add a card\n"
                  << "2. Export to CSV\n"
                  << "3. Quit\n"
                  << "--------------------\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        std::string type, generation, name, serialNumber;
        switch (choice) {
        case 1:
            std::cout << "Enter the type: ";
            std::cin >> type;
            std::cout << "Enter the generation: ";
            std::cin >> generation;
            std::cout << "Enter the name: ";
            std::cin >> name;
            std::cout << "Enter the serial number: ";
            std::cin >> serialNumber;

            
            if (type.empty() || generation.empty() || name.empty() || serialNumber.empty()) {
                std::cout << "Invalid input. Please try again." << std::endl;
                break;
            }

            collection.addCard(new PokemonCard(type, generation, name, serialNumber));
            break;

        case 2:
            {
                std::string filename;
                std::cout << "Enter the filename: ";
                std::cin >> filename;

                
                if (filename.empty()) {
                    std::cout << "Invalid input. Please try again." << std::endl;
                    break;
                }

                if (!collection.exportToCSV(filename)) {
                    std::cout << "Error: Could not export cards to file." << std::endl;
                }
                break;
            }

        case 3:
            std::cout << "Goodbye!\n";
            return 0;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
