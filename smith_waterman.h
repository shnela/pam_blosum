#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

/*
   Implementation of Smith-Waterman algorithm for finding local sequence alignment.
 */
static const int gap_peanality = -1;
static const int mismatch_peanality = -1;
static const int matching_score = 2;

typedef struct {
  int val;
  int prev_x;
  int prev_y;
} MatrixEntry;

int sim_function(char a, char b);

void smith_waterman(char *seq1, char *seq2, char **alignment_seq1, char **alignment_seq2);

#endif
