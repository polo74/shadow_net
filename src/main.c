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

typedef double data_t;

// not implemented yet
typedef struct {
    data_t*** array;
    int x, y, z;
} matrix_t;

data_t*** add_mask(data_t*** matrix, int x, int y, int z);
void sub_mask(data_t*** matrix, data_t*** random, int x, int y, int z);

data_t*** init_matrix(int x, int y, int z);
data_t** init_table(int x, int y);
data_t* init_array(int x);
void free_matrix(data_t*** matrix, int y, int z);
void free_table(data_t** table, int y);
void free_array(data_t* array);

void print_matrix(data_t*** matrix, int x, int y, int z);
void print_table(data_t** table, int x, int y);
void print_array(data_t* array, int x);

void add_matrix(data_t*** matrix, data_t*** add, int x, int y, int z);
void sub_matrix(data_t*** matrix, data_t*** sub, int x, int y, int z);
void rand_matrix(data_t*** rand, int x, int y, int z);
void relu_matrix(data_t*** matrix, int x, int y, int z);
void flatten_matrix(data_t*** matrix, data_t* array, int x, int y, int z, bool forward);
void average_pool(data_t*** matrix, data_t*** average, int table_x, int table_y, int table_z, int average_x, int average_y, int average_z, int win_x, int win_y);
void softmax(data_t* array, int x);

int main(void){


    srand(time(NULL));

    /*
    int table_x = 3;
    int table_y = 3;
    int table_z = 3;

    data_t*** data = init_matrix(table_x, table_y, table_z);
    for (int k = 0; k < table_z; k++){
        for (int j = 0; j < table_y; j++){
            for (int i = 0; i < table_x; i++){
                data[k][j][i] = 0;
            }
        }
    }

    data_t* array = init_array(table_x * table_y * table_z);
    flatten_matrix(data, array, table_x, table_y, table_z, true);
    print_array(array, table_x * table_y * table_z);

    print_matrix(data, table_x, table_y, table_z);
    data_t*** random = add_mask(data, table_x, table_y, table_z);
    print_matrix(data, table_x, table_y, table_z);
    sub_mask(data, random, table_x, table_y, table_z);
    print_matrix(data, table_x, table_y, table_z);

    free_matrix(data, table_x, table_y);
    free(array);

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
    for (int k = 0; k < table_z; k++) {
        for (int i = 0; i < table_x; i++) {
            for (int j = 0; j < table_y; j++) {
                table[k][j][i] = 2;
            }
        }
    }

    data_t*** average = init_matrix(average_x, average_y, average_z);

    average_pool(table, average, table_x, table_y, table_z, average_x, average_y, average_z, win_x, win_y);

    print_matrix(table, table_x, table_y, table_z);
    printf("\n");
    print_matrix(average, average_x, average_y, average_z);

    free_matrix(table, table_y, table_z);
    free_matrix(average, average_y, average_z);

     */

    /*

    int x = 3;
    data_t* data = init_array(x);
    data[0] = 1;
    data[1] = 3;
    data[2] = 2;
    print_array(data, x);
    printf("\n");
    softmax(data, x);
    print_array(data, x);

    */

    int x = 512;
    int y = 256;
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
    //linear transformation = anti conv'
    //ReLU+Batchnorm

    for (int i = 0; i < 100; i++) {
        data_t ***mask = add_mask(data, x, y, z);
        //OUT TEE --> conv'
        //GO TEE
        //Linear transformation = anti conv'
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
    free_matrix(random, y, z);
}

data_t*** init_matrix(int x, int y, int z){
    data_t*** matrix = malloc(sizeof(data_t***) * z * y * x);
    for (int k = 0; k < z; k++) {
        matrix[k] = malloc(sizeof(data_t**) * y * x);
        for (int j = 0; j <y; j++) {
            matrix[k][j] = malloc(sizeof(data_t *) * x);
        }
    }
    return matrix;
}

data_t** init_table(int x, int y){
    data_t** table = malloc(sizeof(data_t**) * x * y);
    for (int j = 0; j < y; j++){
        table[j] = malloc(sizeof(data_t*) * x);
    }
    return table;
}

data_t* init_array(int x){
    return malloc(sizeof(data_t) * x);
}

void free_matrix(data_t*** matrix, int y, int z){
    for (int k = 0; k < z; k++) {
        for (int j = 0; j <y; j++) {
            free(matrix[k][j]);
        }
        free(matrix[k]);
    }
    free(matrix);
}

void free_table(data_t** table, int y){
    for (int j = 0; j < y; j++) {
        free(table[j]);
    }
    free(table);
}

void free_array(data_t* array){
    free(array);
}

void print_matrix(data_t*** matrix, int x, int y, int z){
    printf("x y z\tvalue\n");
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                printf("%d %d %d\t %f\n", i, j, k, matrix[k][j][i]);
            }
        }
    }
}

void print_table(data_t** table, int x, int y){
    printf("\n");
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            printf("%d %d\t %f\n", i, j, table[i][j]);
        }
    }
}

void print_array(data_t* array, int x){
    for (int i = 0; i < x; i++){
        printf("%f\n", array[i]);
    }
}

void rand_matrix(data_t*** random, int x, int y, int z){
    for (int k = 0; k < z; k++){
        for (int j = 0; j < y; j++){
            for (int i = 0; i < x; i++){
                random[k][j][i] = rand() % 10;
            }
        }
    }
}

void add_matrix(data_t*** matrix, data_t*** add, int x, int y, int z){
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                matrix[k][j][i] = matrix[k][j][i] + add[k][j][i];
            }
        }
    }
}

void sub_matrix(data_t*** matrix, data_t*** sub, int x, int y, int z){
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                matrix[k][j][i] = matrix[k][j][i] - sub[k][j][i];
            }
        }
    }
}

void relu_matrix(data_t*** matrix, int x, int y, int z){
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                if (matrix[k][j][i] < 0){
                    matrix[k][j][i] = 0;
                }
                if (matrix[k][j][i] > 6){
                    matrix[k][j][i] = 6;
                }
            }
        }
    }
}

void flatten_matrix(data_t*** matrix, data_t* array, int x, int y, int z, bool forward){
    for (int k = 0; k < z; k++) {
        for (int j = 0; j < y; j++) {
            for (int i = 0; i < x; i++) {
                int pos = i + j * y + k * y * x;
                if (forward)
                    array[pos] = matrix[k][j][i];
                else
                    matrix[k][j][i] = array[pos];
            }
        }
    }
}

void average_pool(data_t*** matrix, data_t*** average, int table_x, int table_y, int table_z, int average_x, int average_y, int average_z, int win_x, int win_y) {
    //Width must be divisible by X

    for (int k = 0; k < average_z; k++) {
        for (int j = 0; j < average_y; j++) {
            for (int i = 0; i < average_x; i++) {
                average[k][j][i] = 0;
            }
        }
    }
// Todo
    for (int k = 0; k < table_z; k++) {
        for (int j = 0; j < table_y; j += win_y) {
            for (int i = 0; i < table_x; i += win_x) {
                for (int b = 0; b < win_y; ++b) {
                    for (int a = 0; a < win_x; ++a) {
                        average[k][j / win_y][i / win_x] += matrix[k][j + b][i + a];
                    }
                }
            }
        }
    }

    for (int k = 0; k < average_z; k++) {
        for (int j = 0; j < average_y; j++) {
            for (int i = 0; i < average_x; i++) {
                average[k][j][i] = average[k][j][i] / (win_x * win_y);
            }
        }
    }
}

void softmax(data_t* array, int x){
    data_t sum = 0;
    for (int i = 0; i < x; i++){
        sum += (data_t) exp(array[i]);
        array[i] = (data_t) exp(array[i]); // Todo: put it on the below 'for' loop
    }

    for (int i = 0; i < x; i++) {
        array[i] = array[i] / sum;
    }
}

data_t mean(data_t** table, int x, int y) {
    int n = x * y;
    int sum = 0;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            sum += table[i][j];
        }
    }
    return (1 / n) * sum;
}

void batchnorm(data_t*** matrix, int x, int y, int z) {
    for (int k = 0; k < z; k++) {
        data_t** table = matrix[z];
    }
}