// Copyright 2019 Denisov Vladislav
#include <mpi.h>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include "../../../modules/task_2/denisov_v_matrix_mult_horiz_schem_only_A/matrix_mult_horiz_schem_only_A.h"

std::vector <int> createRandomMatrix(int sizeSide) {
    if (sizeSide <= 0)
        throw "Error size of matrix";

    std::mt19937 generator;
    generator.seed(static_cast<unsigned int>(time(0)));

    int sizeVector = sizeSide * sizeSide;
    std::vector <int> matrix(sizeVector);
    for (auto i = 0; i < sizeVector; i++)
        matrix[i] = generator() % 10;

    return matrix;
}

std::vector<int> getMatrixMultSeq(std::vector<int> matrixA, std::vector<int> matrixB, int sizeSide) {
    if (sizeSide <= 0)
        throw "Error size of matrix";

    int sizeVector = sizeSide * sizeSide;
    if (matrixA.size() != static_cast<int>(sizeVector) || matrixB.size() != static_cast<int>(sizeVector))
        throw "One or both matrices do not exist";

    if (matrixA.size() != matrixB.size())
        throw "These 2 matrices cannot be multiplied.";

    std::vector<int> matrixResult(sizeVector);

    for (auto i = 0; i < sizeSide; ++i) {
        for (auto j = 0; j < sizeSide; ++j) {
            matrixResult[i * sizeSide + j] = 0;
            for (auto k = 0; k < sizeSide; ++k) {
                matrixResult[i * sizeSide + j] += matrixA[i * sizeSide + k] * matrixB[k * sizeSide + j];
            }
        }
    }

    return matrixResult;
}

// std::vector<int> getMatrixMultPar(std::vector<int> matrixA, std::vector<int> matrixB, int sizeSide) {
// }

void printMatrix(std::vector<int> matrix, int sizeSide) {
    std::cout << "\nPrint Matrix:" << std::endl;

    if (sizeSide > 10) {
        std::cout << "The matrix is too large to display on the console." << std::endl << std::endl;
        return;
    }

    for (auto i = 0; i < sizeSide; ++i) {
        for (auto j = 0; j < sizeSide; ++j) {
            std::cout << matrix[i * sizeSide + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
