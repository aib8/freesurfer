/**
 * @file mri_minus.cpp
 * @brief calculates the result of subtracting second volume from the first one
 *   mri_minus vol1 vol2 vol_out
 *
 */

/*
  BEGINHELP
 * some very helpful information here
  ENDHELP
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "const.h"
#include "utils.h"
#include "mri.h"
#include "version.h"
#include "macros.h"

static void print_usage(void) ;
static void usage_exit(void);
static void print_help(void) ;
static void print_version(void) ;

static int get_option(int argc, char *argv[]) ;
static char vcid[] = "";

const char *Progname ;


/***-------------------------------------------------------****/
int main(int argc, char *argv[]) {
    MRI *mri_1, *mri_2, *mri_out;

    // fill both MRI variables, input check
    mri_1 = MRIread(argv[1]);
    if (!mri_1)
        ErrorExit(ERROR_BADPARM, "%s: could not read source volume %s",
                  Progname, argv[1]);
    mri_2 = MRIread(argv[2]);
    if (!mri_2)
        ErrorExit(ERROR_BADPARM, "%s: could not read source volume %s",
                  Progname, argv[2]);

    // input check for whether the two given volumes are of equal dimensions
    if !(mri_1.width == mri_2.width && mri_1.height == mri_2.hieght && mri_1.depth == mri_2.depth)
        ErrorExit(ERROR_BADPARM, "Given MRI volumes must have the same dimensions");

    // perform the subtract, pixelwise (nested for loops)


    // save the results to mri output variable
    mri_out =
    MRIwrite(mri_out, argv[3]);
}


static int get_option(int argc, char *argv[]) {
//TODO
}

/* --------------------------------------------- */
static void print_usage(void)
{
  printf("USAGE: %s fname1 fname2 outname \n",Progname) ;
  printf("\n");
}

/* --------------------------------------------- */
static void print_help(void)
{
  print_usage() ;
  printf(
    "\n"
    "Performs a voxel-wise minus on two volumes\n"
  );
  exit(1) ;
}

/* --------------------------------------------- */
static void print_version(void)
{
  printf("%s\n", vcid) ;
  exit(1) ;
}

/* ------------------------------------------------------ */
static void usage_exit(void)
{
  print_usage() ;
  exit(1) ;
}


