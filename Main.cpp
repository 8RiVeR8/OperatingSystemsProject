// Copyright 2025 Maks
#include <pthread.h>
#include <iostream>
#include <thread>

void *test(void *arg) {
    int id = *reinterpret_cast<int*>(arg);
    std::cout << "Filozof numer: " << id << " myśli\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return nullptr;
}

int main(int argc, const char * argv[]) {
    const int AMOUNT_OF_PHILOSOPHERS = std::stoi(argv[1]);
    std::cout << "Liczba filozofów: " << AMOUNT_OF_PHILOSOPHERS << std::endl;
    pthread_t philosophersThread[AMOUNT_OF_PHILOSOPHERS];
    int ids[AMOUNT_OF_PHILOSOPHERS];

    for (int i = 0; i < AMOUNT_OF_PHILOSOPHERS; ++i) {
        ids[i] = i;
        pthread_create(&philosophersThread[i], nullptr, &test, &ids[i]);
    }

    for (int i = 0; i < AMOUNT_OF_PHILOSOPHERS; ++i) {
        pthread_join(philosophersThread[i], nullptr);
    }

    return 0;
}
