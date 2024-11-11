#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Player {
    string name;
    int id;
    int score;

    Player(string playerName, int playerId, int playerScore)
        : name(playerName), id(playerId), score(playerScore) {}
};

// Swap function for quick sort
void swap(Player &a, Player &b) {
    Player temp = a;
    a = b;
    b = temp;
}

// Partition function for quick sort
int partition(vector<Player> &players, int low, int high) {
    int pivot = players[high].score;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (players[j].score > pivot) {
            i++;
            swap(players[i], players[j]);
        }
    }
    swap(players[i + 1], players[high]);
    return i + 1;
}

// Quick sort function
void quickSort(vector<Player> &players, int low, int high) {
    if (low < high) {
        int pi = partition(players, low, high);

        quickSort(players, low, pi - 1);
        quickSort(players, pi + 1, high);
    }
}

// Update match scores and resort
void updateMatch(vector<Player>& players, int player1Index, int player2Index, int points) {
    players[player1Index].score += points;
    players[player2Index].score -= points;

    quickSort(players, 0, players.size() - 1);
}

// Save player data to file
void savePlayersToFile(const vector<Player>& players, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& player : players) {
            file << player.name << "," << player.id << "," << player.score << "\n";
        }
        file.close();
    } else {
        cerr << "Unable to open file for saving data.\n";
    }
}

// Load player data from file
vector<Player> loadPlayersFromFile(const string& filename) {
    vector<Player> players;
    ifstream file(filename);
    string line, name;
    int id, score;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            ss >> id;
            ss.ignore();
            ss >> score;
            players.emplace_back(name, id, score);
        }
        file.close();
    } else {
        cerr << "Unable to open file for loading data.\n";
    }
    return players;
}

int main() {
    const string filename = "players_data.csv";

    // Load players from file
    vector<Player> players = loadPlayersFromFile(filename);
    if (players.empty()) {
        players = {Player("Alice", 1, 100), Player("Bob", 2, 150), Player("Charlie", 3, 120)};
    }

    cout << "Initial Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }

    // Update matches and see real-time ranking changes
    cout << "\nMatch Update:\n";
    updateMatch(players, 0, 1, 20); // Example: Alice wins against Bob, gaining 20 points

    cout << "\nUpdated Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }

    // Save updated players to file
    savePlayersToFile(players, filename);

    return 0;
}
