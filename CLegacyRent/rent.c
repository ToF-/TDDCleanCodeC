#include <stdio.h>
#include <stdlib.h>
#define BUFFERMAX 40
#define MAXORDER 10001
#define INFNTY 2000000

struct order{
    char trade_id[BUFFERMAX];
    int start;
    int duration;
    int revenue;
    int best;
} Orders[MAXORDER];

char buf[BUFFERMAX];
char id[BUFFERMAX];

int compare(const void *a, const void *b) {

    struct order *orderA = (struct order *)a;
    struct order *orderB = (struct order *)b;

    if(orderA->start < orderB->start)
        return -1;
    if(orderA->start > orderB->start)
        return 1;
    if(orderA->duration < orderB->duration)
        return -1;
    if(orderA->duration > orderB->duration)
        return 1;
    return orderA->revenue - orderB->revenue;

}
void sort_orders(int max2) {
    // se fait ch.. a réécrire un  fichier
    // ^ on comprend que ça prend du temps
    qsort(Orders,max2, sizeof(struct order), compare); 
}
int next_compatible(int numOrder, int max2) {
    int start = Orders[numOrder].start;
    int end = start + Orders[numOrder].duration;
    int low = numOrder+1; 
    int high = max2; 
    int middle; 
    int k;
    while (low <= high) {
        middle = low + (high - low) / 2;
        if(Orders[middle].start < end)
            low = middle + 1;
        else {
            k = middle;
            high = middle - 1;
        }
    }
    return k;
}
void init_order(int index, const char *trade_id, int start, int duration, int revenue) {
    sprintf(Orders[index].trade_id, "%8.8s", trade_id);
    Orders[index].start = start;
    Orders[index].duration = duration;
    Orders[index].revenue = revenue;
    Orders[index].best = 0;
}

int compute_best_revenue(int max2) {
    for(int numOrder = max2-2; numOrder >= 0; numOrder--) {
        int compatible = next_compatible(numOrder, max2);
        int next = numOrder+1;
        int revenue_from_next = Orders[next].best;
        int revenue_plus_compatible = Orders[numOrder].revenue + Orders[compatible].best;
        if (revenue_from_next > revenue_plus_compatible) {
            Orders[numOrder].best = revenue_from_next;
        }
        else {
            Orders[numOrder].best = revenue_plus_compatible;
        }
    }
    return Orders[0].best;
}

int add_sentinel(int max2) {
    Orders[max2].start = INFNTY;
    Orders[max2].duration   = 0;
    Orders[max2].revenue      = 0;
    max2++;
    return max2;
}

int process_orders(int max2) {
    sort_orders(max2);
    max2 = add_sentinel(max2);
    return compute_best_revenue(max2);
}

int read_orders(char *buf, FILE *fp) {
    int nb_orders;
    fgets(buf, BUFFERMAX, stdin);
    sscanf(buf, "%d", &nb_orders);
    for(int numOrder = 0; numOrder < nb_orders; numOrder++) {
        fgets(buf, BUFFERMAX, fp);
        sscanf(buf, "%s %d %d %d"
                , id
                , &Orders[numOrder].start
                , &Orders[numOrder].duration
                , &Orders[numOrder].revenue);
    }
    return nb_orders;
}

#ifndef IN_TEST
int main() {
#else
int main_test() {
#endif
    int max1;
    fgets(buf, BUFFERMAX, stdin);
    sscanf(buf, "%d", &max1);
    // boucle sur le nombre de blocs
    for(int numBlock=0; numBlock<max1; numBlock++) {
        int nb_orders = read_orders(buf,stdin);
        printf("%d\n", process_orders(nb_orders));
    }
    return 0;
}
