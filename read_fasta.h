#ifndef READ_FASTA_h
#define READ_FASTA_h

static const int MAX_FASTA_SEQUENCES = 70;
static const int MAX_FASTA_SEQUENCE_LENGTH = 2000;

typedef struct {
  char name[100];
  char sequence[MAX_FASTA_SEQUENCE_LENGTH];
} Fasta;

void get_fasta_sequences(char* file_name,
    Fasta **out_fasta_sequences, int *number_of_fasata_sequenes);

void generate_sequence_pairs(Fasta *fasta_seq, int fasta_seq_len,
    Fasta (**fasta_pairs_out)[2]);


#endif
