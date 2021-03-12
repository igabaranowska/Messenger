#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIMIT_KONT 500
#define LIMIT_WIADOMOSCI 1000

struct konto{
    char imie[20];
    char nazwisko[20];
    char mail[50];
    char haslo[20];
    int plec;
};

struct wiadomosc{
    struct konto *nadawca;
    struct konto *odbiorca;
    char tresc[500];
    unsigned long timestamp;
    int wyswietlono;
};

struct konto konta[LIMIT_KONT];
struct wiadomosc wiadomosci[LIMIT_WIADOMOSCI];

int liczba_kont = 0;
int liczba_wiadomosci = 0;

void wypisz_konta()
{
    for(int i=0; i<liczba_kont; i++)
    {
        printf("%s; %s; %s; %s; %d \n", konta[i].imie, konta[i].nazwisko, konta[i].mail, konta[i].haslo, konta[i].plec);
    }
}

void wypisz_wiadomosci()
{
    for(int i=0; i<liczba_wiadomosci; i++)
    {
        printf("%s do %s: %s; %d sekund temu; przeczytano: %d\n", wiadomosci[i].nadawca->imie, wiadomosci[i].odbiorca->imie, wiadomosci[i].tresc, time(NULL)-wiadomosci[i].timestamp, wiadomosci[i].wyswietlono);
    }
}

void wyswietl_wiadomosci(int pozycja)
{
    system("CLS");
    printf("==================================\n");
    printf("    Twoje wiadomosci:\n");
    printf("==================================\n\n");

    for(int i=0; i<liczba_wiadomosci; i++)
    {
        if(strcmp(konta[pozycja].mail, wiadomosci[i].odbiorca->mail)==0)
        {
            printf("------------------------------\n");
            printf("%s %s napisal", wiadomosci[i].nadawca->imie, wiadomosci[i].nadawca->nazwisko);

            if(wiadomosci[i].nadawca->plec)
            {
                printf("a: \n");
            }
            else{
                printf(": \n");
            }
            printf("%s", wiadomosci[i].tresc);
            printf(" (%d sekund temu)\n", time(NULL)-wiadomosci[i].timestamp);
            wiadomosci[i].wyswietlono = 1;
            printf("------------------------------\n\n");
        }
    }
    system("PAUSE");
    wyswietl_profil(pozycja);
}

void napisz_wiadomosc(int pozycja)
{
    system("CLS");
    printf("==================================\n");
    printf("    Wybierz kontakt:\n");
    printf("==================================\n\n");

    for(int i=0; i<liczba_kont; i++)
    {
        if(i==pozycja)
        {
            continue;
        }
        else{
            printf("%d- %s %s\n", i+1, konta[i].imie, konta[i].nazwisko);
        }
    }

    int przycisk;
    scanf("%d", &przycisk);
    przycisk--;

    while(przycisk<0 || przycisk==pozycja || przycisk>(liczba_kont-1))
    {
        printf("Niepoprawna wartosc. Sprobuj ponownie.\n");
        scanf("%d", &przycisk);
        przycisk--;
    }

    system("CLS");
    printf("==================================\n");
    printf("    do: %s %s\n", konta[przycisk].imie, konta[przycisk].nazwisko);
    printf("==================================\n\n");

    char test;
    wiadomosci[liczba_wiadomosci].nadawca = &konta[pozycja];
    wiadomosci[liczba_wiadomosci].odbiorca = &konta[przycisk];
    printf("Tresc: ");
    scanf("%c", &test);
    scanf("%[^\n]s", wiadomosci[liczba_wiadomosci].tresc);
    wiadomosci[liczba_wiadomosci].timestamp = time(NULL);
    wiadomosci[liczba_wiadomosci].wyswietlono = 0;
    liczba_wiadomosci++;

    printf("Wyslano wiadomosc.\n");

   /* wypisz_wiadomosci();*/
    system("PAUSE");
    wyswietl_profil(pozycja);
}

void wyswietl_profil(int pozycja)
{
    system("CLS");
    printf("==================================\n");
    printf("    Zalogowano: %s %s\n", konta[pozycja].imie, konta[pozycja].nazwisko);
    printf("==================================\n\n");

    printf("1- Napisz wiadomosc\n");
    printf("2- Wyswietl wiadomosci\n");
    printf("3- Wyloguj\n");

    int przycisk;
    scanf("%d", &przycisk);

    switch(przycisk)
    {
        case 1:
            napisz_wiadomosc(pozycja);
            break;
        case 2:
            wyswietl_wiadomosci(pozycja);
            break;
        case 3:
            menu();
            break;
        default:
            wyswietl_profil(pozycja);
    }
}

void logowanie()
{
    if(liczba_kont<2)
    {
        menu();
    }
    else{
        system("CLS");
        printf("==========================\n");
        printf("    Zaloguj sie\n");
        printf("==========================\n\n");

        char mail[50];
        char haslo[20];

        printf("Mail: ");
        scanf("%s", mail);
        printf("Haslo: ");
        scanf("%s", haslo);

        int czy_istnieje = 0;
        int indeks_uzytkownika;

        for(int i=0; i<liczba_kont; i++)
        {
            if(strcmp(mail, konta[i].mail)==0 && strcmp(haslo, konta[i].haslo)==0)
            {
                czy_istnieje = 1;
                indeks_uzytkownika = i;
            }
        }

        if(czy_istnieje==0)
        {
            printf("Nieudane logowanie. Sprobuj ponownie.\n");
            system("PAUSE");
            menu();
        }
        else{
            wyswietl_profil(indeks_uzytkownika);
        }
    }
}

void rejestracja()
{
    system("CLS");
    printf("==========================\n");
    printf("    Rejestracja konta\n");
    printf("==========================\n\n");

    printf("Jak masz na imie?: ");
    scanf("%s", konta[liczba_kont].imie);
    printf("Jak sie nazywasz?: ");
    scanf("%s", konta[liczba_kont].nazwisko);
    printf("Adres mail: ");
    scanf("%s", konta[liczba_kont].mail);
    printf("Haslo: ");
    scanf("%s", konta[liczba_kont].haslo);
    printf("Plec (0/1): ");
    scanf("%d", &konta[liczba_kont].plec);

    liczba_kont++;

    printf("\nRejestracja zakonczona sukcesem.\n");

    /*wypisz_konta();*/

    system("PAUSE");

    menu();
}

void menu()
{
    system("CLS");
    printf("==========================\n");
    printf("    Witaj w messengerze\n");
    printf("==========================\n");

    printf("1- Rejestracja konta\n");
    printf("2- Logowanie\n");
    printf("3- Wyjscie\n");

    int przycisk;
    scanf("%d", &przycisk);
    switch(przycisk)
    {
        case 1:
            rejestracja();
            break;
        case 2:
            logowanie();
            break;
        case 3:
            exit(1);
            break;
        default:
            menu();
    }
}

int main()
{
    menu();
    return 0;
}
