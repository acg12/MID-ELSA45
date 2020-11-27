struct patients
{
    char name[255];
    int day;
    char month[20];
    int year;
    patients *next, *prev;
};

char days[13][20] = {"0", "january", "february", "march",
                     "april", "may", "june", "july", "august",
                     "september", "october", "november", "december"};