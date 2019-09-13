#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>


#define MAX_NACHNAME 31
#define MAX_VORNAME 31
#define MAX_FACHNAME 31
#define MAX_FAECHER 5
#define MAX_ZEUGNISSE 20


typedef struct
{
	unsigned char fach[MAX_FACHNAME];
	unsigned short note;

}FachUndNote;


typedef struct 
{
	unsigned char nachname[MAX_NACHNAME];
	unsigned char vorname[MAX_VORNAME];
	FachUndNote fachnote[MAX_FAECHER];

}Zeugnisdaten;


void zeigeMenue();
void stringEingabe(char *txt, Zeugnisdaten *pZeugnisse, int len);
int zahlEingabe(char *txt, int min, int max);
void erstelleZeugnisse(Zeugnisdaten *pZeugnisse, int *countZeugnisse);
void anzeigenZeugnisse(Zeugnisdaten *pZeugnisse, int *countZeugnisse);


int main(int argc, char *argv[])
{
	Zeugnisdaten Zeugnisse[MAX_ZEUGNISSE];
	int countZeugnisse = 0;
	char entscheidung;

	do
	{
		zeigeMenue();

		switch (toupper(_getwch()))
		{
			case 'A': erstelleZeugnisse(Zeugnisse, &countZeugnisse); break;
			case 'B': anzeigenZeugnisse(Zeugnisse, &countZeugnisse); break;
			case 'C': return 0;
		}

		system("pause");

	} while (1);
	
	return 0;
}


void zeigeMenue()
{
	system("cls");

	printf_s(	":::::::::::::::::::: MENUE ::::::::::::::::::::\n"
				"::                                           ::\n"
				"::           A) Zeugniss erstellen           ::\n"
				"::           B) Zeugnisse anzeigen           ::\n"
				"::           C) Programm beenden             ::\n"
				"::                                           ::\n"
				":::::::::::::::::::::::::::::::::::::::::::::::\n"	);
}

void stringEingabe(char *txt, Zeugnisdaten *pZeugnisse, int len)
{
	printf_s(txt);
	fseek(stdin, 0, SEEK_END);
	scanf_s("%s", pZeugnisse, len);
}

int zahlEingabe(char *txt, int min, int max)
{
	int noteEingabe = 0;

	printf_s(txt);
	fseek(stdin, 0, SEEK_END);
	scanf_s("%d", &noteEingabe);

	while (noteEingabe < min || noteEingabe > max)
	{
		printf_s("Ungueltige Eingabe!\n");
		printf_s(txt);
		fseek(stdin, 0, SEEK_END);
		scanf_s("%d", &noteEingabe);
	}

	return noteEingabe;
}

void erstelleZeugnisse(Zeugnisdaten *pZeugnisse, int *countZeugnisse)
{
	system("cls");

	if (*countZeugnisse >= MAX_ZEUGNISSE)
	{
		printf_s("\n\n\nSie sind nicht berechtigt mehr als 20 Zeugnisse zu erstellen\n\n\n");
	}

	while (*countZeugnisse < MAX_ZEUGNISSE)
	{
		system("cls");
		printf_s(":::::::::::::: ZEUGNISS ERSTELLEN :::::::::::::\n\n");

		stringEingabe("Nachname...: ", pZeugnisse[*countZeugnisse].nachname, MAX_NACHNAME);
		stringEingabe("Vorname....: ", pZeugnisse[*countZeugnisse].vorname, MAX_VORNAME);
		printf_s("\n");

		for (int i = 0; i < MAX_FAECHER; i++)
		{
			stringEingabe("Fach.......: ", pZeugnisse[*countZeugnisse].fachnote[i].fach, MAX_FACHNAME);
			pZeugnisse[*countZeugnisse].fachnote[i].note = zahlEingabe("Note.......: ", 1, 5);
			printf_s("\n");
		}

		*countZeugnisse += 1;
		printf_s("\n\nDieses Zeugniss wurde erfolgreich erstellt!\n\n");

		break;
	}
}

void anzeigenZeugnisse(Zeugnisdaten *pZeugnisse, int *countZeugnisse)
{
	system("cls");
	printf_s(":::::::::::::: ZEUGNISSE ANZEIGEN :::::::::::::\n\n");

	for (int i = 0; i < *countZeugnisse; i++)
	{
		printf_s("\n\t\t\tNachname: %-30s\n\t\t\t Vorname: %-30s\n\n", pZeugnisse[i].nachname, pZeugnisse[i].vorname);

		for (int j = 0; j < MAX_FAECHER; j++)
		{
			printf_s(" %30s: %d\n", pZeugnisse[i].fachnote[j].fach, pZeugnisse[i].fachnote[j].note);
		}

		printf_s("\n:::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	}
}