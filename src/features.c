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
    printf("dimension : %d, %d\n", width , height);

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

void print_pixel( char *filename, int x, int y ){
    unsigned char *data= NULL;
    int width, height, channel_count;
    read_image_data(filename, &data, &width, &height, &channel_count);
    pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
    printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    if (data != NULL) {
        free(data);
    }
}

void min_pixel( char *source_path){
    int min_sum, min_x, min_y, y, x, sum;
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path,&data, &width, &height, &channel_count);
    min_sum = 255*3;
    min_x= 0;
    min_y = 0;
    pixelRGB *pixel = NULL;
        
    for (y=0; y<height; y++){
        for(x=0; x<width; x++){
            pixelRGB *pixel_lu = get_pixel(data, width, height, channel_count, x, y);
            if(pixel_lu != NULL){
                sum= pixel_lu->R +pixel_lu->G +pixel_lu->B;
                if (sum< min_sum){
                    min_sum = sum;
                    min_x = x;
                    min_y = y;
                    pixel = pixel_lu;
                }           
            }
        }
    }

    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, pixel->R, pixel->G, pixel->B );
}


void max_pixel( char *source_path){
    int max_sum, max_x, max_y, y, x, sum;
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path,&data, &width, &height, &channel_count);
    max_sum = 0;
    max_x= 0;
    max_y = 0;
    pixelRGB *pixel = NULL;
        
    for (y=0; y<height; y++){
        for(x=0; x<width; x++){
            pixelRGB *pixel_lu = get_pixel(data, width, height, channel_count, x, y);
            if(pixel_lu != NULL){
                sum= pixel_lu->R +pixel_lu->G +pixel_lu->B;
                if (sum> max_sum){
                    max_sum = sum;
                    max_x = x;
                    max_y = y;
                    pixel = pixel_lu;
                }           
            }
        }
    }

    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, pixel->R, pixel->G, pixel->B );
}

