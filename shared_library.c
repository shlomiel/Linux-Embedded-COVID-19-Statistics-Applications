
#include "shared_library.h"


ContryData *addDataToCountry(char* countryName)
{
    char fileName[255];
    char* inputBuffer = NULL;
    char dirName[] = "countries/";
    size_t lineLen;
    int currEOF;
    strcpy(fileName, dirName);
    strcat(fileName, countryName);
    strcat(fileName, ".txt");
    FILE* fd = fopen(fileName, "r");
    ContryData * currCounry = (ContryData*)malloc(sizeof(ContryData));
    currCounry->DataByDateHead = NULL;
    currCounry->DataByDateTail = NULL;
    currCounry->NextContry = NULL;
    currCounry->CountryName = malloc(strlen(countryName) + 1);
    strcpy(currCounry->CountryName,countryName);
    DataByDate* currDate;

    while (getline(&inputBuffer, &lineLen, fd) != EOF)
    {
        currDate = (struct DataByDate*)malloc(sizeof(struct DataByDate));
        extractNumber(inputBuffer);
        currDate->Confirmed = (char *)malloc(strlen(inputBuffer) + 1);
        strcpy(currDate->Confirmed, inputBuffer);
        currDate->Deaths = readCopyStringToDataStruct(inputBuffer, &lineLen, fd);
        currDate->Recovered = readCopyStringToDataStruct(inputBuffer, &lineLen, fd);
        currDate->Active = readCopyStringToDataStruct(inputBuffer, &lineLen, fd);
        currDate->Date = readCopyDateToDataStruct(inputBuffer, &lineLen, fd, &currEOF);
        InsertTailDateList(currCounry, currDate);
    }

    free(inputBuffer);
    fclose(fd);
    return currCounry;
}

struct AllCountriesData* load_db()
{
    struct AllCountriesData* AllCountriesData = (struct AllCountriesData*)malloc(sizeof(struct AllCountriesData));
    AllCountriesData->Head = NULL;
    AllCountriesData->Tail = NULL;

    char fileName[] = "countries.txt";
    char* inputBuffer = NULL;
    size_t lineLen;
    FILE* fd = fopen(fileName, "r");
    ContryData* curr;

    while (getline(&inputBuffer, &lineLen, fd) != EOF)
    {
        if (strcmp(inputBuffer, "\n") != 0)
        {
            stripNewLine(inputBuffer);
            curr = addDataToCountry(inputBuffer);
            InsertTailCountryList(AllCountriesData,curr);
        }
    }

    fclose(fd);
    free(inputBuffer);

    return AllCountriesData;
}

ContryData *load_country(char* countryName)
{
    return addDataToCountry(countryName);
}

void printContryData(ContryData* contryData)
{
    DataByDate * curr = contryData->DataByDateHead;

    printf("%s\n", contryData->CountryName);
    while (curr)
    {
        printf("%s\n", curr->Confirmed);
        printf("%s\n", curr->Deaths);
        printf("%s\n", curr->Recovered);
        printf("%s\n", curr->Active);
        printf("%s\n", curr->Date);
        curr = curr->Next;
    }
}


void printAllContriesData(struct AllCountriesData* allCountriesData)
{
    ContryData * curr = allCountriesData->Head;

    while (curr)
    {
        printContryData(curr);
        curr = curr->NextContry;
    }
}

void freeContryData(ContryData *contryData)
{
    DataByDate * curr = contryData->DataByDateHead;
    DataByDate * next;

    while (curr)
    {
        free(curr->Confirmed);
        free(curr->Deaths);
        free(curr->Recovered);
        free(curr->Active);
        free(curr->Date);
        next = curr->Next;
        free(curr);
        curr = next;
    }
}

void freeAllContriesData(struct AllCountriesData* AllCountriesData)
{
    ContryData *curr =  AllCountriesData->Head;
    ContryData *next;

    while (curr)
    {
        next = curr->NextContry;
        freeContryData(curr);
        free(curr->CountryName);
        free(curr);
        curr = next;
    }

    free(AllCountriesData);
}