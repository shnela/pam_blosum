#ifndef PAM_H
#define PAM_H

/*
   Implementation of PAM matrix.
 */

static char amino_acid_order[] = {
  'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I',
  'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};

static double amino_accid_frequencies[] = {
  0.096, 0.034, 0.042, 0.053, 0.025, 0.032, 0.053, 0.09, 0.034, 0.035,
  0.085, 0.085, 0.012, 0.045, 0.041, 0.057, 0.062, 0.012, 0.03, 0.078};
const static int number_of_amino = 20;

typedef struct {
  char oryginal_amino_acid;
  char replacement_amino_acid;
  int distance;
} PamEntry;

void get_pam1_matrix(double (**pam1_matrix_out)[20]);

void get_log_odds_matrix(int n, int (**log_odds_matrix_out)[20]);

#endif
