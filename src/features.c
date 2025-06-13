#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"
#include <stdlib.h>

#include <limits.h>
#include <ctype.h>


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
void min_component(char *source_path, char component){
    unsigned char *data;
    int width, height, channel_count;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    char comp_upper = toupper(component);
    int channel_offset;

    if (comp_upper == 'R') channel_offset = 0;
    else if (comp_upper == 'G') channel_offset = 1;
    else if (comp_upper == 'B') channel_offset = 2;
    else {
        printf("Erreur: Composante invalide. Utilisez R, G ou B.\n");
        free(data);
        return;
    }

    int min_value = 256;
    int min_x = 0, min_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channel_count + channel_offset;
            int value = data[index];
            if (value < min_value) {
                min_value = value;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_component %c (%d, %d): %d\n", comp_upper, min_x, min_y, min_value);
    free(data);
}


