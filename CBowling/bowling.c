#include <stdlib.h>

struct bowling_score {
    int score;
    int bonus;
    int bonus_suivant;
    int dernier_tir;
    int moities_tour;
};

struct bowling_score * compteur_bowling() {
    return (struct bowling_score *)calloc(1,sizeof(struct bowling_score));
}

void initialise(struct bowling_score *bs) {
    bs->score = 0;
    bs->bonus = 0;
    bs->bonus_suivant = 0;
    bs->dernier_tir = 0;
    bs->moities_tour = 0;
}
void consomme_bonuses(struct bowling_score *bs, int tir) {
    if(bs->bonus) {
        bs->score += tir * bs->bonus;
        bs->bonus = bs->bonus_suivant;
        bs->bonus_suivant--;
    }
}
void calcule_prochain_bonus(struct bowling_score *bs, int tir) {
    if(tir == 10 && bs->moities_tour % 2 == 0)
    {
        bs->bonus++;
        bs->bonus_suivant++;
        bs->moities_tour++;
    }
    else if(bs->moities_tour % 2 && tir + bs->dernier_tir == 10)
    {
        bs->bonus = 1;
    }
}
void enregistre_tir(struct bowling_score* bs, int tir) {
    if(bs->moities_tour < 20) {
        bs->score += tir;
    }

    consomme_bonuses(bs, tir);

    if(bs->moities_tour < 20) {
        calcule_prochain_bonus(bs, tir);
    }
    bs->dernier_tir = tir;
    bs->moities_tour++;
}

int calcule_score(struct bowling_score *bs) {
    return bs->score;
}

void termine(struct bowling_score *bs) {
    free(bs);
}

#ifndef IN_TEST
int main() {
#else
int main_test() {
#endif
    exit(0);
}
