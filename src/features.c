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

void first_pixel(char *source_path) {
    unsigned char *data = NULL;
    const char *filename = source_path;

    int r = data[0];
    int g = data[1];
    int b = data[2];
    
    printf("first_pixel: %d, %d, %d\n", r, g, b);

    free(data);
}
void dimension (char *source_path){
    unsigned char* data;
    int width, height, channel_count;
    const char *filename= source_path; 
   /* int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count);*/
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("Dimensions : %d, %d\n", width , height);

}
