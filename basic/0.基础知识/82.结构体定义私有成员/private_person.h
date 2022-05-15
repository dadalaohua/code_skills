#ifndef _PRIVATE_PERSON_H_
#define _PRIVATE_PERSON_H_

typedef struct {
    void* _Placeholder;
} Person;

Person *PersonNew(char const *name, int age, char const *intro);

char const *PersonGetName(Person const *p);

int PersonGetAge(Person const *p);

void PersonToString(Person const *p);

void PersonDestroy(Person **ptr);

void PersonSetIntro(Person **ptr, char const *intro);

#endif //_PRIVATE_PERSON_H_
