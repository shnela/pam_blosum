#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "smith_waterman.h"


void print_help(char *prog_name)
{
  printf("Usage:\n");
  printf("\t%s -h\n", prog_name);
  printf("\t%s -d out_dir fasta1 fasta2 .. fastan\n", prog_name);
  printf("\t%s -d out_dir -f fasta_dir\n", prog_name);
}


int main(int argc, char *argv[])
{
  int c;
  int errflg = 0;
  char *out_dir = 0;
  char *fasta_dir = 0;
  const int MAX_FASTA_FILES = 5;
  char *fasta_files[MAX_FASTA_FILES];
  FILE * fasta;

  while ((c = getopt(argc, argv, "hf:d:")) != -1) {
    switch(c) {
      case 'h':
        print_help(argv[0]);
        exit(0);
      case 'd':
        out_dir = optarg;
        break;
      case 'f':
        fasta_dir = optarg;
        break;
      case ':':       /* -f or -d without operand */
        fprintf(stderr,
            "Option -%c requires an operand\n", optopt);
        errflg++;
        break;
      case '?':
        fprintf(stderr,
            "Unrecognized option: '-%c'\n", optopt);
        errflg++;
    }
  }
  if (errflg) {
    print_help(argv[0]);
    exit(2);
  }

  /* if to many fasta files were provided */
  if (argc - optind > MAX_FASTA_FILES) {
     printf("Max %d fasta files allowed\n", MAX_FASTA_FILES); 
     exit(2);
  }

  /* if fasta dir not suuplied, take fasta files */
  if (!fasta_dir) {
    int i;
    for (i=0 ; optind < argc; optind++, i++) {
      if (access(argv[optind], R_OK)) {
        fasta_files[i] = argv[optind];
      }
    }
  }

  char *seq1 = "-ACACACTA";
  char *seq2 = "-AGCACACA";
  printf("%s\n%s\n", seq1, seq2);
  char **sq1;
  char **sq2;
  smith_waterman(seq1,seq2, sq1, sq2);
  
}
