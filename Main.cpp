// Copyright 2025 Maks
#include <pthread.h>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

pthread_mutex_t* waitForFork;
int amountOfPhilosophers;
pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER;
std::vector<std::string> states;

void printStates() {
    pthread_mutex_lock(&printMutex);
    for (int i = 0; i < amountOfPhilosophers; i++) {
        std::cout << "Filozof " << i << " " << states[i] << "\n";
    }
    std::cout << "\n\n";
    pthread_mutex_unlock(&printMutex);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void *philosopher(void *arg) {
    int id = *reinterpret_cast<int*>(arg);
    int firstFork = std::min(id, (id + 1) % amountOfPhilosophers);
    int secondFork = std::max(id, (id + 1) % amountOfPhilosophers);

    while (true) {
        states[id] = "mysli";
        std::this_thread::sleep_for(std::chrono::seconds(4));

        pthread_mutex_lock(&waitForFork[firstFork]);
        pthread_mutex_lock(&waitForFork[secondFork]);

        states[id] = "je";
        printStates();
        std::this_thread::sleep_for(std::chrono::seconds(4));

        pthread_mutex_unlock(&waitForFork[secondFork]);
        pthread_mutex_unlock(&waitForFork[firstFork]);
    }
}

int main(int argc, const char * argv[]) {
    amountOfPhilosophers = std::stoi(argv[1]);
    std::cout << "Liczba filozofów: " << amountOfPhilosophers << std::endl;

    std::vector<pthread_t> philosophersThread(amountOfPhilosophers);
    std::vector<int> ids(amountOfPhilosophers);
    waitForFork = new pthread_mutex_t[amountOfPhilosophers];
    states.resize(amountOfPhilosophers, "mysli");
    printStates();

    for (int i = 0; i < amountOfPhilosophers; ++i) {
        pthread_mutex_init(&waitForFork[i], nullptr);
    }

    for (int i = 0; i < amountOfPhilosophers; ++i) {
        ids[i] = i;
        pthread_create(&philosophersThread[i], nullptr, &philosopher, &ids[i]);
    }

    for (int i = 0; i < amountOfPhilosophers; ++i) {
        pthread_join(philosophersThread[i], nullptr);
    }

    for (int i = 0; i < amountOfPhilosophers; ++i) {
        pthread_mutex_destroy(&waitForFork[i]);
    }

    delete[] waitForFork;
    return 0;
}
