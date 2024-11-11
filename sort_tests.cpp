#include <iostream>
#include <vector>
#include <string>
#include <chrono>

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

// Quick Sort
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

// Merge Sort
void merge(vector<Player> &players, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Player> leftArr(n1), rightArr(n2);
    for (int i = 0; i < n1; i++) leftArr[i] = players[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = players[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].score >= rightArr[j].score) players[k++] = leftArr[i++];
        else players[k++] = rightArr[j++];
    }
    while (i < n1) players[k++] = leftArr[i++];
    while (j < n2) players[k++] = rightArr[j++];
}

void mergeSort(vector<Player> &players, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(players, left, mid);
        mergeSort(players, mid + 1, right);
        merge(players, left, mid, right);
    }
}

// Heap Sort
void heapify(vector<Player> &players, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && players[left].score > players[largest].score) largest = left;
    if (right < n && players[right].score > players[largest].score) largest = right;

    if (largest != i) {
        swap(players[i], players[largest]);
        heapify(players, n, largest);
    }
}

void heapSort(vector<Player> &players) {
    int n = players.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(players, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(players[0], players[i]);
        heapify(players, i, 0);
    }
}

// Benchmarking function
void benchmarkSort(void (*sortFunc)(vector<Player>&, int, int), vector<Player> players, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(players, 0, players.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took " << duration.count() << " seconds.\n";
}

// Overloaded benchmark function for heap sort (no low/high parameters)
void benchmarkSort(void (*sortFunc)(vector<Player>&), vector<Player> players, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(players);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took " << duration.count() << " seconds.\n";
}

int main() {
    // Sample players
    vector<Player> players = {
        Player("Alice", 1, 100),
        Player("Bob", 2, 150),
        Player("Charlie", 3, 120),
        Player("Dave", 4, 90),
        Player("Eve", 5, 130)
    };

    cout << "Benchmarking Sorting Algorithms:\n";

    // Quick Sort Benchmark
    benchmarkSort(quickSort, players, "Quick Sort");

    // Merge Sort Benchmark
    benchmarkSort(mergeSort, players, "Merge Sort");

    // Heap Sort Benchmark
    benchmarkSort(heapSort, players, "Heap Sort");

    cout << "\nFinal Rankings:\n";
    for (const auto &player : players) {
        cout << player.name << " - " << player.score << "\n";
    }

    return 0;
}
