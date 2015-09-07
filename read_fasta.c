#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "read_fasta.h"


void get_fasta_sequences(char* file_name,
    Fasta **out_fasta_sequences, int *number_of_fasata_sequenes)
{
//  Fasta fasta_sequences[MAX_FASTA_SEQUENCES];
  Fasta *fasta_sequences = malloc(MAX_FASTA_SEQUENCES * sizeof(Fasta));
  FILE *file = fopen(file_name, "r");
  size_t max_row_width = 70;
  char *line = malloc(max_row_width);
  int n;
  int fasta_sequence_index = 0, /* index of struct Fasta in fasta_sequences */
      inside_sequence_index = 0, /* indes in sequence field of struct Fasta */
      fasta_sequence_len = 0; /* current sequence len */

  while((n = getline(&line, &max_row_width, file)) != -1)
  {
//    printf("%s", line);

    /* check if this fasta sequence can be enlarge */
    if (inside_sequence_index + n >= MAX_FASTA_SEQUENCE_LENGTH) {
      fprintf(stderr, "Max fasta sequence length exceeded.");
      exit(2);
    }

    /* copy line without newline character and null */
    strncpy(fasta_sequences[fasta_sequence_index].sequence
            + inside_sequence_index, line, n - 1);
    inside_sequence_index += n - 1;
    fasta_sequences[fasta_sequence_index].sequence[inside_sequence_index] = 0;

    /* end of the sequence */
    if (line[n - 2] == '*')
    {
      /*
      printf ("%d\n", inside_sequence_index);
      printf ("%s\n", fasta_sequences[fasta_sequence_index].sequence);
      */
      /* terminate sequence with null */
      fasta_sequences[fasta_sequence_index].sequence[inside_sequence_index] = 0;
      fasta_sequence_index++;
      if (fasta_sequence_index == MAX_FASTA_SEQUENCES) {
        fprintf(stderr, "Max fasta sequences amount exceeded..");
        exit(2);
      }
      fasta_sequence_len = 0;
    }

    /* new sequence occured */
    if (line[0] == '>') {
        strncpy((char*)&fasta_sequences[fasta_sequence_index].name,
            line, n - 2);
        fasta_sequences[fasta_sequence_index].name[n - 2] = 0;
//        printf("Created: %s\n", fasta_sequences[0].name);
        inside_sequence_index = 0;
    }
  }
  *number_of_fasata_sequenes = fasta_sequence_index;
  *out_fasta_sequences = fasta_sequences;
}


void generate_sequence_pairs(Fasta *fasta_seq, int fasta_seq_len,
    Fasta (**fasta_pairs_out)[2])
/*
   generate pairs of fasta matrices
 */
{
  Fasta (*fasta_pairs)[2] =
    malloc(fasta_seq_len * fasta_seq_len * sizeof(Fasta[2]) / 2 + 1);
  /* here we can allocate huge amount of memory, check if successfull */

  *fasta_pairs_out = fasta_pairs;
}
