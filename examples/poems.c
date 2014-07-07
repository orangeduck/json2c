#include "poems.h"

poems poems_object = {
    {
        .id_author = "czeslaw-milosz", 
        .index = 48670, 
        .id_poem = "magpiety", 
        .score = 5.2, 
        .poem = "The same and not quite the same, I walked through oak forests\nAmazed that my Muse, Mnemosyne,\nHas in no way diminished my amazement.\nA magpie was screeching and I said: Magpiety?\nWhat is magpiety? I shall never achieve\nA magpie heart, a hairy nostril over the beak, a flight\nThat always renews just when coming down,\nAnd so I shall never comprehend magpiety.\nIf however magpiety does not exist\nMy nature does not exist either.\nWho would have guessed that, centuries later,\nI would invent the question of universals?", 
        .author = "Czeslaw Milosz", 
        .title = "Magpiety", 
        .votes = 8, 
        .about = {
            .length = 2, 
            .values = (const char*[]){"nature", "heart"}
        }
    }, 
    {
        .id_author = "john-mccrae", 
        .index = 53195, 
        .id_poem = "quebec", 
        .score = 6.5, 
        .poem = "-1908\n\n\n\nOf old, like Helen, guerdon of the strong --\n Like Helen fair, like Helen light of word, --\n\"The spoils unto the conquerors belong.\n Who winneth me must win me by the sword.\"\n\nGrown old, like Helen, once the jealous prize\n That strong men battled for in savage hate,\nCan she look forth with unregretful eyes,\n Where sleep Montcalm and Wolfe beside her gate?", 
        .author = "John McCrae", 
        .title = "Quebec", 
        .votes = 13, 
        .about = {
            .length = 3, 
            .values = (const char*[]){"hate", "sleep", "light"}
        }
    }
};

