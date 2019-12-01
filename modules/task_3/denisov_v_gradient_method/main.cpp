// Copyright 2019 Denisov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./gradient_method.h"

TEST(gradient_method, try_create_random_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sizeSide = 5;
    std::vector<double> matrix = createRandomMatrix(sizeSide);

    if (rank == 0) {
        printMatrix(matrix, sizeSide);
    }
}

TEST(gradient_method, try_create_random_vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size = 5;
    std::vector<double> vector = createRandomVector(size);

    if (rank == 0) {
        printVector(vector, size);
    }
}

TEST(gradient_method, seq_solve) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size = 10;
    std::vector<double> matrix = createRandomMatrix(size);
    std::vector<double> vector = createRandomVector(size);

    double startPar = MPI_Wtime();
    std::vector<double> resultPar = getSolvePar(matrix, vector, size);
    double endPar = MPI_Wtime();

    if (rank == 0) {
        printSystem(matrix, vector, size);
        double startSeq = MPI_Wtime();
        std::vector<double> resultSeq = getSolveSeq(matrix, vector, size);
        double endSeq = MPI_Wtime();
        std::cout << "Time seq: " << endSeq - startSeq << std::endl;
        printVector(resultSeq, size);

        std::cout << "Time par: " << endPar - startPar << std::endl;
        printVector(resultPar, size);

        for (size_t i = 0; i < resultSeq.size(); ++i)
            ASSERT_NEAR(resultSeq[i], resultPar[i], 0.05);
    }
}

// TEST(gradient_method, throw_when_create_random_matrix_with_negative_size) {
    // int rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // if (rank == 0) {
        // ASSERT_ANY_THROW(createRandomMatrix(-1));
    // }
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
