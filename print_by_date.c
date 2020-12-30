#include "print_by_date.h"
#include "shared_library.h"

typedef struct InputFlags InputFlags;

void initInputFlags(InputFlags* inputFlags);
void toLower(int argc, char* argv[]);
void parseArgs(int argc, char* argv[], InputFlags* inputFlags);

void actOnInput2(InputFlags* inputFlags, AllCountriesData* allCountriesData)
{
    ContryData* ContryData = allCountriesData->Head;
    DataByDate* dataByDate;

    while (ContryData)
    {
        dataByDate = ContryData->DataByDateHead;

        while (dataByDate)
        {
            if (strstr(dataByDate->Date,inputFlags->Date) != NULL)
            {
                if (inputFlags->Active)
                {
                    printf("%s: %s\n", ContryData->CountryName, dataByDate->Active);
                }
                else if (inputFlags->Confirmed)
                {
                    printf("%s: %s\n", ContryData->CountryName, dataByDate->Confirmed);
                }
                else if (inputFlags->Death)
                {
                    printf("%s: %s\n", ContryData->CountryName, dataByDate->Deaths);
                }
                else if (inputFlags->Recovered)
                {
                    printf("%s: %s\n", ContryData->CountryName, dataByDate->Recovered);
                }               
            }
            
            dataByDate = dataByDate->Next;
        }

        ContryData = ContryData->NextContry;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("not enough arguments were given.\n");
        return -1;
    }
    
    InputFlags* inputFlags = (InputFlags*)malloc(sizeof(InputFlags));
    initInputFlags(inputFlags);
    parseArgs(argc,argv, inputFlags);
    AllCountriesData* allCountriesData = load_db();
    actOnInput2(inputFlags,allCountriesData);
    free(inputFlags);
    freeAllContriesData(allCountriesData);
    return 0;
}