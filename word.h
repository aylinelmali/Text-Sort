#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Word
{
 char* text;
 int count;
 struct Word* next;
};

struct Word *word(char* text, int count, struct Word* next);

char* get_text(struct Word* word);

int get_count(struct Word* word);

struct Word* get_next(struct Word* word);

void set_text(struct Word* word, char* text);

void set_count(struct Word* word, int count);

void set_next(struct Word* word, struct Word* next);