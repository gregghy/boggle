#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dict.h"

void afficher (vectd_t v){
  int i;

  printf("%d ",v.nb);
  for (i = 0; i < v.nb; i++){ 
    printf("%lf ",v.v[i]);
    printf("\n");
  }
}

void ecrire (vectd_t v, char * nomfichier) {
  int i;
  FILE * fd;

  fd = fopen (nomfichier, "w");
  if (! fd) { /* good old ways */
	printf("Impossible d ouvrir le fichier %s !\n\n", nomfichier);
	exit (1);
  }
  fprintf(fd,"%d ",v.nb);
  for (i = 0; i < v.nb; i++)
	fprintf(fd,"%lf ",v.v[i]);
  fclose(fd);
}

vectd_t creer (int nb) {
  vectd_t v;
  int i;
  double x, eps;
  
  v.nb = nb;
  v.v = (double *) malloc (nb * sizeof(double));
  assert(v.v);
  eps = - 0.07;
  for (i = 0, x=1.3; i < v.nb; i++) {
	v.v[i] = x;
	x += eps;
	if (x < 1.0) 
	  eps = 0.145 + eps;
	if (x > 1.7) 
	  eps = - 0.145 + eps;
  }
  return v;
}

vectd_t lire (char * nomfichier) {
  vectd_t v;
  int i, nb;
  FILE * fd;
  double x;
  
  fd = fopen (nomfichier, "r");
  if (! fd) {
	printf("Impossible d ouvrir le fichier %s !\n\n", nomfichier);
	exit (1);
  }
  fscanf(fd,"%d ",&nb);
  v.nb = nb;
  v.v = (double *) malloc (nb * sizeof(double));
  if (! v.v) {
	printf("Impossible d allouer la memoire de taille %d !\n\n", nb);
	exit (1);
  }
  for (i = 0; i < v.nb; i++) {
	fscanf(fd,"%lf ",&x);
	v.v[i] = x;
  }
  fclose(fd);
  return v;
}

int main() {
  vectd_t cont; 
  char * nf = "words.txt";
  cont = lire(nf);
  afficher(cont);

}
