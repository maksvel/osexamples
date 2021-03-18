
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

pthread_t t0,t1; //deklarisu se dve niti (postoji poseban tip za niti - pthread)
int counter = 0; //ovo je globalna promenljiva, dostupna svim nitima procesa
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //deklarise se i inicjalizuje mutex


/*'void Pthread_mutex_lock(pthread_mutex_t *mutex) {
int rc = pthread_mutex_lock(mutex);
assert(rc == 0);
}*/

/*void Pthread_mutex_unlock(pthread_mutex_t *mutex) {
int rc = pthread_mutex_lock(mutex);
assert(rc == 0);
}*/
void* inkrementiraj()  //funkcija koja vraca pokazivac; koja ce se koristiti za kreiranje obe niti - obe niti æe raditi istu stvar
{
    for (int i=0; i<10000000;i++) {  //sto miliona puta se vrsi uvecavanje globalne promenljive counter
        pthread_mutex_lock(&lock); //"zakljucava" se sekcija
            counter++;
        pthread_mutex_unlock(&lock);
        }
    return NULL;
}
int main() //glavna nit
{

   // if ( pthread_mutex_init( &lock, NULL) != 0 )
     //   printf( "mutex init failed\n" ); //inicijalizuje se mutex
    int greska0 = pthread_create(&t0, NULL, &inkrementiraj,NULL);  //kreira se prva nit koja izvrsava funkciju inkrementiraj
    if (greska0 != 0) { printf("ne moze se kreirati prva nit\n");}
    int greska1 = pthread_create(&t1, NULL, &inkrementiraj,NULL);
    if (greska1!= 0) { printf("ne moze se kreirati druga nit\n");}
    pthread_join(t0, NULL);//ceka okoncanje prve niti
    pthread_join(t1, NULL);//isto za drugu
    pthread_mutex_destroy(&lock); //unistava se mutex
    printf ("Vrednost counter-a je sada %d", counter);

    return 0;
}
