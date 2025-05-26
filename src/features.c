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

void stat_report (char *source_path){
    unsigned char *data = NULL;
    int width, height, channels;
    int size;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        fprintf(stderr, "Erreur de lecture de l'image : %s\n", source_path);
        return;
    }

    size = width * height * channels;

    int max_pixel = 0;
    int min_pixel = 255;
    int max_r = 0, max_g = 0, max_b = 0;
    int min_r = 255, min_g = 255, min_b = 255;

    for (int i = 0; i < size; i += channels) {
        int r = data[i];
        int g = data[i + 1];
        int b = data[i + 2];
        int pixel_intensity = (r + g + b) / 3;

        // Max / min sur l'intensité du pixel
        if (pixel_intensity > max_pixel) max_pixel = pixel_intensity;
        if (pixel_intensity < min_pixel) min_pixel = pixel_intensity;

        // Composantes
        if (r > max_r) max_r = r;
        if (g > max_g) max_g = g;
        if (b > max_b) max_b = b;

        if (r < min_r) min_r = r;
        if (g < min_g) min_g = g;
        if (b < min_b) min_b = b;
    }

    FILE *out = fopen("stat_report.txt", "w");
    if (out == NULL) {
        fprintf(stderr, "Erreur : impossible de créer stat_report.txt\n");
        free(data);
        return;
    }

    fprintf(out, "max_pixel: %d\n\n", max_pixel);
    fprintf(out, "min_pixel: %d\n\n", min_pixel);
    fprintf(out, "max_component R: %d\n\n", max_r);
    fprintf(out, "max_component G: %d\n\n", max_g);
    fprintf(out, "max_component B: %d\n\n", max_b);
    fprintf(out, "min_component R: %d\n\n", min_r);
    fprintf(out, "min_component G: %d\n\n", min_g);
    fprintf(out, "min_component B: %d\n", min_b);

    printf("fichier cree");

    fclose(out);
    free(data);
}
