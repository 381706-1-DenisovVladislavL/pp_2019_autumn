// Copyright 2019 Denisov Vladislav
#include <mpi.h>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include "../../../modules/task_3/denisov_v_gradient_method/gradient_method.h"

std::vector<double> createRandomMatrix(int sizeSide) {
    if (sizeSide <= 0)
        throw "Error size of matrix";

    std::default_random_engine generator;
    generator.seed(static_cast<unsigned int>(time(0)));

    int sizeVector = sizeSide * sizeSide;
    std::vector <double> matrix(sizeVector);
    for (int i = 0; i < sizeSide; ++i) {
        for (int j = i; j < sizeSide; ++j) {
            matrix[i * sizeSide + j] = matrix[j * sizeSide + i] = generator() % 10;
        }
    }

    return matrix;
}

std::vector<double> createRandomVector(int size) {
    if (size <= 0)
        throw "Error size of vector";

    std::default_random_engine generator;
    generator.seed(static_cast<unsigned int>(time(0)));

    std::vector <double> vector(size);
    for (int i = 0; i < size; ++i) {
        vector[i] = generator() % 10 + 1;
    }

    return vector;
}

void printMatrix(std::vector<double> matrix, int size) {
    std::cout << "\nPrint Matrix:" << std::endl;

    if (size > 10) {
        std::cout << "The matrix is too large to display on the console." << std::endl << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printVector(std::vector<double> vector, int size) {
    std::cout << "\nPrint Vector:" << std::endl;

    if (size > 10) {
        std::cout << "The vector is too large to display on the console." << std::endl << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << vector[i] << std::endl;
    }
}

void printSystem(std::vector<double> matrix, std::vector<double> vector, int size) {
    std::cout << "\nPrint System:" << std::endl;

    if (size > 10) {
        std::cout << "The system is too large to display on the console." << std::endl << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j] << " ";
        }
        std::cout << "| "<< vector[i] << std::endl;
    }
    std::cout << std::endl;
}

double vectorMult(const std::vector<double>& vectorA, const std::vector<double>& vectorB) {
    double res = 0.0;
    for (size_t i = 0; i < vectorA.size(); ++i)
        res += vectorA[i] * vectorB[i];

    return res;
}

std::vector<double> matrixVectorMult(const std::vector<double>& matrix, const std::vector<double>& vector) {
    std::vector<double> res(vector.size());
    for (size_t i = 0; i < vector.size(); ++i) {
        res[i] = 0.0;
        for (size_t j = 0; j < vector.size(); ++j) {
            res[i] += matrix[i * vector.size() + j] * vector[j];
        }
    }

    return res;
}

std::vector<double> getSolveSeq(std::vector<double> matrix, std::vector<double> vector, int size) {
    int iters = 0;
    double eps = 0.1, beta = 0.0, alpha = 0.0, check = 0.0;

    std::vector<double> result(size);
    for (int i = 0; i < size; i++) {
        result[i] = 1;
    }

    std::vector<double> Ap = matrixVectorMult(matrix, result);
    std::vector<double> rprev(size), rnext(size);;
    for (int i = 0; i < size; i++)
        rprev[i] = vector[i] - Ap[i];

    std::vector<double> p(rprev);

    do {
        iters++;
        Ap = matrixVectorMult(matrix, p);
        alpha = vectorMult(rprev, rprev) / vectorMult(p, Ap);
        for (int i = 0; i < size; i++) {
            result[i] += alpha * p[i];
            rnext[i] = rprev[i] - alpha * Ap[i];
        }
        beta = vectorMult(rnext, rnext) / vectorMult(rprev, rprev);

        // Norma neviazki
        check = sqrt(vectorMult(rnext, rnext));
        
        for (int j = 0; j < size; j++)
            p[j] = beta * p[j] + rnext[j];

        rprev = rnext;
    } while ((check > eps) && (iters <= size));

    return result;
}
