// Copyright 2019 Denisov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_mult_horiz_schem_only_A.h"

 TEST(matrix_mult_horiz_schem_only_A, test_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizeSide = 10;
    std::vector<int> matrixA = createRandomMatrix(sizeSide);
    std::vector<int> matrixB = createRandomMatrix(sizeSide);

    std::vector<int> resultPar = getMatrixMultPar(matrixA, matrixB, sizeSide);

    if (rank == 0) {
        std::vector<int> resultSeq = getMatrixMultSeq(matrixA, matrixB, sizeSide);
        ASSERT_EQ(resultSeq, resultPar);
    }
 }

// TEST(matrix_mult_horiz_schem_only_A, test_print) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int sizeSide = 3;
//    std::vector<int> matrix = createRandomMatrix(sizeSide);
//    printMatrix(matrix, sizeSide);
// }

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
