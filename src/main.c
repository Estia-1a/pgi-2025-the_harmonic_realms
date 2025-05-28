#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: - add --debug: freud.exe --debug -f images/input/image.jpeg */
  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */
  
  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  }
  if ( strncmp( configuration.command, "dimension", 1 ) == 0 ) {
    /* dimension() function is defined in feature.h and implemented in feature.c */
    dimension( configuration.filenames[0] );
  } 
  if ( strncmp( configuration.command, "first_pixel", 2 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    first_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "tenth_pixel", 3) == 0 ) {
    /* tenth_pixel() function is defined in feature.h and implemented in feature.c */
    tenth_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "print_pixel", 4 ) == 0 ) {
    int x =atoi(argv[argc-2]);
    int y =atoi(argv[argc-1]);
    print_pixel(configuration.filenames[0], x, y );
  }
  if ( strncmp( configuration.command, "min_pixel", 5 ) == 0 ) {
    min_pixel(configuration.filenames[0]);
  }
/*Creation branche dev */
  if ( strncmp( configuration.command, "max_pixel", 6 ) == 0 ) {
    max_pixel(configuration.filenames[0]);
  }

  return 0;

}
