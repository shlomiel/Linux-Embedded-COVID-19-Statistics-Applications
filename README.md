# Linux-Embedded-COVID-19-Statistics-Applications
Includes 
# a bash program that retrieves statistics for each country(except USA) in the world using REST APIs from the following link: https://documenter.getpostman.com/view/10808728/SzS8rjbc?version=latest
and saves them to local directory.

# 3 C programs that read the data and perform the following:
1)	Print all countries specific data according to:
i.	Date
ii.	Key (Confirmed, Death, Recovered, active)

2)Print a “graph” according to:
i.	country name
ii.	Key (Confirmed, Death, Recovered, active)

3)Export data by country to CSV

# a shared library that provides functionalities like load_db, load_country, iterate_by_key, get_next_element, etc... this library is compiled as a separate .so and used by
all first 3 C programs

Made By:
Artem Kuznetsov 
Shlomi Eliyahu 
Daniel Shaanan 



Instructions:
run in terminal: $export LD_LIBRARY_PATH=`pwd`
run bash scrip: $./getData.sh
build the project: $make
clean the project: $make clean
