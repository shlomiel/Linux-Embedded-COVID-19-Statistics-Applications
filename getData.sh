#!/bin/bash

getAllcountries()
{

    INDEX=0

    while IFS= read -r line; do
        if [[ -n $line ]]; then
            curl -s --location --request GET "https://api.covid19api.com/total/country/$line" > countries/$line.txt
            echo "Written $line"
            let INDEX+=1
        fi
    done < $1
}

changeFormatForAllCountrys()
{
    DIR="countries/"
    for filename in countries/*.txt; do
        tr '\{' '\n' < "$filename" > "$DIR"c.tmp
        grep -o 'Confirmed.*' < "$DIR"c.tmp > "$DIR"d.tmp
        tr -d '\}\}\]\[\"' < "$DIR"d.tmp > "$DIR"e.tmp
        tr -d '\n' < "$DIR"e.tmp > "$DIR"f.tmp
        tr ',' '\n' < "$DIR"f.tmp > "$filename"
        rm "$DIR"*.tmp
    done
}

mkdir countries
curl -s --location --request GET 'https://api.covid19api.com/countries' > countries/countries.txt
echo "downloading countries into countries.txt"
tr '\{' '\n' < countries/countries.txt > countries/formatedContries.tmp   # split to lines
tr '\}\,' ' ' < countries/formatedContries.tmp > countries/formatedCommaSeperaded.tmp
awk -F ':' '{print $3}' < countries/formatedCommaSeperaded.tmp > countries/a.tmp
awk -F ' ' '{print $1}' < countries/a.tmp > countries/b.tmp
tr -d '\"' < countries/b.tmp > countries.txt
sort countries.txt > countries2.txt
rm countries.txt
cat countries2.txt > countries.txt
mkdir countries_csv
rm countries/*.tmp
getAllcountries countries.txt
changeFormatForAllCountrys