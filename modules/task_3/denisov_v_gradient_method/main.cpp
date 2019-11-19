// Copyright 2019 Denisov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./gradient_method.h"

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
