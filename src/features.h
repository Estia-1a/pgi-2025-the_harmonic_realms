#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

void first_pixel(char *source_path);

void dimension (char *source_path);

void tenth_pixel (char *source_path);

void second_line(char *source_path);

void max_component(char *source_path, char component);

void min_component(char* source_path, char component);


void print_pixel( char *filename, int x, int y );

void min_pixel( char *filename );

void max_pixel( char *filename );

void stat_report (char *source_path);

void color_invert(char *source_path);


void color_red (char *source_path);

void color_blue (char *source_path);

void color_green (char *source_path);

void color_gray (char *source_path);

#endif
