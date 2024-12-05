#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Namespace declaration
using namespace std;

const string filename = "players_data.csv";

// Player struct to store player details
struct Player {
    string name;
    int id;
    int score;
    
    // Default constructor
    Player() : name(""), id(0), score(0) {}
    
    Player(string playerName, int playerId, int playerScore)
        : name(playerName), id(playerId), score(playerScore) {}
};

// Merge function for Merge Sort
void merge(vector<Player> &players, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Player> leftArray(n1);
    vector<Player> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = players[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = players[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].score >= rightArray[j].score) {
            players[k] = leftArray[i];
            i++;
        } 
        else {
            players[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        players[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        players[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort function to rank players
void mergeSort(vector<Player> &players, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(players, left, mid);
        mergeSort(players, mid + 1, right);
        merge(players, left, mid, right);
    }
}

// Advanced ranking logic in match update
void updateMatch(vector<Player> &players, int player1Index, int player2Index, int points) {
    int difficultyFactor = players[player2Index].score / 100;
    players[player1Index].score += points * difficultyFactor;

    mergeSort(players, 0, players.size() - 1);
}

// Save player data to file for persistence
void saveDataToFile(const vector<Player> &players, const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto &player : players) {
            file << player.name << " " << player.id << " " << player.score << "\n";
        }
        file.close();
    }
}

// Load player data from file
void loadDataFromFile(vector<Player> &players, const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string name;
        int id, score;
        players.clear(); // Clear existing players before loading new data
        while (file >> name >> id >> score) {
            players.push_back(Player(name, id, score)); // Use push_back here
        }
        file.close();
    }
}

// Check if the player ID already exists in the system
bool playerIdExists(const vector<Player> &players, int playerId) {
    for (const auto &player : players) {
        if (player.id == playerId) {
            return true;
        }
    }
    return false;
}

// Command-line interface function
void displayMenu() {
    cout << "\nTournament Ranking System\n";
    cout << "1. View Rankings\n";
    cout << "2. Add Player\n";
    cout << "3. Run Match Update\n";
    cout << "4. Save Rankings\n";
    cout << "5. Load Rankings\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Player> players;
    players.push_back(Player("Alice", 1, 100));
    players.push_back(Player("Bob", 2, 150));
    players.push_back(Player("Joe", 3, 120));

    loadDataFromFile(players, "players_data.csv"); // Load data at program start
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nCurrent Rankings:\n";
                for (const auto &player : players) {
                    cout << player.name << " - " << player.score << "\n";
                }
                break;

            case 2: {
                string name;
                int id, score;
                cout << "Enter player name: ";
                cin >> name;
                cout << "Enter player ID: ";
                cin >> id;

                // Check if player ID already exists
                while (playerIdExists(players, id)) {
                    cout << "Error: Player ID already exists. Please enter a different ID: ";
                    cin >> id;
                }

                cout << "Enter player score: ";
                cin >> score;

                players.push_back(Player(name, id, score)); // Use push_back here
                mergeSort(players, 0, players.size() - 1);
                cout << "Player added and rankings updated.\n";
                break;
            }

            case 3: {
                int p1, p2, points;
                cout << "Enter index of player 1: ";
                cin >> p1;
                cout << "Enter index of player 2: ";
                cin >> p2;
                cout << "Enter points for the match: ";
                cin >> points;
                if (p1 < players.size() && p2 < players.size()) {
                    updateMatch(players, p1, p2, points);
                    cout << "Match updated and rankings adjusted.\n";
                } 
                else {
                    cout << "Invalid player indices.\n";
                }
                break;
            }

            case 4:
                saveDataToFile(players, "players_data.csv");
                cout << "Rankings saved to file.\n";
                break;

            case 5:
                loadDataFromFile(players, "players_data.csv");
                cout << "Rankings loaded from file.\n";
                break;

            case 6:
                cout << "Exiting...\n";
                saveDataToFile(players, "players_data.csv"); // Auto-save before exit
                return 0;

            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}
