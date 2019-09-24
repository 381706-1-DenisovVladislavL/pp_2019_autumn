// Copyright 2019 Denisov Vladislav
#include <mpi.h>
#include <random>
#include <ctime>
#include <stdexcept>
#include <string>
#include "../../../modules/task_1/denisov_v_count_frequency_char_in_str/count_frequency_char_in_str.h"

//static int offset = 0;

void getRandomStr(int strSize) {
}

int getCountFreqCharInStr(std::string str, char ch) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = str.length() / size;
    const int remainder = str.length() % size;

    if (rank == 0) {
        for (int proc = 1; proc < size; ++proc) {
            if (delta > 0) {
                MPI_Send(&str[remainder] + proc * delta, delta, MPI_CHAR, proc, 1, MPI_COMM_WORLD);
                MPI_Send(&ch, 1, MPI_CHAR, proc, 2, MPI_COMM_WORLD);
            }
        }
    }

    std::string strLocal;
    char chLocal;

    if (rank == 0) {
        for (int i = 0; i < delta + remainder; i++) {
            strLocal += str[i];
        }
        chLocal = ch;
    } else {
        MPI_Status status;
        if (delta > 0) {
            MPI_Recv(&strLocal, delta, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&chLocal, delta, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        }
    }

    int count = 0;
    for (int i = 0; i <= static_cast<int>(strLocal.length()); i++) {
        if (strLocal[i] == chLocal)
            count++;
    }

    if (rank == 0) {
        for (int proc = 1; proc < size; ++proc) {
            int temp;
            MPI_Status status;
            MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
            count += temp;
        }
    } else {
        MPI_Send(&count, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    return count;
}
