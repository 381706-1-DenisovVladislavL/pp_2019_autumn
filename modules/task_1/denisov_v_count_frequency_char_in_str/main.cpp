// Copyright 2019 Denisov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <stdio.h>
#include <cstring>
#include "./count_frequency_char_in_str.h"

TEST(Count_frequency_char_in_str, Test_Name_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char str[] = "aababas";
    char ch = 'a';

    int count = getCountFreqCharInStr(str, ch);

    if (rank == 0) {
        int seqCount = 0;
        int length = strlen(str);
        for (int i = 0; i < length; ++i) {
            if (str[i] == ch)
                seqCount++;
        }
        ASSERT_EQ(seqCount, count);
    }
}

TEST(Count_frequency_char_in_str, Test_Name_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = 10;
    char *str = new char[size];
    ASSERT_NO_THROW(getRandomStr(str, size));

    if (rank == 0) {
        int length = strlen(str);
        std::cout << "Size: " << size << " Len: " << length << " Str: ";
        for (int i = 0; i < length; ++i) {
            std::cout << str[i];
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
