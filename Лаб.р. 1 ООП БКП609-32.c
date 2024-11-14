#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Item{
	struct Item *next;
	struct Item *prev;
}Item;

typedef struct List{
	Item *head;
	Item *tail;
}List;

// + это готовые функции
void Add(List *l, Item *i); //+
void Delete(List *l, int Number); //+
Item* GetItem(List *l, int Number); //+
Item* Remove(List *l, int Number); //+
void Insert(List *l, Item *i, int Number); 
int Count(List *l); //+
void Clear(List *l);
int GetIndex(List *l, Item *i);

void PrintList(List *l); //+













void Add(List *l, Item *i){
	if (l->head == 0 || l->tail == 0)
	{
		i->next = 0;
		i->prev = 0;
		l->tail = i;
		l->head = i;
		return;
	}
	i->next = l->tail;
	i->prev = 0;
	l->tail->prev = i;
	l->tail = i;
}

int Count(List *l){
	if (l->head == 0 || l->tail == 0)	
		return 0;
	Item *a = l->head;
	int i;
	for(i = 1; a->prev != 0; i++, a = a->prev);
	return i;
}

Item* GetItem(List *l, int Number){
	Item *a = l->head;
	int i;
	for(i = 0; i != Number; i++, a = a->prev);
	return a;
}

Item* Remove(List *l, int Number){
	Item *cur = GetItem(l, Number);
	Item *a = cur->prev;
	Item *b = cur->next;
	if(!a && !b)
	{
		l->head = 0;
		l->tail = 0;
		return;
	}
	if (a)
		a->next = b;
	else
	{
		b->prev = 0;
		l->tail = b;
	}
	if (b)
		b->prev = a;
	else
	{
		a->next = 0;
		l->head = a;
	}
}

void Delete(List *l, int Number){
	free(Remove(l, Number));
}

void Insert(List *l, Item *i, int Number){
	/*
	i->next = l->tail;
	i->prev = 0;
	l->tail->prev = i;
	l->tail = i;
	В цикле передвинуть все Item'ы на 1
	*/
}








void PrintList(List *l){
	if (l->head == 0 || l->tail == 0)
	{
		printf("Список пуст!\n");
		return;
	}
	Item *a = l->head;
	int i;
	printf("List: %p \tHead: %p \t Tail: %p\n# \tp                \tprev                \tnext\n", l, l->head, l->tail);
	for(i = 0; 1; i++, a = a->prev)
	{
		printf("%d \t%p \t%p \t%p\n", i, a, a->prev, a->next);
		if (a->prev == 0)
			break;
	}	
}



int main(){
	setlocale(LC_ALL, "Rus");
	int menu;
	List *l = malloc(sizeof(List));
	l->head = 0;
	l->tail = 0;
	Item *c;
	/*
	Item *a = malloc(sizeof(Item));
	Item *b = malloc(sizeof(Item));
	a->next = 0;
	a->prev = b;
	b->next = a;
	b->prev = 0;
	l->head = a;
	l->tail = b;
	*/
	
	/*
	printf("a = %p; ap = %p, %p; an = %p, %p;\n", a, a->prev, &a->prev, a->next, &a->next);
	printf("b = %p; bp = %p, %p; bn = %p, %p;\n", b, b->prev, &b->prev, b->next, &b->next);	
	printf("c = %p; cp = %p, %p; cn = %p, %p;\n", c, c->prev, &c->prev, c->next, &c->next);
	*/
	
	

	while(1){
		menu = -1;
		while(printf("1.Добавить элемент в список\n"
					"2.Узнать количество элементов в списке\n"
					"3.Получить элемент списка по номеру\n"
					"4.Исключить элемент из списка\n"
					"5.Удалить элемент списка\n"
					"6.TEST. Очистить список\n"
					"7.TEST. Добавить элемент в список на заданную позицию\n"
					"8.TEST. Определить номер элемента по его указателю\n"
					"9.Вывести список на экран\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu > 9))
		{
			system("cls");
			printf("Некорректный ввод!\n");
		}
		switch(menu){
			case 1:	//Add();
				c = malloc(sizeof(Item));
				if (!c)
				{
					printf("Ошибка выделения памяти!\n");
					break;
				}
				c->next = 0;
				c->prev = 0;
				Add(l, c);
				c = 0;
				system("cls");
				printf("Элемент успешно добавлен в список.\n");
				break;
			case 2:	//Count();
				menu = Count(l);
				system("cls");
				if (menu)
					printf("Элементов в списке: %d.\n", menu);
				else
					printf("Список пуст, в нём 0 элементов!\n");
				break;
			case 3:	//GetItem();
				system("cls");
				if (!Count(l))
				{
					printf("Список пуст, в нём нет элементов!\n");
					break;
				}
				while(printf("Введите номер элемента, который хотите получить.\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu >= Count(l)))
				{
					system("cls");
					printf("Некорректный ввод!\n");
				}
				system("cls");
				c = GetItem(l, menu);
				printf("# \tp                \tprev                \tnext\n%d \t%p \t%p \t%p\n", menu, c, c->prev, c->next);
				break;
			case 4:	//Remove();
				system("cls");
				if (!Count(l))
				{
					printf("Список пуст, из него нечего исключать!\n");
					break;
				}
				menu = -1;
				while(PrintList(l), printf("Введите номер элемента, который хотите исключить из списка.\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu >= Count(l)))
				{
					system("cls");
					printf("Некорректный ввод!\n");
				}
				Remove(l, menu);
				system("cls");
				printf("Элемент успешно исключён из списка.\n");
				break;
			case 5:	//Delete();
				system("cls");
				if (!Count(l))
				{
					printf("Список пуст, из него нечего удалять!\n");
					break;
				}
				menu = -1;
				while(PrintList(l), printf("Введите номер элемента, который хотите удалить.\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu >= Count(l)))
				{
					system("cls");
					printf("Некорректный ввод!\n");
				}
				Delete(l, menu);
				system("cls");
				printf("Элемент успешно удалён.\n");
				break;
				
				
			case 6:	//Clear();
				
				
				
				break;
			case 7:	//Insert();
				system("cls");
				menu = -1;
				if (!Count(l))
				{
					while(printf("Список пуст! Добавить первый элемент?\n0 - да\n1 - нет\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu > 1))
					{
						system("cls");
						printf("Некорректный ввод!\n");
					}
					system("cls");
					if (!menu)
					{
						c = malloc(sizeof(Item));
						if (!c)
						{
							printf("Ошибка выделения памяти!\n");
							break;
						}
						c->next = 0;
						c->prev = 0;
						Add(l, c);
						c = 0;
						break;
					}
				}
				if (menu == 0 || menu == 1)
					break;
				while(PrintList(l), printf("Введите номер для элемента, которым он станет в списке.\n"), fflush(stdin), (scanf("%d", &menu)!=1 || menu < 0 || menu >= Count(l)))
				{
					system("cls");
					printf("Некорректный ввод!\n");
				}
				c = malloc(sizeof(Item));
				if (!c)
				{
					printf("Ошибка выделения памяти!\n");
					break;
				}
				c->next = 0;
				c->prev = 0;
				Insert(l, c, menu);
				c = 0;
				system("cls");
				printf("Элемент успешно внедрён в список.\n");
				break;
			case 8:	//GetIndex();
				
				
				
				
				

				
				
				break;
			case 9:	//PrintList();
				system("cls");
				PrintList(l);
				break;
		}
	}
	
	
	
	
	system("pause");
	return 0;
}
