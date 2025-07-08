#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int NUM_ELEMENTS = 400;
vector<int> baseArray(NUM_ELEMENTS);

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;

// Structure for each visual sorter
struct SortVisualizer {
    vector<int> arr;
    int offsetY;
    string name;
    bool finished = false;
};

// Draw one sorting visual section
void drawBars(SortVisualizer& vis, int highlight1 = -1, int highlight2 = -1) {
    int barWidth = SCREEN_WIDTH / NUM_ELEMENTS;
    int sectionHeight = SCREEN_HEIGHT / 3;
    int startY = vis.offsetY;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        SDL_Rect bar = {
            i * barWidth,
            startY + sectionHeight - vis.arr[i] * sectionHeight / NUM_ELEMENTS,
            barWidth - 1,
            vis.arr[i] * sectionHeight / NUM_ELEMENTS
        };

        if (i == highlight1 || i == highlight2)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (vis.finished)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);

        SDL_RenderFillRect(renderer, &bar);
    }
}

// Bubble Sort
void bubbleSort(SortVisualizer& vis) {
    for (int i = 0; i < vis.arr.size(); ++i) {
        for (int j = 0; j < vis.arr.size() - i - 1; ++j) {
            if (vis.arr[j] > vis.arr[j + 1]) {
                swap(vis.arr[j], vis.arr[j + 1]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            drawBars(vis, j, j + 1);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }
    }
    vis.finished = true;
}

// Merge Sort Helper
void merge(vector<int>& arr, int l, int m, int r, SortVisualizer& vis) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawBars(vis, k - 1);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort
void mergeSort(vector<int>& arr, int l, int r, SortVisualizer& vis) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, vis);
        mergeSort(arr, m + 1, r, vis);
        merge(arr, l, m, r, vis);
    }
}

// Wrapper
void runMergeSort(SortVisualizer& vis) {
    mergeSort(vis.arr, 0, vis.arr.size() - 1, vis);
    vis.finished = true;
}

// Partition for QuickSort
int partition(vector<int>& arr, int low, int high, SortVisualizer& vis) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawBars(vis, j, high);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort
void quickSort(vector<int>& arr, int low, int high, SortVisualizer& vis) {
    if (low < high) {
        int pi = partition(arr, low, high, vis);
        quickSort(arr, low, pi - 1, vis);
        quickSort(arr, pi + 1, high, vis);
    }
}

void runQuickSort(SortVisualizer& vis) {
    quickSort(vis.arr, 0, vis.arr.size() - 1, vis);
    vis.finished = true;
}

// Initialization
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("Sorting Comparison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != nullptr;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    srand(time(NULL));
    generate(baseArray.begin(), baseArray.end(), []() { return rand() % NUM_ELEMENTS + 1; });

    SortVisualizer bubble{baseArray, 0, "Bubble"};
    SortVisualizer merge{baseArray, SCREEN_HEIGHT / 3, "Merge"};
    SortVisualizer quick{baseArray, 2 * SCREEN_HEIGHT / 3, "Quick"};

    if (!initSDL()) {
        cout << "SDL Init Failed\n";
        return 1;
    }

    thread t1(bubbleSort, ref(bubble));
    thread t2(runMergeSort, ref(merge));
    thread t3(runQuickSort, ref(quick));

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawBars(bubble);
        drawBars(merge);
        drawBars(quick);

        SDL_RenderPresent(renderer);

        if (bubble.finished && merge.finished && quick.finished)
            break;
    }

    t1.join();
    t2.join();
    t3.join();
    SDL_Delay(1000);
    closeSDL();
    return 0;
}

