#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>

/*
 * array: 1 dim
 * table: 2 dim
 * matrix: 3 dim
 */

typedef float data_t;

// A voir...
typedef struct {
    data_t*** array;
    int x, y, z;
} matrix_t;

data_t*** add_mask(data_t*** matrix, int x, int y, int z);
void sub_mask(data_t*** matrix, data_t*** random, int x, int y, int z);

data_t*** init_matrix(int x, int y, int z);
data_t** init_table(int x, int y);
data_t* init_array(int x);
void free_matrix(data_t*** matrix, int x, int y);
void free_table(data_t** table, int x);
void free_array(data_t* array);

void print_matrix(data_t*** matrix, int x, int y, int z);
void print_table(data_t** table, int x, int y);
void print_array(data_t* array, int x);

void add_matrix(data_t*** matrix, data_t*** add, int x, int y, int z);
void sub_matrix(data_t*** matrix, data_t*** sub, int x, int y, int z);
void rand_matrix(data_t*** rand, int x, int y, int z);
void relu_matrix(data_t*** matrix, int x, int y, int z);
void flatten_matrix(data_t*** matrix, data_t* array, int x, int y, int z, bool forward);
// TODO: utiliser la matrice (pour faire comme dans les autres fonctions)
void average_pool(data_t*** matrix, data_t*** average, int table_x, int table_y, int table_z, int average_x, int average_y, int average_z, int win_x, int win_y);
void softmax(data_t* array, int x);

int main(void){

    /*
    int table_x = 2;
    int table_y = 2;
    int z = 2;

    data_t*** data = init_matrix(table_x, table_y, z);
    for (int i = 0; i < table_x; i++){
        for (int j = 0; j < table_y; j++){
            for (int k = 0; k < z; k++){
                data[i][j][k] = i+j+k;
            }
        }
    }

    data_t* array = init_array(table_x * table_y * z);
    flatten_matrix(data, array, table_x, table_y, z, true);
    print_array(array, table_x * table_y * z);

    print_matrix(data, table_x, table_y, z);
    data_t*** random = add_mask(data, table_x, table_y, z);
    print_matrix(data, table_x, table_y, z);
    sub_mask(data, random, table_x, table_y, z);
    print_matrix(data, table_x, table_y, z);

    free(data);

     */

    /*

    int table_x = 6;
    int table_y = 6;
    int table_z = 1;
    int win_x = 2;
    int win_y = 2;
    int average_x = table_x / win_x;
    int average_y = table_x / win_y;
    int average_z = table_z;

    data_t ***table = init_matrix(table_x, table_y, table_z);
    for (int k = 0; k < table_z; ++k) {
        for (int i = 0; i < table_x; ++i) {
            for (int j = 0; j < table_y; ++j) {
                table[i][j][k] = 2;
            }
        }
    }

    data_t*** average = init_matrix(average_x, average_y, average_z);

    average_pool(table, average, table_x, table_y, table_z, average_x, average_y, average_z, win_x, win_y);

    print_matrix(table, table_x, table_y, table_z);
    printf("\n");
    print_matrix(average, average_x, average_y, average_z);

    free_matrix(table, table_x, table_y);
    free_matrix(average, average_x, average_y);

     */

    /*

    int x = 3;
    data_t* data = init_array(x);
    data[0] = 1;
    data[1] = 3;
    data[2] = 2;
    print_array(data, x);
    printf("\n\n");
    softmax(data, x);
    print_array(data, x);

     */

    int x = 16;
    int y = 16;
    int z = 16;

    int win_x = 1;
    int win_y = 1;

    int average_x = x / win_x;
    int average_y = y / win_y;
    int average_z = z;
    
    int flat_x = x * y * z;

    data_t*** data = init_matrix(x, y, z);
    data_t*** average = init_matrix(average_x, average_y, average_z);
    data_t* flat = init_array(flat_x);

    //conv'
    //GO TEE
    //linear transfo = anti conv'
    //ReLU+Batchnorm

    for (int i = 0; i < 100; ++i) {
        data_t ***mask = add_mask(data, x, y, z);
        //OUT TEE --> conv'
        //GO TEE
        //Linear transfo = anti conv'
        sub_mask(data, mask, x, y, z);
        relu_matrix(data, x, y, z);
        // BatchNorm
    }

    average_pool(data, average, x, y, z, average_x, average_y, average_z, win_x, win_y);
    flatten_matrix(average, flat, x, y, z, true);
    // Dense
    softmax(flat, flat_x);

    free_array(flat);
    free_matrix(average, average_x, average_y);
    free_matrix(data, x, y);

    return 0;
}

data_t*** add_mask(data_t*** matrix, int x, int y, int z){
    data_t*** random = init_matrix(x, y, z);
    rand_matrix(random, x, y, z);
    add_matrix(matrix, random, x, y, z);
    return random;
}

void sub_mask(data_t*** matrix, data_t*** random, int x, int y, int z){
    sub_matrix(matrix, random, x, y, z);
    free(random);
}

data_t*** init_matrix(int x, int y, int z){
    data_t*** matrix = malloc(sizeof(data_t***) * x * y * z);
    for (int i = 0; i < x; ++i) {
        matrix[i] = malloc(sizeof(data_t**) * y * z);
        for (int j = 0; j <y; ++j) {
            matrix[i][j] = malloc(sizeof(data_t *) * z);
        }
    }
    return matrix;
}

data_t** init_table(int x, int y){
    data_t** table = malloc(sizeof(data_t**) * x * y);
    for (int i = 0; i < x; ++i){
        table[i] = malloc(sizeof(data_t*) * y);
    }
    return table;
}

data_t* init_array(int x){
    return malloc(sizeof(data_t) * x);
}

void free_matrix(data_t*** matrix, int x, int y){
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

void free_table(data_t** table, int x){
    for (int i = 0; i < x; ++i) {
        free(table[i]);
    }
    free(table);
}

void free_array(data_t* array){
    free(array);
}

void print_matrix(data_t*** matrix, int x, int y, int z){
    printf("\n");
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("%d %d %d\t %f\n", i, j, k, matrix[i][j][k]);
            }
        }
    }
}

void print_table(data_t** table, int x, int y){
    printf("\n");
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; j++) {
            printf("%d %d\t %f\n", i, j, table[i][j]);
        }
    }
}

void print_array(data_t* array, int x){
    for (int i = 0; i < x; i++){
        printf("%f ", array[i]);
    }
}

void rand_matrix(data_t*** random, int x, int y, int z){
    srand(time(NULL));
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for (int k = 0; k < z; k++){
                random[i][j][k] = rand();
            }
        }
    }
}

void add_matrix(data_t*** matrix, data_t*** add, int x, int y, int z){
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                matrix[i][j][k] = matrix[i][j][k] + add[i][j][k];
            }
        }
    }
}

void sub_matrix(data_t*** matrix, data_t*** sub, int x, int y, int z){
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                matrix[i][j][k] = matrix[i][j][k] - sub[i][j][k];
            }
        }
    }
}

void relu_matrix(data_t*** matrix, int x, int y, int z){
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                if (matrix[i][j][k] < 0){
                    matrix[i][j][k] = 0;
                }
                if (matrix[i][j][k] > 6){
                    matrix[i][j][k] = 6;
                }
            }
        }
    }
}

void flatten_matrix(data_t*** matrix, data_t* array, int x, int y, int z, bool forward){
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int pos = i + x * j + k * x * y;
                if (forward)
                    array[pos] = matrix[i][j][k];
                else
                    matrix[i][j][k] = array[pos];
            }
        }
    }
}

void average_pool(data_t*** matrix, data_t*** average, int table_x, int table_y, int table_z, int average_x, int average_y, int average_z, int win_x, int win_y) {
    //Width must be divisible by X

    for (int i = 0; i < average_x; ++i) {
        for (int j = 0; j < average_y; ++j) {
            for (int k = 0; k < average_z; ++k) {
                average[i][j][k] = 0;
            }
        }
    }

    for (int k = 0; k < table_z; ++k) {
        for (int i = 0; i < table_x; i += win_x) {
            for (int j = 0; j < table_y; j += win_y) {
                for (int a = 0; a < win_x; ++a) {
                    for (int b = 0; b < win_y; ++b) {
                        average[i / win_x][j / win_y][k] += matrix[i + a][j + b][k];
                    }
                }
            }
        }
    }

    for (int k = 0; k < average_z; ++k) {
        for (int i = 0; i < average_x; ++i) {
            for (int j = 0; j < average_y; ++j) {
                average[i][j][k] = average[i][j][k] / (win_x * win_y);
            }
        }
    }
}

void softmax(data_t* array, int x){
    data_t sum = 0;
    for (int i = 0; i < x; i++){
        sum += (data_t) exp(array[i]);
        array[i] = (data_t) exp(array[i]);
    }

    for (int i = 0; i < x; ++i) {
        array[i] = array[i] / sum;
    }
}