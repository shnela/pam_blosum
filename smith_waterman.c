#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smith_waterman.h"


void set_matrix_entry(MatrixEntry *me,
    int val, int prev_x, int prev_y)
{
  me->val = val;
  me->prev_x = prev_x;
  me->prev_y = prev_y;
}

int sim_function(char a, char b)
{
  return (a == b ? matching_score : mismatch_peanality);
}

void set_matrix_entry_prev_and_max_value(MatrixEntry **matrix,
    char *seq1, char *seq2, int x, int y)
  /*
     {[y][x - 1], [y - 1][x - 1], [x - 1][y]}
   */
{
  MatrixEntry *me = &matrix[y][x];
  int horizontal_move =
    matrix[y][x - 1].val + gap_peanality;
  int vertical_move =
    matrix[y - 1][x].val + gap_peanality;
  int diagonal_move =
    matrix[y - 1][x - 1].val + sim_function(seq1[x], seq2[y]);

  if(horizontal_move > diagonal_move) {
    if(horizontal_move > vertical_move) {
      me->prev_x = x - 1;
      me->prev_y = y;
      me->val = horizontal_move;
    } else {
      me->prev_x = x;
      me->prev_y = y - 1;
      me->val = vertical_move;
    }
  } else if(diagonal_move > vertical_move) {
    me->prev_x = x - 1;
    me->prev_y = y - 1;
    me->val = diagonal_move;
  } else {
    me->prev_x = x;
    me->prev_y = y - 1;
    me->val = vertical_move;
  }
}


void print_matrix(MatrixEntry **matrix, int max_x, int max_y)
{
  printf("=\n");
  int x, y;
  for (y = 0; y < max_y; y++) {
    for (x = 0; x < max_x; x++)
      printf("( %d )\t", matrix[y][x].val);
    printf("\n");
    for (x = 0; x < max_x; x++)
      printf("[%d:%d]\t", y, x);
    printf("\n");
    for (x = 0; x < max_x; x++)
      printf("(%d:%d)\t", matrix[y][x].prev_y, matrix[y][x].prev_x);
    printf("\n");
    printf("\n");
  }
}


void revert_matrix_path(MatrixEntry **matrix,
    char *seq1, char *seq2, int seq1_len, int seq2_len)
/* 
   revert array path from the last cell
   after this process we could go from the (0,0) point
 */
{
  int x = seq1_len - 1;
  int y = seq2_len - 1;
  int prev_x, prev_y;
  int next_x, next_y;
  while (1) {
    /* store where to go next */
    next_x = matrix[y][x].prev_x;
    next_y = matrix[y][x].prev_y;

    /* update values in current cell */
    matrix[y][x].prev_x = prev_x;
    matrix[y][x].prev_y = prev_y;

    /* set values to current field, which will be updated in next cell */
    prev_x = x;
    prev_y = y;

    /* end the loop if it's (0,0) cell */
    if (!x && !y)
      break;

    /* go to the next cell */
    x = next_x;
    y = next_y;
  }
}


void construct_alignments(MatrixEntry **matrix,
    char *seq1, char *seq2, int seq1_len, int seq2_len,
    char **alignment_seq1, char **alignment_seq2)
{
  int x = 1, y = 1;
  int seq_ind = 0;
  int prev_x = 0, prev_y = 0;
  while (1)
  {
    if (prev_x == x) {
      /* vertical move */
      (*alignment_seq1)[seq_ind] = '-';
      (*alignment_seq2)[seq_ind++] = seq2[y];
    } else if (prev_y == y) {
      /* horizontal move */
      (*alignment_seq1)[seq_ind] = seq1[x];
      (*alignment_seq2)[seq_ind++] = '-';
    } else {
      /* diagonal move */
      (*alignment_seq1)[seq_ind] = seq1[x];
      (*alignment_seq2)[seq_ind++] = seq2[y];
    }
    (*alignment_seq1)[seq_ind] = 0;
    (*alignment_seq2)[seq_ind] = 0;
    
    /* end the loop */
    if (x == seq1_len - 1 && y == seq2_len - 1) {
      (*alignment_seq1)[seq_ind] = 0;
      (*alignment_seq2)[seq_ind] = 0;
      break;
    }

    /* set next_cell */
    prev_x = x;
    prev_y = y;
    int tmp_x = matrix[y][x].prev_x;
    y = matrix[y][x].prev_y;
    x = tmp_x;
  }
}


void smith_waterman(char *seq1_in, char *seq2_in,
    char **alignment_seq1, char **alignment_seq2)
  /*
     matrix scheme:

     y\x  s e q 1

     s
     e
     q
     2
   */
{
  int seq1_len = strlen(seq1_in) + 1;
  int seq2_len = strlen(seq2_in) + 1;
  
  /* append - to the sequence */
  char *seq1 = malloc(seq1_len);
  char *seq2 = malloc(seq2_len);
  strcpy(seq1 + 1, seq1_in);
  strcpy(seq2 + 1, seq2_in);
  seq1[0] = seq2[0] = '-';

  /* allocate allignment sequences */
  *alignment_seq1 = malloc(seq1_len * 2);
  *alignment_seq2 = malloc(seq2_len * 2);

  /* allocate matrix */
  MatrixEntry ** matrix = malloc(seq2_len * sizeof(*matrix));
  int x, y;
  for (y = 0; y < seq2_len; y++) {
    matrix[y] = malloc(seq1_len * sizeof(MatrixEntry));
  }

  /* fill matrix */
  for (y = 0; y < seq2_len; y++) {
    for (x = 0; x < seq1_len; x++) {
      MatrixEntry *me = &matrix[y][x];
      if (!x && !y) {
        set_matrix_entry(me, 0, 0, 0);
      } else if (!x) {
        set_matrix_entry(me, 0, 0, y - 1);
      } else if (!y) {
        set_matrix_entry(me, 0, x - 1, 0);
      } else {
        set_matrix_entry_prev_and_max_value(matrix, seq1, seq2,x, y);
      }
      matrix[y][x] = *me;
    }
  }

  revert_matrix_path(matrix, seq1, seq2, seq1_len, seq2_len);

  construct_alignments(matrix, seq1, seq2, seq1_len, seq2_len,
      alignment_seq1, alignment_seq2);

  printf("%s\n%s\n", *alignment_seq1, *alignment_seq2);

  /* free matrix */
  for (y = 0; y < seq2_len; y++) {
    free(matrix[y]);
  }
  free(matrix);
}
