#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>


typedef struct ContryData ContryData;
typedef struct DataByDate DataByDate;
typedef struct AllCountriesData AllCountriesData;
#define bool int
#define false 0
#define true 1

struct AllCountriesData
{
    ContryData* Head;
    ContryData* Tail;
};

struct ContryData
{
    char* CountryName;
    DataByDate* DataByDateHead;
    DataByDate* DataByDateTail;
    ContryData* NextContry;
};

struct DataByDate
{
    char* Date;
    char* Confirmed;
    char* Deaths;
    char* Recovered;
    char* Active;
    DataByDate* Next;
};

void freeAllContriesData(AllCountriesData* AllCountriesData);
void freeContryData(ContryData *contryData);
void printAllContriesData(AllCountriesData* allCountriesData);
void printContryData(ContryData* contryData);
ContryData *load_country(char* countryName);
AllCountriesData* load_db();

void InsertTailDateList(ContryData* contryData, DataByDate* dataByDate)
{
    if (contryData->DataByDateTail == NULL)
	{
		contryData->DataByDateHead = dataByDate;
		contryData->DataByDateTail = dataByDate;
	}
	else
	{
        contryData->DataByDateTail->Next = dataByDate;
        contryData->DataByDateTail = dataByDate;
        dataByDate->Next = NULL;
 	}
}

void InsertTailCountryList(struct AllCountriesData* AllCountriesData, struct ContryData * contryData)
{
	if (AllCountriesData->Tail == NULL)
	{
		AllCountriesData->Head = contryData;
		AllCountriesData->Tail = contryData;
	}
	else
	{
		AllCountriesData->Tail->NextContry = contryData;
		AllCountriesData->Tail = contryData;
        contryData->NextContry = NULL;
	}
}

bool isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

void stripNewLine(char * string)
{
    char buff[100];
    int i = 0;
    int j = 0;

    while (string[i] != '\0')
    {
        if (string[i] != '\n')
        {
            buff[j] = string[i];
            j++;
        }

        i++;
    }

    buff[j] = '\0';
    strcpy(string, buff);
}

void extractDate(char* date)
{
    int i = 0;
    int j = 0;
    char tempBuffer[100] = "";

    while (date[i] != '\0')
    {
        if (date[i] == ':')
        {
            i++;

            while (date[i] != '\0')
            {
                tempBuffer[j] = date[i];

                i++;
                j++;
            }

            break;
        }

        i++;
    }
    
    strcpy(date, tempBuffer);
    stripNewLine(date);
}


void extractNumber(char* numberOfKey)
{
    char numberBuffer[100];
    int i = 0;
    int newStrigIndex = 0;
    while (numberOfKey[i] != '\0')
    {
        if (isDigit(numberOfKey[i]))
        {
            numberBuffer[newStrigIndex] = numberOfKey[i];
            newStrigIndex++;
        }
        
        i++;
    }
    
    numberBuffer[newStrigIndex] = '\n';
    numberBuffer[newStrigIndex + 1] = '\0';
    strcpy(numberOfKey, numberBuffer);
    stripNewLine(numberOfKey);
}

char* readCopyDateToDataStruct(char* inputBuffer, size_t *lineLen, FILE* fd, int* eof)
{
    char * buff;
    *eof = getline(&inputBuffer, lineLen, fd);
    extractDate(inputBuffer);
    buff = (char *)malloc(strlen(inputBuffer) + 1);
    strcpy(buff, inputBuffer);
    return buff;
}


char* readCopyStringToDataStruct(char* inputBuffer, size_t *lineLen, FILE* fd)
{
    char * buff; 
    getline(&inputBuffer, lineLen, fd);
    extractNumber(inputBuffer);
    buff = (char *)malloc(strlen(inputBuffer) + 1);
    strcpy(buff, inputBuffer);
    return buff;
}