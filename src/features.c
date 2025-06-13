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

void helloWorld()
{
    printf("Hello World !");
}

void dimension(char *source_path)
{
    unsigned char *data;
    int width, height, channel_count;
    /* int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count);*/
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("dimension : %d, %d\n", width, height);
}

void first_pixel(char *source_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("first_pixel : %d, %d, %d\n", data[0], data[1], data[2]);
}

void tenth_pixel(char *source_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("tenth_pixel : %d, %d, %d\n", data[27], data[28], data[29]);
}
void min_component(char *source_path, char component)
{
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

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * channel_count + channel_offset;
            int value = data[index];
            if (value < min_value)
            {
                min_value = value;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_component %c (%d, %d): %d\n", comp_upper, min_x, min_y, min_value);
    free(data);
}

void second_line(char *source_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int index_second_line = width * 3;
    printf("second_line: %d, %d, %d\n", data[index_second_line], data[index_second_line + 1], data[index_second_line + 2]);
}

void max_component(char *source_path, char component)
{
    unsigned char *data;
    int width, height, channel_count;

    read_image_data(source_path, &data, &width, &height, &channel_count);
    int component_offset;
    char comp_upper = toupper(component);

    if (comp_upper == 'R')
    {
        component_offset = 0;
    }
    else if (comp_upper == 'G')
    {
        component_offset = 1;
    }
    else if (comp_upper == 'B')
    {
        component_offset = 2;
    }
    else
    {
        printf("Erreur: Composante invalide. Utilisez R, G ou B.\n");
        free(data);
        return;
    }

    unsigned char max_value = 0;
    int max_x = 0, max_y = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pixel_index = (y * width + x) * channel_count;
            unsigned char current_value = data[pixel_index + component_offset];

            if (current_value > max_value ||
                (current_value == max_value && (y < max_y || (y == max_y && x < max_x))))
            {
                max_value = current_value;
                max_x = x;
                max_y = y;
            }
        }
    }

    printf("max_component %c (%d, %d): %d\n", comp_upper, max_x, max_y, max_value);

    free(data);
}

void print_pixel(char *filename, int x, int y)
{
    unsigned char *data = NULL;
    int width, height, channel_count;
    read_image_data(filename, &data, &width, &height, &channel_count);
    pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
    printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    if (data != NULL)
    {
        free(data);
    }
}

void min_pixel(char *source_path)
{
    int min_sum, min_x, min_y, y, x, sum;
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    min_sum = 255 * 3;
    min_x = 0;
    min_y = 0;
    pixelRGB *pixel = NULL;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pixelRGB *pixel_lu = get_pixel(data, width, height, channel_count, x, y);
            if (pixel_lu != NULL)
            {
                sum = pixel_lu->R + pixel_lu->G + pixel_lu->B;
                if (sum < min_sum)
                {
                    min_sum = sum;
                    min_x = x;
                    min_y = y;
                    pixel = pixel_lu;
                }
            }
        }
    }

    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, pixel->R, pixel->G, pixel->B);
}

void max_pixel(char *source_path)
{
    int max_sum, max_x, max_y, y, x, sum;
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    max_sum = 0;
    max_x = 0;
    max_y = 0;
    pixelRGB *pixel = NULL;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pixelRGB *pixel_lu = get_pixel(data, width, height, channel_count, x, y);
            if (pixel_lu != NULL)
            {
                sum = pixel_lu->R + pixel_lu->G + pixel_lu->B;
                if (sum > max_sum)
                {
                    max_sum = sum;
                    max_x = x;
                    max_y = y;
                    pixel = pixel_lu;
                }
            }
        }
    }

    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, pixel->R, pixel->G, pixel->B);
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

void color_red(char *source_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    
    pixelRGB *pixel = NULL;
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixel = get_pixel(data, width, height, channel_count, x, y);
            if (pixel != NULL)
            {
                pixel->G = 0;
                pixel->B = 0;
            }
        }
    }
    
    write_image_data("image_out.bmp", data, width, height);
}