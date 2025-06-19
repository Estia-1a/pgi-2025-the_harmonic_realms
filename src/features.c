#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"
#include <stdlib.h>

#include <limits.h>
#include <ctype.h>
#include <math.h>


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
    printf("tenth_pixel : %d, %d, %d\n", data[27],data[28], data[29] );
}

void min_component(char *source_path, char component)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    char comp_upper = toupper(component);
    int channel_offset;
    if (comp_upper =='R') channel_offset = 0;
    else if (comp_upper =='G') channel_offset =1;
    else if (comp_upper =='B') channel_offset =2;
    int min_value = 256;
    int min_x = 0, min_y = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * channel_count +channel_offset;
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
    char comp_upper =toupper(component);
    if (comp_upper =='R')
    {
        component_offset =0;
    }
    else if (comp_upper == 'G')
    {
        component_offset =1;
    }
    else if (comp_upper =='B')
    {
        component_offset =2;
    }
    unsigned char max_value =0;
    int max_x = 0, max_y = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pixel_index = (y * width + x) * channel_count;
            unsigned char current_value = data[pixel_index + component_offset];
            if (current_value > max_value ||
                (current_value ==max_value && (y < max_y|| (y ==max_y && x < max_x))))
            {
                max_value =current_value;
                max_x =x;
                max_y =y;
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
    if (data !=NULL)
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
    min_sum = 255 * 3 +1;
    min_x = 0;
    min_y = 0;
    pixelRGB *pixel = NULL;
    for (y =0; y < height; y++)
    {
        for (x = 0; x <width; x++)
        {
            pixelRGB *pixel_lu =get_pixel(data, width, height, channel_count, x, y);
            if (pixel_lu != NULL)
            {
                sum = pixel_lu->R + pixel_lu->G + pixel_lu->B;
                if (sum <min_sum)
                {
                    min_sum =sum;
                    min_x =x;
                    min_y =y;
                    pixel =pixel_lu;
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
    max_sum = -1;
    max_x = 0;
    max_y = 0;
    pixelRGB *pixel = NULL;
    for (y = 0; y< height; y++)
    {
        for (x =0; x < width; x++)
        {
            pixelRGB *pixel_lu =get_pixel(data, width, height, channel_count, x, y);
            if (pixel_lu != NULL)
            {
                sum= pixel_lu->R + pixel_lu->G + pixel_lu->B;
                if (sum > max_sum)
                {
                    max_sum =sum;
                    max_x =x;
                    max_y =y;
                    pixel =pixel_lu;
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
    size = width * height * channels;
    int max_pixel = 0;
    int min_pixel = 255;
    int max_r =0, max_g= 0, max_b = 0;
    int min_r =255, min_g= 255, min_b = 255;
    for (int i =0; i < size; i += channels) {
        int r =data[i];
        int g =data[i +1];
        int b =data[i +2];
        int pixel_intensity = (r + g + b) / 3;
        if (pixel_intensity > max_pixel) max_pixel =pixel_intensity;
        if (pixel_intensity < min_pixel) min_pixel =pixel_intensity;
        if (r > max_r) max_r =r;
        if (g > max_g) max_g =g;
        if (b > max_b) max_b =b;
        if (r < min_r) min_r =r;
        if (g < min_g) min_g =g;
        if (b < min_b) min_b =b;
    }
    FILE *out = fopen("stat_report.txt", "w");
    fprintf(out, "max_pixel: %d\n\n", max_pixel);
    fprintf(out, "min_pixel: %d\n\n", min_pixel);
    fprintf(out, "max_component R: %d\n\n",max_r);
    fprintf(out, "max_component G: %d\n\n",max_g);
    fprintf(out, "max_component B: %d\n\n", max_b);
    fprintf(out, "min_component R: %d\n\n",min_r);
    fprintf(out, "min_component G: %d\n\n", min_g);
    fprintf(out, "min_component B: %d\n", min_b);
    printf("fichier cree");
    fclose(out);
    free(data);
}

void color_invert(char *source_path, char *dest_path) {
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
   for (int y =0; y<height ; y++){
        for(int x =0 ; x<width; x++){
            int i = (y*width +x) * channel_count;
            data[i]=255 -data[i];
            data[i+1]= 255 -data[i+1];
            data[i+2]= 255 -data[i+2];
        }
   }
   write_image_data("image_out.bmp", data, width, height);
   free_image_data(data);
}

void color_red(char *source_path, char *dest_path)
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
            if (pixel !=NULL)
            {
                pixel->G =0;
                pixel->B =0;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_blue(char *source_path,char *dest_path )
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    pixelRGB *pixel = NULL;
    for (int y =0; y <height; y++)
    {
        for (int x =0; x <width; x++)
        {
            pixel = get_pixel(data, width, height, channel_count, x, y);
            if (pixel != NULL)
            {
                pixel->R =0;
                pixel->G =0;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_green(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    pixelRGB *pixel =NULL;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixel = get_pixel(data, width, height, channel_count, x, y);
            if (pixel != NULL)
            {
                pixel->R =0;
                pixel->B =0;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_desaturate(char *source_path, char *dest_path) {
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channel_count;
            unsigned char R =data[index];
            unsigned char G =data[index +1];
            unsigned char B =data[index +2];
            unsigned char min_val =R;
            if (G < min_val) min_val =G;
            if (B < min_val) min_val =B;
            unsigned char max_val =R;
            if (G > max_val) max_val =G;
            if (B > max_val) max_val =B;
            unsigned char new_val =(min_val + max_val) /2;
            data[index] = new_val;
            data[index +1] =new_val;
            data[index +2] =new_val;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_gray(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    pixelRGB *pixel = NULL;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixel =get_pixel(data, width, height, channel_count, x, y);
            if (pixel != NULL)
            {
                unsigned char value = (pixel->R +pixel->G +pixel->B) / 3;
                pixel->R =value;
                pixel->G =value;
                pixel->B =value;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_gray_luminance(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned int idx = (y * width + x) *channel_count;
            unsigned char R =data[idx];
            unsigned char G =data[idx +1];
            unsigned char B =data[idx +2];
            int gray = (int)(0.299 *R +0.587 *G +0.114 *B);
            if (gray > 255) {
                gray = 255;
                } 
            else {
                if (gray < 0) {
                    gray = 0;
                    } 
                else {
                    gray = gray;
                    }
                }
            data[idx] = gray;
            data[idx + 1] = gray;
            data[idx + 2] = gray;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void mirror_total(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    unsigned char *mirrored_data =malloc(width *height *channel_count);
    for (int y = 0; y <height; y++) {
        for (int x = 0; x < width; x++) {
            int src_idx = (y * width + x) *channel_count;

            int mirrored_x =width -1 -x;
            int mirrored_y =height -1 -y;
            int dst_idx = (mirrored_y *width +mirrored_x) *channel_count;

            for (int c = 0; c <channel_count; c++) {
                mirrored_data[dst_idx + c] = data[src_idx +c];
            }
        }
    }
    write_image_data(dest_path, mirrored_data, width, height);
    free(data);
    free(mirrored_data);
}

void mirror_vertical(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    unsigned char *mirrored = malloc(width * height * channel_count);
    for (int y = 0; y <height; y++) {
        int mirrored_y = height-1-y;
        for (int x = 0; x < width; x++) {
            for (int c = 0; c <channel_count; c++) {
                int src_idx = (y *width +x) *channel_count +c;
                int dst_idx =(mirrored_y *width + x) *channel_count +c;
                mirrored[dst_idx] =data[src_idx];
            }
        }
    }
    write_image_data(dest_path, mirrored, width, height);
    free(data);
    free(mirrored);
}

void mirror_horizontal(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    unsigned char *mirrored = malloc(width * height * channel_count);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int mirrored_x = width - 1 - x;
            for (int c = 0; c < channel_count; c++) {
                int src_idx = (y * width + x) * channel_count + c;
                int dst_idx = (y * width + mirrored_x) * channel_count + c;
                mirrored[dst_idx] = data[src_idx];
            }
        }
    }
    write_image_data(dest_path, mirrored, width, height);
    free(data);
    free(mirrored);
}

void rotate_acw(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int new_width =height;
    int new_height =width;
    unsigned char *rotated = malloc(new_width * new_height *channel_count);
    for (int y = 0; y < height; y++) {
        for (int x =0; x < width; x++) {
            for (int c =0; c <channel_count; c++) {
                int src_idx= (y *width +x) *channel_count +c;
                int dst_idx= ((width -1 -x) *new_width +y) *channel_count +c;
                rotated[dst_idx] =data[src_idx];
            }
        }
    }
    write_image_data(dest_path, rotated, new_width, new_height);
    free(data);
    free(rotated);
}

void rotate_cw(char *source_path, char *dest_path)
{
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int new_width = height;
    int new_height = width;
    unsigned char *rotated = malloc(new_width * new_height * channel_count);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channel_count; c++) {
                int src_idx = (y *width +x) *channel_count +c;
                int dst_idx = (x *new_width + (new_width - 1 - y)) * channel_count +c;
                rotated[dst_idx] =data[src_idx];
            }
        }
    }
    write_image_data(dest_path, rotated, new_width, new_height);
    free(data);
    free(rotated);
}

void scale_bilinear(char *source_path, float scale) {
    unsigned char *data;
    int width, height, channels;
    read_image_data(source_path, &data, &width, &height, &channels);
    int new_width = (int)(width * scale);
    int new_height = (int)(height * scale);
    unsigned char *new_data = malloc(new_width * new_height * channels);
    for (int y_out = 0; y_out < new_height; y_out++) {
        for (int x_out = 0; x_out < new_width; x_out++) {
            float x_in = x_out / scale;
            float y_in = y_out / scale;
            int x1 = (int)floorf(x_in);
            int x2 = x1 + 1;
            int y1 = (int)floorf(y_in);
            int y2 = y1 + 1;
            float dx = x_in - x1;
            float dy = y_in - y1;
            if (x2 >=width) x2 =width - 1;
            if (y2 >=height) y2 =height - 1;
            if (x1 >=width) x1 =width - 1;
            if (y1 >=height) y1 =height - 1;
            for (int c = 0; c < channels; c++) {
                int index_q11 = (y1 *width +x1) * channels + c;
                int index_q12 = (y2 *width +x1) * channels + c;
                int index_q21 = (y1 *width +x2) * channels + c;
                int index_q22 = (y2 *width +x2) * channels + c;
                float Q11 =data[index_q11];
                float Q12 =data[index_q12];
                float Q21 =data[index_q21];
                float Q22 =data[index_q22];
                float value = Q11 * (1 -dx) * (1 -dy) +
                              Q21 * dx * (1 -dy) +
                              Q12 * (1 -dx) *dy +
                              Q22 * dx * dy;
                new_data[(y_out * new_width + x_out) * channels + c] = (unsigned char)value;
            }
        }
    }

    write_image_data("image_out.bmp", new_data, new_width, new_height);

    free(data);
    free(new_data);
}

void scale_nearest(char *source_path, float scale) {
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int new_width = (int)(width * scale);
    int new_height = (int)(height * scale);
    unsigned char *new_data = malloc(new_width * new_height * channel_count);
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = (int)(x / scale);
            int src_y = (int)(y / scale);
            for (int c = 0; c < channel_count; c++) {
                new_data[(y * new_width + x) * channel_count + c] =
                    data[(src_y * width + src_x) * channel_count + c];
            }
        }
    }
    write_image_data("image_out.bmp", new_data, new_width, new_height);
    free(data);
    free(new_data);
}

void scale_crop(char *source_path, int center_x, int center_y, int crop_width, int crop_height) {
    unsigned char *data;
    int width, height, channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    int start_x = center_x - crop_width / 2;
    int start_y = center_y - crop_height / 2;
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (start_x + crop_width > width) crop_width = width - start_x;
    if (start_y + crop_height > height) crop_height = height - start_y;
    unsigned char *new_data = malloc(crop_width * crop_height * channel_count);
    for (int y = 0; y < crop_height; y++) {
        for (int x = 0; x < crop_width; x++) {
            for (int c = 0; c < channel_count; c++) {
                new_data[(y * crop_width + x) * channel_count + c] =
                    data[((start_y + y) * width + (start_x + x)) * channel_count + c];
            }
        }
    }
    write_image_data("image_out.bmp", new_data, crop_width, crop_height);
    free(data);
    free(new_data);
}

