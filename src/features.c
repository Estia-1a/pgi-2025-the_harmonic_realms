#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void dimension (char *source_path){
    unsigned char *data;
    int width, height, channel_count;
   /* int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count);*/
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("Dimensions : %d, %d\n", width , height);

}

void first_pixel (char *source_path){
    unsigned char *data;
    int width, height, channel_count; 
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("first_pixel : %d, %d, %d\n", data[0],data[1], data[2] );
}

void tenth_pixel (char *source_path){
    unsigned char *data;
    int width, height, channel_count; 
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("tenth_pixel : %d, %d, %d\n", data[27],data[28], data[29] );

}

void second_line(char *source_path) {
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int index_second_line = width * 3;
    printf("second_line: %d, %d, %d\n", data[index_second_line], data[index_second_line + 1], data[index_second_line + 2]);
}