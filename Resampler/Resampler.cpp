// Resampler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int xdim;
int ydim;
int maxraw;
unsigned char *image;

void ReadPGM(FILE*);
void WritePGM(FILE*);
void Validate(int);
void Validate(FILE*);


int main(int argc, char **argv)
{
  int i, j;
  FILE *fp;

  Validate(argc);

  /* begin reading PGM.... */
  printf("begin reading PGM.... \n");
  fp = fopen(argv[1], "rb");
  
  Validate(fp);
  
  ReadPGM(fp);
 
  // your application here 
  // As an example, let's just make an inversion of the input image.
  for (j=0; j<ydim; j++)
    for (i=0; i<xdim; i++) {
      image[j*xdim+i] = 255 - image[j*xdim+i];
    }
  
  /* Begin writing PGM.... */
  printf("Begin writing PGM.... \n");
  if ((fp=fopen(argv[2], "wb")) == NULL){
     printf("write pgm error....\n");
     exit(0);
   }
  WritePGM(fp);

  free(image);
    
  return (1);
}



void ReadPGM(FILE* fp)
{
    int c;
    int i,j;
    int val;
    unsigned char *line;
    char buf[1024];


    while ((c=fgetc(fp)) == '#')
        fgets(buf, 1024, fp);
     ungetc(c, fp);
     if (fscanf(fp, "P%d\n", &c) != 1) {
       printf ("read error ....");
       exit(0);
     }
     if (c != 5 && c != 2) {
       printf ("read error ....");
       exit(0);
     }

     if (c==5) {
       while ((c=fgetc(fp)) == '#')
         fgets(buf, 1024, fp);
       ungetc(c, fp);
       if (fscanf(fp, "%d%d%d",&xdim, &ydim, &maxraw) != 3) {
         printf("failed to read width/height/max\n");
         exit(0);
       }
       printf("Width=%d, Height=%d \nMaximum=%d\n",xdim,ydim,maxraw);

       image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
       getc(fp);

       line = (unsigned char *)malloc(sizeof(unsigned char)*xdim);
       for (j=0; j<ydim; j++) {
          fread(line, 1, xdim, fp);
          for (i=0; i<xdim; i++) {
            image[j*xdim+i] = line[i];
         }
       }
       free(line);

     }

     else if (c==2) {
       while ((c=fgetc(fp)) == '#')
         fgets(buf, 1024, fp);
       ungetc(c, fp);
       if (fscanf(fp, "%d%d%d", &xdim, &ydim, &maxraw) != 3) {
         printf("failed to read width/height/max\n");
         exit(0);
       }
       printf("Width=%d, Height=%d \nMaximum=%d,\n",xdim,ydim,maxraw);

       image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
       getc(fp);

       for (j=0; j<ydim; j++)
         for (i=0; i<xdim; i++) {
            fscanf(fp, "%d", &val);
            image[j*xdim+i] = val;
         }

     }

     fclose(fp);
}


void WritePGM(FILE* fp)
{
  int i,j;
  

  fprintf(fp, "P5\n%d %d\n%d\n", xdim, ydim, 255);
  for (j=0; j<ydim; j++)
    for (i=0; i<xdim; i++) {
      fputc(image[j*xdim+i], fp);
    }

  fclose(fp);
  
}

void Validate(int argc)
{
	if (argc != 3)
	{
		printf("Usage: MyProgram <input_ppm> <output_ppm> \n");
		printf("       <input_ppm>: PGM file \n");
		printf("       <output_ppm>: PGM file \n");
		exit(0);
	}
}

void Validate(FILE * fp)
{
	if (fp == NULL)
	{
		printf("read error...\n");
		exit(0);
	}
}


