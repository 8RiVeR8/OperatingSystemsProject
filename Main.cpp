// Copyright 2025 Maks
#include <pthread.h>
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

pthread_mutex_t* waitForFork;
int amountOfPhilosophers;
pthread_mutex_t waitForThinking = PTHREAD_MUTEX_INITIALIZER;

void *philosopher(void *arg) {
    int id = *reinterpret_cast<int*>(arg);
    int firstFork = std::min(id, (id + 1) % amountOfPhilosophers);
    int secondFork = std::max(id, (id + 1) % amountOfPhilosophers);

    while (true) {
        pthread_mutex_lock(&waitForThinking);
        std::cout << "Filozof numer: " << id << " myśli\n";
        pthread_mutex_unlock(&waitForThinking);

        std::this_thread::sleep_for(std::chrono::seconds(8));
        pthread_mutex_lock(&waitForFork[firstFork]);
        pthread_mutex_lock(&waitForThinking);
        std::cout << "Filozof " << id << " wzial widelec " << firstFork << "\n";
        pthread_mutex_unlock(&waitForThinking);

        pthread_mutex_lock(&waitForFork[secondFork]);
        pthread_mutex_lock(&waitForThinking);
        std::cout << "Filozof " << id << " wzial widelec " << secondFork;
        std::cout << " i zaczal jesc" << "\n";
        pthread_mutex_unlock(&waitForThinking);
        std::this_thread::sleep_for(std::chrono::seconds(16));

        pthread_mutex_unlock(&waitForFork[secondFork]);
        pthread_mutex_lock(&waitForThinking);
        std::cout << "Filozof " << id << " odlozyl widelec ";
        std::cout << secondFork << "\n";
        pthread_mutex_unlock(&waitForThinking);

        pthread_mutex_unlock(&waitForFork[firstFork]);
        pthread_mutex_lock(&waitForThinking);
        std::cout << "Filozof " << id << " odlozyl widelec " << firstFork;
        std::cout << " i ponownie mysli" <<"\n";
        pthread_mutex_unlock(&waitForThinking);
    }
}

int main(int argc, const char * argv[]) {
    amountOfPhilosophers = std::stoi(argv[1]);
    std::cout << "Liczba filozofów: " << amountOfPhilosophers << std::endl;

    std::vector<pthread_t> philosophersThread(amountOfPhilosophers);
    std::vector<int> ids(amountOfPhilosophers);
    waitForFork = new pthread_mutex_t[amountOfPhilosophers];

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
