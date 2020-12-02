#include "word.h"

struct Word *word(char* text, int count, struct Word* next)
{
 struct Word *w;
 w = (struct Word *) malloc(sizeof(struct Word));
 w->text = text,
 w->count = count;
 w->next = next;
 return w;
}

//returns text of word
char* get_text(struct Word* word){
 return word->text;
}

//returns word count
int get_count(struct Word* word){
 return word->count;
}

//returns next word
struct Word* get_next(struct Word* word){
 return word->next;
}

//sets text
void set_text(struct Word* word, char* text){
 word->text = text;
}

//sets count
void set_count(struct Word* word, int count){
 word->count = count;
}

//sets next word
void set_next(struct Word* word, struct Word* next){
 word->next = next;
}