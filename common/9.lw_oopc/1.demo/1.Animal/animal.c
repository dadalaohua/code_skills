#include <stdio.h>
#include <string.h>
#include "animal.h"

/* ���ö�����ǳ� */
void Animal_setName(Animal* t, const char* name)
{
    // ����ٶ�nameС��128���ַ���Ϊ��ʾ�����룬������������Ʒ�����в�Ҫ����д��
    strcpy(t->name, name);
}
/* ���ö�������� */
void Animal_setAge(Animal* t, int age)
{
    t->age = age;
}
/* ��������Ǵ��к� */
void Animal_sayHello(Animal* t)
{
    //printf("Hello! ����%s������%d���ˣ�\n", t->name, t->age);
    printf("Hello! my name is%s,%d years��\n", t->name, t->age);
    printf("\r\n");
}
/* ��ʼ��������ǳƺ����� */
void Animal_init(Animal* t, const char* name, int age)
{
    t->setName(t, name);
    t->setAge(t, age);
}

ABS_CTOR(Animal)
FUNCTION_SETTING(setName, Animal_setName);
FUNCTION_SETTING(setAge, Animal_setAge);
FUNCTION_SETTING(sayHello, Animal_sayHello);
FUNCTION_SETTING(init, Animal_init);
END_ABS_CTOR

/* ��ĳ���Ϊ */
void Fish_eat(Animal* t)
{
    //printf("���ˮ�ݣ�\n");
    printf("Fish eat aquatic plants!\n");
}
/* ��ĺ�����Ϊ */
void Fish_breathe(Animal* t)
{
    //printf("������������\n");
    printf("Fish breathe with gills!\n");
}
/* ����ƶ���Ϊ */
void Fish_move(IMoveable* t)
{
    //printf("����ˮ���Σ�\n");
    printf("Fish swim in the water!\n");
}
/* ��ʼ������ǳƺ����� */
void Fish_init(Fish* t, const char* name, int age)
{
    Animal* animal = SUPER_PTR(t, Animal);
    animal->setName(animal, name);
    animal->setAge(animal, age);
}

CTOR(Fish)
SUPER_CTOR(Animal);
FUNCTION_SETTING(Animal.eat, Fish_eat);
FUNCTION_SETTING(Animal.breathe, Fish_breathe);
FUNCTION_SETTING(IMoveable.move, Fish_move);
FUNCTION_SETTING(init, Fish_init);
END_CTOR

/* ���ĳ���Ϊ */
void Dog_eat(Animal* t)
{
    //printf("���Թ�ͷ��\n");
    printf("Dogs eat bones !\n");
}
/* ���ĺ�����Ϊ */
void Dog_breathe(Animal* t)
{
    //printf("���÷κ�����\n");
    printf("Dogs breathe with their lungs!\n");
}
/* �����ƶ���Ϊ */
void Dog_move(IMoveable* t)
{
    //printf("���ڵ����ܣ�\n");
    printf("The dog is running on the ground!\n");
}
/* ��ʼ�������ǳƺ����� */
void Dog_init(Dog* t, const char* name, int age)
{
    Animal* animal = SUPER_PTR(t, Animal);
    animal->setName(animal, name);
    animal->setAge(animal, age);
}

CTOR(Dog)
SUPER_CTOR(Animal);
FUNCTION_SETTING(Animal.eat, Dog_eat);
FUNCTION_SETTING(Animal.breathe, Dog_breathe);
FUNCTION_SETTING(IMoveable.move, Dog_move);
FUNCTION_SETTING(init, Dog_init);
END_CTOR

void Car_move(IMoveable* t)
{
    //printf("�����ڿ�����\n");
    printf("The car is moving!\n");
}

CTOR(Car)
FUNCTION_SETTING(IMoveable.move, Car_move);
END_CTOR