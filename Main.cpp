// Copyright 2025 Maks
#include <pthread.h>
#include <iostream>
#include <thread>

pthread_mutex_t* waitForFork;
int amountOfPhilosophers;

void *philosopher(void *arg) {
    int id = *reinterpret_cast<int*>(arg);
    int firstFork = std::min(id, (id + 1) % amountOfPhilosophers);
    int secondFork = std::max(id, (id + 1) % amountOfPhilosophers);

    while (true) {
        std::cout << "Filozof numer: " << id << " myśli\n";

        std::this_thread::sleep_for(std::chrono::seconds(8));

        pthread_mutex_lock(&waitForFork[firstFork]);
        std::cout << "Filozof " << id << " wzial widelec " << firstFork << "\n";
        pthread_mutex_lock(&waitForFork[secondFork]);
        std::cout << "Filozof " << id << " wzial widelec " << secondFork << " i zaczal jesc" << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(16));

        pthread_mutex_unlock(&waitForFork[secondFork]);
        std::cout << "Filozof " << id << " odlozyl widelec " << secondFork << "\n";
        pthread_mutex_unlock(&waitForFork[firstFork]);
        std::cout << "Filozof " << id << " odlozyl widelec " << firstFork << " i ponownie mysli" <<"\n";
    }
}

int main(int argc, const char * argv[]) {
    amountOfPhilosophers = std::stoi(argv[1]);
    std::cout << "Liczba filozofów: " << amountOfPhilosophers << std::endl;

    pthread_t philosophersThread[amountOfPhilosophers];
    int ids[amountOfPhilosophers];
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
