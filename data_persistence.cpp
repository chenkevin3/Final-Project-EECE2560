#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Player {
    string name;
    int id;
    int score;

    Player(string playerName, int playerId, int playerScore)
        : name(playerName), id(playerId), score(playerScore) {}
};

// Quick Sort for Ranking
void swap(Player &a, Player &b) {
    Player temp = a;
    a = b;
    b = temp;
}

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

void quickSort(vector<Player> &players, int low, int high) {
    if (low < high) {
        int pi = partition(players, low, high);
        quickSort(players, low, pi - 1);
        quickSort(players, pi + 1, high);
    }
}

void displayRankings(const vector<Player> &players) {
    cout << "\nCurrent Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - Score: " << player.score << "\n";
    }
}

// Update score after a match
void updateMatch(vector<Player> &players, int player1Id, int player2Id, int points) {
    for (auto &player : players) {
        if (player.id == player1Id) player.score += points;
        else if (player.id == player2Id) player.score -= points;
    }
    quickSort(players, 0, players.size() - 1);  // Update rankings after score change
}

void addPlayer(vector<Player> &players) {
    string name;
    int id, score;
    cout << "Enter player name: ";
    cin >> name;
    cout << "Enter player ID: ";
    cin >> id;
    cout << "Enter initial score: ";
    cin >> score;
    players.emplace_back(name, id, score);
    cout << "Player added successfully.\n";
}

void updatePlayerScore(vector<Player> &players) {
    int player1Id, player2Id, points;
    cout << "Enter ID of the first player: ";
    cin >> player1Id;
    cout << "Enter ID of the second player: ";
    cin >> player2Id;
    cout << "Enter points to award to the first player: ";
    cin >> points;
    updateMatch(players, player1Id, player2Id, points);
    cout << "Match updated successfully.\n";
}

void sortPlayers(vector<Player> &players) {
    quickSort(players, 0, players.size() - 1);
    cout << "Players sorted by score.\n";
}

// Save data to file
void saveDataToFile(const vector<Player> &players, const string &filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto &player : players) {
            outFile << player.name << " " << player.id << " " << player.score << "\n";
        }
        outFile.close();
        cout << "Data saved successfully.\n";
    } else {
        cout << "Failed to open file for saving.\n";
    }
}

// Load data from file
void loadDataFromFile(vector<Player> &players, const string &filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        players.clear();  // Clear any existing data
        string name;
        int id, score;
        while (inFile >> name >> id >> score) {
            players.emplace_back(name, id, score);
        }
        inFile.close();
        cout << "Data loaded successfully.\n";
    } else {
        cout << "No previous data found. Starting fresh.\n";
    }
}

int main() {
    vector<Player> players;
    const string filename = "player_data.txt";

    // Load existing data if available
    loadDataFromFile(players, filename);

    int choice;
    do {
        cout << "\n--- Tournament Menu ---\n";
        cout << "1. View Rankings\n";
        cout << "2. Add Player\n";
        cout << "3. Update Match Scores\n";
        cout << "4. Sort Players\n";
        cout << "5. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayRankings(players);
                break;
            case 2:
                addPlayer(players);
                break;
            case 3:
                updatePlayerScore(players);
                break;
            case 4:
                sortPlayers(players);
                break;
            case 5:
                saveDataToFile(players, filename);
                cout << "Exiting tournament system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
