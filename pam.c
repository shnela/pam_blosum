#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pam.h"
#include "matrix.h"

void get_pam1_matrix(double (**pam1_matrix_out)[20])
  /* ! free pam1_matrix_out */
{
  int x, y;
  double (*pam1_matrix)[20];
  FILE *pam1_file;
  const char* pam1_file_name = "in/pam1.matrix";
  int v;

  /* allocate memory */
  pam1_matrix = malloc(sizeof(double[number_of_amino][number_of_amino]));

  /* read pam1 value from file */
  pam1_file = fopen(pam1_file_name, "r");

  y = 0;
  x = 0;
  while(1)
  {
    fscanf (pam1_file, "%d", &v);
    if (feof(pam1_file))
      break;
    pam1_matrix[y][x] = (double)v / 10000;

    if (!(++x % number_of_amino)) {
      y++;
    }
    x %= number_of_amino;
  }

  /* asign return variables */
  *pam1_matrix_out = pam1_matrix;
  
  /* free memory */
  fclose(pam1_file);
}

void get_log_odds_matrix(int n, int (**log_odds_matrix_out)[20])
{
  double (*pam_matrix)[20];
  int (*log_odds_matrix)[20];
  int x, y;
  double odds_a, odds_b;
  double multiplier_scale = 10;

  /* get PAMn matrix */
  get_pam1_matrix(&pam_matrix);
  power_matrix(&pam_matrix, n);

  /* count log odds matrix */
  for (y = 0; y < 20; y++) {
    for (x = 0; x <= y; x++) {
      odds_a = log10(pam_matrix[y][x] / amino_accid_frequencies[x]) * 10;
      odds_b = log10(pam_matrix[y][x] / amino_accid_frequencies[y]) * 10;
      log_odds_matrix[y][x] = (int)((odds_a + odds_b + 0.5) / 2);
//      printf ("%3d ", log_odds_matrix[y][x]);
    }
//    printf("\n");
  }

  /* assign return variables */
  *log_odds_matrix_out = log_odds_matrix;

  /* free alocated memory */
  free(pam_matrix);

}
