#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
int delete (const char *sciezka)
{
    char pytania[1000][200];
    int i = 0;
    FILE *plik = fopen(sciezka, "r+");
    if (plik == NULL)
    {
        perror("Przepraszamy cos poszlo nie tak");
    }
    while (!feof(plik))
    {
        fgets(pytania[i], 200, plik);
        if (i % 6 == 0)
        {
            printf("[%d] %s", i, pytania[i]);
        }
        i++;
    }
    fclose(plik);
    int d, ilosc_lini, wybor;
    ilosc_lini = i;
    printf("\n");
    printf("Twoj plik tekstowy zawiera: %d lini\n", ilosc_lini);
    printf("Podaj Numer pytania ktorego chcesz sie pozbyc\n ");
    scanf("%d", &d);
    do
    {
        if (d == ilosc_lini - 6)
        {
            printf("Nie mozna usunac ostatniego pytania, wybierz inna linie !\n");
            printf("Podaj nowa wartosc\n");
            scanf("%d", &d);
        }
    } while (d == ilosc_lini - 6);
    FILE *plik2 = fopen(sciezka, "w");
    if (plik2 == NULL)
    {
        perror("Przepraszamy cos poszlo nie tak");
    }
    for (i = 0; i < ilosc_lini; i++)
    {
        if (i >= d && i < d + 6)
        {
            printf("Usunieto : %s", pytania[i]);
        }
        else
        {
            fprintf(plik2, "%s", pytania[i]);
        }
    }
    fclose(plik2);
    printf("\n");
    return 1;
}
int liczba_lini(const char *sciezka)
{
    FILE *plik = fopen(sciezka, "r");
    char znak;
    int linie = 0;
    while ((znak = getc(plik)) != EOF)
    {
        if (znak == '\n')
            linie++;
    }
    fclose(plik);
    return linie;
}
int tryb_edycji(const char *sciezka)
{
    FILE *plik = fopen(sciezka, "a");
    if (plik == NULL)
    {
        perror("Niestety cos poszlo nie tak :((");
    }
    printf("Wzorzec wedlug ktorego nalezy dopisywac pytania:\nKazmierza Pawlaka w  'Samych swoich' zagral ?\na) Zdzislaw Maklakiewicz\nb) Wladyslaw Hancza\nc) Witold Pyrkosz\nd) Waclaw Kowalski\nd\n ");
    char pytanie[200];
    char odpowiedzi[50];
    char poprawna[2];
    int ilosc;
    printf("Podaj ilosc pytan ktore chcesz dodac.");
    scanf("%d", &ilosc);
    do
    {
        fprintf(plik, "\n");
        printf("Prosze o wprowadzenie pytania: max(200 znakow) \n");
        fflush(stdin);
        fgets(pytanie, sizeof(pytanie), stdin);
        fprintf(plik, "%s", pytanie);
        for (int i = 0; i < 4; i++)
        {
            printf("Prosze o wprowadzenie odpowiedzi: max(50 znakow) \n");
            fflush(stdin);
            fgets(odpowiedzi, sizeof(odpowiedzi), stdin);
            fprintf(plik, "%s", odpowiedzi);
        }
        printf("Prosze o wprowadzenie poprawnej odpowiedzi: max(1 znak np. a) \n");
        fflush(stdin);
        fgets(poprawna, sizeof(poprawna), stdin);
        fprintf(plik, "%s", poprawna);
        ilosc--;
    } while (ilosc >= 1);
    fclose(plik);
    return 1;
}
int losuj_pytanie(const char *sciezka)
{
    FILE *plik = fopen(sciezka, "r");
    char pytania[liczba_lini(sciezka) / 6][200];
    char odpowiedzi[liczba_lini(sciezka) - 2 * liczba_lini(sciezka) / 6][200];
    int poprawna[liczba_lini(sciezka) / 6];
    int i = 0;
    while (!feof(plik))
    {
        fgets(pytania[i], 200, plik);
        for (int j = 0; j < 4; j++)
        {
            fgets(odpowiedzi[i * 4 + j], 100, plik);
        }
        poprawna[i] = fgetc(plik);
        fgetc(plik);
        i++;
    }
    fclose(plik);
    srand(time(NULL));
    int suma = 0;
    int zycia = 3;
    int wyjscie = 0;
    int numer_podejscia = 1, temp, losowe_pytanie[liczba_lini(sciezka) / 6], j;
    for (int i = 0; i < liczba_lini(sciezka) / 6; i++)
    {
        losowe_pytanie[i] = i + 1;
    }
    for (int i = 0; i < liczba_lini(sciezka) / 6; i++)
    {
        j = (rand() % (liczba_lini(sciezka) / 6) - 1) + 1;
        temp = losowe_pytanie[i];
        losowe_pytanie[i] = losowe_pytanie[j];
        losowe_pytanie[j] = temp;
    }
    int k = 1;
    do
    {
        if (zycia != 3)
        {
            printf("Liczba zyc w Quizie %d\n", zycia);
        }
        int numer_pytania = losowe_pytanie[k];
        printf("%s", pytania[numer_pytania]);
        for (int i = 0; i < 4; i++)
        {
            printf("%s", odpowiedzi[numer_pytania * 4 + i]);
        }
        char odpowiedz_uzytkownika;
        printf("Podaj odpowiedz:\n");
        fflush(stdin);
        scanf("%c", &odpowiedz_uzytkownika);
        do
        {

            if (odpowiedz_uzytkownika != 'a' && odpowiedz_uzytkownika != 'b' && odpowiedz_uzytkownika != 'c' && odpowiedz_uzytkownika != 'd')
            {
                printf("Podales nieprawidlowa opcje, wprowadz nowy znak:\n");
                fflush(stdin);
                odpowiedz_uzytkownika = getchar();
                odpowiedz_uzytkownika = tolower(odpowiedz_uzytkownika);
            }
        } while (odpowiedz_uzytkownika != 'a' && odpowiedz_uzytkownika != 'b' && odpowiedz_uzytkownika != 'c' && odpowiedz_uzytkownika != 'd');
        k++;
        if (poprawna[numer_pytania] == (int)odpowiedz_uzytkownika)
        {
            suma++;
        }
        else
        {
            if (zycia == 1)
            {
                FILE *plik2 = fopen("uzytkownik.txt", "a");
                if (plik2 == NULL)
                {
                    perror(":( Przykro nam cos poszlo nie tak.");
                }
                char podejscie[] = "podejscie=";
                char ilosc_pytan[] = "/10";
                fprintf(plik2, "%d ", numer_podejscia);
                fprintf(plik2, "%s", podejscie);
                fprintf(plik2, " %d", suma);
                fprintf(plik2, "%s\n", ilosc_pytan);
                fclose(plik2);
                FILE *plik3 = fopen("uzytkownik.txt", "r");
                if (plik3 == NULL)
                {
                    perror(":( Przykro nam cos poszlo nie tak.");
                }
                char odczyt;
                while (fscanf(plik3, "%c", &odczyt) == 1)
                {
                    printf("%c", odczyt);
                }
                fclose(plik3);
                printf("Niestety Twoja przygoda dobiegla konca, ale zawsze mozesz sprobowac jeszce raz w tym celu wybierz T/N\n");
                char odpowiedz;
                fflush(stdin);
                odpowiedz = getchar();
                odpowiedz = tolower(odpowiedz);
                do
                {

                    if (odpowiedz != 't' && odpowiedz != 'n')
                    {
                        printf("Podales nieprawidlowa opcje, wprowadz nowy znak:\n");
                        fflush(stdin);
                        odpowiedz = getchar();
                        odpowiedz = tolower(odpowiedz);
                    }
                } while (odpowiedz != 't' && odpowiedz != 'n');
                if (odpowiedz != 't')
                {
                    wyjscie = 1;
                    return 1;
                }
                else
                {
                    numer_podejscia++;
                    zycia = 3;
                    suma = 0;
                }
            }
            else
            {
                printf("Ehhhhh co zawiodlo ?\n");
                zycia--;
            }
        }
    } while (suma <= 10 && wyjscie == 0);
}
int menu_kategoria(char kategoria)
{
    printf("Wybierz kategorie z ktorej chcesz otrzymac pytania. \n");
    printf("a)kultura\nb)sport\nc)Lektury\nd)Technologia\n");
    printf("Podaj wybrana kategorie: np. A\n");
    kategoria = getchar();
    kategoria = tolower(kategoria);
    do
    {

        if (kategoria != 'a' && kategoria != 'b' && kategoria != 'c' && kategoria != 'd')
        {
            printf("Podales nieprawidlowa opcje, wprowadz nowy znak:\n");
            fflush(stdin);
            kategoria = getchar();
            kategoria = tolower(kategoria);
        }
    } while (kategoria != 'a' && kategoria != 'b' && kategoria != 'c' && kategoria != 'd');
    switch (kategoria)
    {
    case 'a':
        if (losuj_pytanie("Kultura.txt") == 1)
        {
            return 1;
        }
        break;
    case 'b':
        if (losuj_pytanie("sport.txt") == 1)
        {
            return 1;
        }
        break;
    case 'c':
        if (losuj_pytanie("lektury.txt") == 1)
        {
            return 1;
        }
        break;
    case 'd':
        if (losuj_pytanie("technologia.txt") == 1)
        {
            return 1;
        }
        break;
    }
}
void pobiera_nazwe_uzytkownika(const char *sciezka)
{
    int i;
    FILE *plik = fopen(sciezka, "w");
    if (plik == NULL)
    {
        perror(":( Przykro nam cos poszlo nie tak.");
    }
    char nazwa_uzytkownika[11];
    char uzytkownik[] = "Nazwa Uzytkownika : ";
    fprintf(plik, "%s", uzytkownik);
    printf("Prosze o wprowadzenie nazwy uzytkownika (maksymalnie 10 znakow)\n");
    fflush(stdin);
    fgets(nazwa_uzytkownika, sizeof(nazwa_uzytkownika), stdin);
    fprintf(plik, "%s", nazwa_uzytkownika);
    printf("Dziekuje za wprowadzenie nazwy uzytkownika\n");
    fclose(plik);
    printf("\n");
}
void czytanie_regulaminu(const char *sciezka)
{
    int i;
    FILE *plik = fopen(sciezka, "r");
    if (plik == NULL)
    {
        perror(":( Przykro nam cos poszlo nie tak.");
    }
    char odczyt;
    while (fscanf(plik, "%c", &odczyt) == 1)
    {
        printf("%c", odczyt);
    }
    printf("\n");
    fclose(plik);
    printf("\n");
}
int menu(const char *sciezka)
{
    int wraca = 1;
    char kategoria;
    do
    {
        FILE *plik = fopen(sciezka, "r");
        if (plik == NULL)
        {
            perror(":( Przykro nam cos poszlo nie tak.");
        }
        char odczyt;
        while (fscanf(plik, "%c", &odczyt) == 1)
        {
            printf("%c", odczyt);
        }
        fclose(plik);
        int wybor, wybor2;
        printf("\n");
        printf("Prosze o wybranie opcji z ktorej chcesz skorzystac np 1\n ");
        scanf("%d", &wybor);
        do
        {
            if (wybor != 1 && wybor != 2 && wybor != 3 && wybor != 4)
            {
                printf("Podales nieprawidlowa wartosc, wprowadz ja na nowo\n");
                fflush(stdin);
                scanf("%d", &wybor);
            }
        } while (wybor != 1 && wybor != 2 && wybor != 3 && wybor != 4);
        switch (wybor)
        {
        case 1:
            czytanie_regulaminu("zasady gry.txt");
            pobiera_nazwe_uzytkownika("uzytkownik.txt");
            if (menu_kategoria(kategoria) == 1)
            {
                wraca = 0;
            }
            break;
        case 2:
            printf("Z ktorego pliku chcesz usunac pytania :\n1.kultura.txt\n2.sport.txt\n3.lektruy.txt\n4.technologia.txt\n");
            scanf("%d", &wybor2);
            do
            {
                if (wybor2 != 1 && wybor2 != 2 && wybor2 != 3 && wybor2 != 4)
                {
                    printf("Podales nieprawidlowa wartosc, wprowadz ja na nowo\n");
                    fflush(stdin);
                    scanf("%d", &wybor2);
                }
            } while (wybor2 != 1 && wybor2 != 2 && wybor2 != 3 && wybor2 != 4);
            switch (wybor2)
            {
            case 1:
                if (delete ("kultura.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 2:
                if (delete ("sport.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 3:
                if (delete ("lektury.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 4:
                if (delete ("technologia.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            }
            break;
        case 3:
            printf("Ktory z plikow chcesz edytowac :\n1.kultura.txt\n2.sport.txt\n3.lektruy.txt\n4.technologia.txt\n");
            scanf("%d", &wybor2);
            do
            {
                if (wybor2 != 1 && wybor2 != 2 && wybor2 != 3 && wybor2 != 4)
                {
                    printf("Podales nieprawidlowa wartosc, wprowadz ja na nowo\n");
                    fflush(stdin);
                    scanf("%d", &wybor2);
                }
            } while (wybor2 != 1 && wybor2 != 2 && wybor2 != 3 && wybor2 != 4);
            switch (wybor2)
            {
            case 1:
                if (tryb_edycji("kultura.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 2:
                if (tryb_edycji("sport.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 3:
                if (tryb_edycji("lektury.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            case 4:
                if (tryb_edycji("technologia.txt") == 1)
                {
                    wraca = 0;
                }
                break;
            }
            break;
        case 4:
            wraca = 1;
            break;
        }
    } while (wraca == 0);
}
typedef struct komunikat_pozegnalny
{
    int znak;
    struct komunikat_pozegnalny *next;
} komunikat;
komunikat *head = NULL, *tail, *tmp;
int komunikat_pozegnalny(int komunikat)
{
    FILE *plik;
    int znakk;
    plik = fopen("komunikat_pozegnalny.txt", "r");
    while (!feof(plik))
    {
        fscanf(plik, "%c", &znakk);
        tmp = malloc(sizeof(komunikat));
        tmp->znak = znakk;
        tmp->next = NULL;
        if (head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tmp;
        }
    }
    tmp = head;
    while (tmp != NULL)
    {
        printf("%c", tmp->znak);
        tmp = tmp->next;
    }
}
int main()
{
    int znakk;
    menu("komunikat.txt");
    komunikat_pozegnalny(znakk);
    return 0;
}
