// Copyright 2019 Denisov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./matrix_mult_horiz_schem_only_A.h"

// TEST(matrix_mult_horiz_schem_only_A, test_1) {
    // int rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // char str[] = "aababas";
    // char ch = 'a';

    // int count = getCountFreqCharInStr(str, ch);

    // if (rank == 0) {
        // int seqCount = countFreqSeq(str, ch);
        // ASSERT_EQ(seqCount, count);
    // }
// }

TEST(matrix_mult_horiz_schem_only_A, test_print) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizeSide = 3;
    std::vector<int> matrix = createRandomMatrix(sizeSide);
    printMatrix(matrix, sizeSide);
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
