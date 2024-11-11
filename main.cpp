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
