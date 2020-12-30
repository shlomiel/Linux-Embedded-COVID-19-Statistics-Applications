#include "shared_library.c"

void parse_input(char* arguements[])
{
    if(strcmp("--country",arguements[1]) == 0 )
    {
        char fileName[255];
        char dirName[] = "countries_csv/";
        strcpy(fileName,dirName);
        strcat(fileName,arguements[2]);
        strcat(fileName,".csv");
        FILE* countryFile = fopen(fileName,"w+");
        ContryData* countryData = load_country(arguements[2]);
        DataByDate* currentDateData = countryData->DataByDateHead;
        fprintf(countryFile," , Date, Confirmed, Deaths, Recovered, Active");
        int rowCounter = 1;
        while (currentDateData!=NULL)
        {
            fprintf(countryFile, "\n%d,%s,%s,%s,%s,%s", rowCounter++, currentDateData->Date, 
            currentDateData->Confirmed, currentDateData->Deaths, currentDateData->Recovered, currentDateData->Active);
            currentDateData = currentDateData->Next;
        }
        fclose(countryFile);
    }   


}


int main(int argc,char* argv[])
{
    parse_input(argv);
}