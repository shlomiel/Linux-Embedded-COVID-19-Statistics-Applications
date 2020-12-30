

#include <stdio.h>

#include "shared_library.h"

#define CONFIRMED 1
#define DEATHS 2
#define RECOVERED 3
#define ACTIVE 4




int stringToInt(char* str);
int DetermineKey(char *Key);
void PrintWithSpaces(int value,int Scaler);
void PrintGraph(DataByDate *headCountry,int key,int maxVaule);
int GetCountryMaxByKey(int keyValue,DataByDate *ctryData);



int main(int argc, char const *argv[])
{
    char buff[100];
    strcpy(buff,argv[2]);
    ContryData *countryData = load_country(buff);
    strcpy(buff,argv[4]);
    int keyValue = DetermineKey(buff);
    int countryMax = GetCountryMaxByKey(keyValue,countryData->DataByDateHead);
    PrintGraph(countryData->DataByDateHead,keyValue,countryMax); 
    return 0;
}

int GetCountryMaxByKey(int keyValue,DataByDate *ctryData)
{
    int maxValue = 0;
    DataByDate *current = ctryData;
    switch(keyValue)
    {
        case(CONFIRMED):
            while(current)
            {
                if(atoi(current->Confirmed) > maxValue)
                    maxValue = atoi(current->Confirmed);
                current = current->Next;
            }

        case(DEATHS):
            while(current)
            {
                if(atoi(current->Deaths) > maxValue)
                    maxValue = atoi(current->Deaths);
                current = current->Next;
            }

        case(RECOVERED):
            while(current)
            {
                if(atoi(current->Recovered) > maxValue)
                    maxValue = atoi(current->Recovered);
                current = current->Next;
            }

        case(ACTIVE):
            while(current)
            {
                if(atoi(current->Active) > maxValue)
                    maxValue = atoi(current->Active);
                current = current->Next;
            }

        default:
        break;

    }
    return maxValue;
}

int stringToInt(char* str)
{
    int index = strlen(str);
    int val = 0;
    int decDig = 1;

    if(!str)
        return 0;

    while(index>=0)
    {
        val+= (str[index]-'0') * decDig;
        index--;
        decDig*=10;
    }

    return val;
}

int DetermineKey(char *Key)
{
    if(!strcmp(Key,"Confirmed"))
        return CONFIRMED;
    
    if(!strcmp(Key,"Deaths"))
        return DEATHS;
    
    if(!strcmp(Key,"Recovered"))
        return RECOVERED;
    
    if(!strcmp(Key,"Active"))
        return ACTIVE;

    printf("Error, wrong input exiting\n");
    exit(1);
}


void PrintWithSpaces(int value,int Scaler)
{
    for(int i = 0 ; i < value/Scaler; i++)
        putchar(' ');

    printf("%d\n",value);
}


void PrintGraph(DataByDate *headCountry,int key,int maxVaule)
{
    int currentValue;
    int Scaler = maxVaule/100;
    DataByDate *current = headCountry;
    while(current)
    {
      switch(key)
         {
            case(RECOVERED):
            currentValue = atoi(current->Recovered);
            break;

            case(DEATHS):
            currentValue = atoi(current->Deaths);
            break;

            case(CONFIRMED):
            currentValue = atoi(current->Confirmed);
            break;
            
            case(ACTIVE):
            currentValue = atoi(current->Active);
            break;

            default:
            printf("wrotng key, exiting");
            exit(1);
         }
         PrintWithSpaces(currentValue,Scaler);
      current = current->Next;
    }
}