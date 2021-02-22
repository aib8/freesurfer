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
#include "string"

static void print_usage(void) ;
static void usage_exit(void);
static void print_help(void) ;
static void print_version(void) ;

static int get_option(int argc, char *argv[]) ;
static char vcid[] = "";
static string operation = "minus"

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

    // define the MRI output based off given MRI
    mri_out = MRIclone(mri_1, NULL)

    // input check for whether the two given volumes are of equal dimensions
    if !(mri_1->xsize == mri_2->xsize && mri_1->ysize == mri_2->ysize && mri_1->zsize == mri_2->zsize)
        ErrorExit(ERROR_BADPARM, "Given MRI volumes must have the same dimensions, number of frames");

    // compare voxel sixes as well
    if !(mri_1->width == mri_2->width && mri_1->height == mri_2->hieght && mri_1->depth == mri_2->depth)
         ErrorExit(ERROR_BADPARM, "Given MRI volumes must have identical voxel volume sizes");

    // perform the subtract (or addition), pixelwise (nested for loops), only for first frame
    int x, y, z;
    for (int x = 0; x < mri_1->width; x++) {
        for (int y = 0; y < mri_1->height; y++) {
            for (int z = 0; z < mri_1->depth; z++) {
                if (operation == "minus") {
                    MRIsetVoxVal(mri_out , 0, MRIgetVoxVal(mri_1, x, y, z, 0) - MRIgetVoxVal(mri_2, x, y, z, 0))
                } else {
                    MRIsetVoxVal(mri_out , 0, MRIgetVoxVal(mri_1, x, y, z, 0) + MRIgetVoxVal(mri_2, x, y, z, 0))\
                }
            }
        }
    }

    // save the results to mri output variable
    MRIwrite(mri_out, argv[3]);
}


static int get_option(int argc, char *argv[]) {
    option = argv[1] + 1 ;            /* past '-' */
    if (!stricmp(option, "-help")||!stricmp(option, "-usage"))
    {
        print_usage();
    }
    else if (!stricmp(option, "version"))
    {
        print_version();
    }
    else if (!stricmp(option, "plus"))
    {
        operation = "plus";
    }
    else
    {
        fprintf(stderr, "unknown option %s\n", argv[1]) ;
        usage(1) ;
        exit(1) ;
    }
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


