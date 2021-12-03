#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Błażej Wróbel, 250070, Wydział Informatyki i Telekomunikacji, PWr */
/* Zadanie kwalifikacyjne - drugi sposób rozwiązania. */

/* Forward declaration, żeby kompilator wiedział, co będzie w strukturze CString. */
typedef struct CString CString;
long long int cstring_length(CString* cstring);
char get_char_at_given_position(long long int position, CString* cstring);
void replace_char_at_given_position(long long int position, char new_char, CString* cstring);
const char* const get_whole_string(CString* cstring); 

/* Struktura CString z polami na długość i napis oraz ze wskaźnikami do odpowiednich funkcji. */
typedef struct CString
{
    long long int length;
    char* str;

    /* Wskaźniki do funkcji. */
    long long int (*cstring_length_ptr)(CString*);
    char (*get_char_at_given_position_ptr)(long long int, CString*);
    void (*replace_char_at_given_position_ptr)(long long int, char, CString*);
    const char* const (*get_whole_string_ptr)(CString*);
 
} CString;

/* Funkcja do tworzenia struktur CString. W niej również są odpowiednio inicjowane wskaźniki do funkcji. */
CString* cstring_new(const char* str)
{
    CString* cstring_ptr = malloc(sizeof(CString));

    long long int index = 0;
    long long int length  = 0;

    while(str[index] != '\0'){
        length++;
        index++;
    }
    
    cstring_ptr->length = length;

    cstring_ptr->str = malloc(length+1);

    strcpy(cstring_ptr->str, str); 

    /* Wskaźniki do funkcji. */
    cstring_ptr->cstring_length_ptr = &cstring_length;
    cstring_ptr->get_char_at_given_position_ptr = &get_char_at_given_position;
    cstring_ptr->replace_char_at_given_position_ptr = &replace_char_at_given_position;
    cstring_ptr->get_whole_string_ptr = &get_whole_string;

    return cstring_ptr;
}

/* Funkcja do pobierania długości łańcucha znaków. */
long long int cstring_length(CString* cstring)
{
    return cstring->length;
}

/* Funkcja do pobierania znaku na danej (dowolnej) pozycji */
char get_char_at_given_position(long long int position, CString* cstring)
{
    return cstring->str[position];   
}

/* Funkcja do zamiany znaku na danej (dowolnej) pozycji */
void replace_char_at_given_position(long long int position, char new_char, CString* cstring)
{
    long long int string_length = (cstring->length);

    if(string_length == 0)
    {
        return;
    } 
    else if(position >= 0 && position < string_length)
    {
        cstring->str[position] = new_char;
    }
}

/* Funkcja do pobierania całego łańcucha znaków (stały wskaźnik na stałą). Wiem, że jak ktoś się uprze, to i tak
 zmodyfikuje ten napis np. poprzez przypisanie do char* - ale wtedy kompilator wygeneruje ostrzeżenie.
 */
const char* const get_whole_string(CString* cstring)
{
    return (const char* const) cstring->str;
}

int main(void)
{
    /* Testy (5 przypadków testowych) */

    char* test1 = "Ala ma kota";
    char* test2 = "Drzewo binarne";
    char* test3 = "otoczka";
    char* test4 = "abcde fghij";
    char* test5 = "";

    CString* cstring1 = cstring_new(test1);
    CString* cstring2 = cstring_new(test2);
    CString* cstring3 = cstring_new(test3);
    CString* cstring4 = cstring_new(test4);
    CString* cstring5 = cstring_new(test5);

    printf("Rozpoczynam testy...\n");

    assert(11 == cstring1->cstring_length_ptr(cstring1));
    assert(14 == cstring2->cstring_length_ptr(cstring2));
    assert(7 == cstring3->cstring_length_ptr(cstring3));
    assert(11 == cstring4->cstring_length_ptr(cstring4));
    assert(0 == cstring5->cstring_length_ptr(cstring5));

    printf("Testy pobierania długości łańcucha znaków - przeszły.\n");

    printf("\n");

    assert(' ' == cstring1->get_char_at_given_position_ptr(3, cstring1));
    assert('D' == cstring2->get_char_at_given_position_ptr(0, cstring2));
    assert('a' == cstring3->get_char_at_given_position_ptr(6, cstring3));
    assert('e' == cstring4->get_char_at_given_position_ptr(4, cstring4));
    assert('\0' == cstring5->get_char_at_given_position_ptr(0, cstring5));

    printf("Testy pobierania znaku na danej pozycji - przeszły.\n");

    printf("\n");

    const char* const whole_string1 = cstring1->get_whole_string_ptr(cstring1);
    const char* const whole_string2 = cstring2->get_whole_string_ptr(cstring2);
    const char* const whole_string3 = cstring3->get_whole_string_ptr(cstring3);
    const char* const whole_string4 = cstring4->get_whole_string_ptr(cstring4);
    const char* const whole_string5 = cstring5->get_whole_string_ptr(cstring5);

    assert(0 == strcmp("Ala ma kota", whole_string1));
    assert(0 == strcmp("Drzewo binarne", whole_string2));
    assert(0 == strcmp("otoczka", whole_string3));
    assert(0 == strcmp("abcde fghij", whole_string4));
    assert(0 == strcmp("", whole_string5));

    printf("Testy pobierania całego łańcucha znaków - przeszły.\n");

    printf("\n");

    cstring1->replace_char_at_given_position_ptr(4, '2', cstring1);
    cstring2->replace_char_at_given_position_ptr(0, 'p', cstring2);
    cstring3->replace_char_at_given_position_ptr(1, '+', cstring3);
    cstring4->replace_char_at_given_position_ptr(3, 'c', cstring4);
    cstring5->replace_char_at_given_position_ptr(0, 'b', cstring5);

    assert(0 == strcmp("Ala 2a kota", cstring1->str));
    assert(0 == strcmp("przewo binarne", cstring2->str));
    assert(0 == strcmp("o+oczka", cstring3->str));
    assert(0 == strcmp("abcce fghij", cstring4->str));
    assert(0 == strcmp("", cstring5->str));

    printf("Testy zamiany znaku na danej pozycji - przeszły.\n");

    printf("\n");

    printf("Koniec testów.\n");

    return 0;
}