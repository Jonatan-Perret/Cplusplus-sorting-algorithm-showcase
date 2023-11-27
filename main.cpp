#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int BAR_WIDTH = 1;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

void closeSDL() {
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}

void drawBars(const std::vector<int>& bars) {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);

  for (size_t i = 0; i < bars.size(); ++i) {
    SDL_Rect fillRect = {static_cast<int>(i * BAR_WIDTH), SCREEN_HEIGHT - bars[i], BAR_WIDTH, bars[i]};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
  }

  SDL_RenderPresent(gRenderer);
}

void bubbleSort(std::vector<int>& arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        drawBars(arr);
      }
    }
  }
}

void selectionSort(std::vector<int>& arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < n; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    std::swap(arr[i], arr[min_index]);
    drawBars(arr);
  }
}

void insertionSort(std::vector<int>& arr) {
  int n = arr.size();
  for (int i = 1; i < n; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
    drawBars(arr);
  }
}

int quickSortPartition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j <= high - 1; ++j) {
    if (arr[j] < pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
      drawBars(arr);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  drawBars(arr);
  return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pi = quickSortPartition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void quickSort(std::vector<int>& arr) {
  quickSort(arr, 0, arr.size() - 1);
}


void randomizeArray(std::vector<int>& arr) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, SCREEN_HEIGHT - 1);

  for (int& val : arr) {
    val = dis(gen);
  }
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  gWindow = SDL_CreateWindow("Sorting Algorithms Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  std::vector<int> bars(SCREEN_WIDTH / BAR_WIDTH);
  randomizeArray(bars);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      else if (e.type == SDL_KEYDOWN) {
        // record time at start of sorting
        auto start = std::chrono::high_resolution_clock::now();
        if (e.key.keysym.sym == SDLK_b) {
          std::vector<int> tempBars = bars;
          bubbleSort(tempBars);
        }
        else if (e.key.keysym.sym == SDLK_s) {
          std::vector<int> tempBars = bars;
          selectionSort(tempBars);
        }
        else if (e.key.keysym.sym == SDLK_i) {
          std::vector<int> tempBars = bars;
          insertionSort(tempBars);
        }
        else if (e.key.keysym.sym == SDLK_q) {
          std::vector<int> tempBars = bars;
          quickSort(tempBars);
        }
        else if (e.key.keysym.sym == SDLK_r) {
          randomizeArray(bars);
          drawBars(bars);
        }
        // record time at end of sorting
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken by sorting algorithm: " << elapsed.count() << " seconds" << std::endl;
      }
    }
  }

  closeSDL();
  return 0;
}
