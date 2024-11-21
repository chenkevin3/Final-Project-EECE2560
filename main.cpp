#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

// Namespace declaration
using namespace std;

// Player struct to store player details
struct Player {
    string name;
    int id;
    int score;
    
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
        } else {
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
            players.emplace_back(name, id, score);
        }
        file.close();
    }
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
    vector<Player> players = {
        Player("Alice", 1, 100),
        Player("Bob", 2, 150),
        Player("Charlie", 3, 120)
    };

    loadDataFromFile(players, "players.txt"); // Load data at program start
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
                cout << "Enter player score: ";
                cin >> score;
                players.emplace_back(name, id, score);
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
                } else {
                    cout << "Invalid player indices.\n";
                }
                break;
            }

            case 4:
                saveDataToFile(players, "players.txt");
                cout << "Rankings saved to file.\n";
                break;

            case 5:
                loadDataFromFile(players, "players.txt");
                cout << "Rankings loaded from file.\n";
                break;

            case 6:
                cout << "Exiting...\n";
                saveDataToFile(players, "players.txt"); // Auto-save before exit
                return 0;

            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <chrono>  // For performance measurement
#include <cstdlib> // For random number generation

using namespace std;

struct Player {
    string name;
    int id;
    int score;
    
    Player(string playerName, int playerId, int playerScore)
        : name(playerName), id(playerId), score(playerScore) {}
};

// Swap function for sorting
void swap(Player &a, Player &b) {
    Player temp = a;
    a = b;
    b = temp;
}

// Partition function for Quick Sort
int partition(vector<Player> &players, int low, int high) {
    int pivot = players[high].score;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (players[j].score > pivot) { // Sort in descending order
            i++;
            swap(players[i], players[j]);
        }
    }
    swap(players[i + 1], players[high]);
    return i + 1;
}

// Quick Sort function to rank players by score
void quickSort(vector<Player> &players, int low, int high) {
    if (low < high) {
        int pi = partition(players, low, high);
        
        quickSort(players, low, pi - 1);
        quickSort(players, pi + 1, high);
    }
}

// Function to update match results
void updateMatch(vector<Player>& players, int player1Index, int player2Index, int points) {
    players[player1Index].score += points;  // Player 1 gains points
    players[player2Index].score -= points;  // Player 2 loses points
    
    // Re-sort players by score to update rankings
    quickSort(players, 0, players.size() - 1);
}

// Generate random test data for validation
vector<Player> generateRandomPlayers(int count) {
    vector<Player> players;
    for (int i = 0; i < count; ++i) {
        string name = "Player" + to_string(i + 1);
        int score = rand() % 500;  // Random score between 0 and 500
        players.push_back(Player(name, i, score));
    }
    return players;
}

// Test the sorting algorithm and update mechanism
void runTests() {
    cout << "\n--- Running Tests ---\n";
    
    // Generate test data
    vector<Player> players = generateRandomPlayers(10); // Example with 10 players
    
    cout << "\nInitial Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }
    
    // Measure sorting time
    auto start = chrono::high_resolution_clock::now();
    quickSort(players, 0, players.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> sortDuration = end - start;
    
    cout << "\nSorted Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }
    cout << "Sorting time: " << sortDuration.count() << " seconds\n";
    
    // Update and re-sort after a match
    cout << "\nSimulating match (Player1 vs Player2, 20 points to Player1)...\n";
    updateMatch(players, 0, 1, 20);  // Player1 wins against Player2

    cout << "\nUpdated Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }
    
    // Check if rankings are maintained
    bool sorted = true;
    for (size_t i = 1; i < players.size(); ++i) {
        if (players[i-1].score < players[i].score) {
            sorted = false;
            break;
        }
    }
    cout << "\nRanking validation: " << (sorted ? "Passed" : "Failed") << "\n";
}

int main() {
    // Sample players
    vector<Player> players = {
        Player("Alice", 1, 100),
        Player("Bob", 2, 150),
        Player("Charlie", 3, 120),
    };

    // Display initial rankings
    cout << "Initial Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }

    // Update matches and see real-time ranking changes
    cout << "\nMatch Update:\n";
    updateMatch(players, 0, 1, 20); // Example: Alice wins against Bob, gaining 20 points

    // Display updated rankings
    cout << "\nUpdated Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }

    // Run tests on sorting and ranking functionality
    runTests();

    return 0;
}
