/***************************************************************************************
CIS2750 F2017
Assignment 1
Gia Vinh Lam
0925571
****************************************************************************************/

#include "CalendarParser.h"
#include <ctype.h>

bool customCompare(const void *first, const void *second){
    if (first == NULL || second == NULL){
        return false;
    }

    if (strcmp(first, second) == 0){
        return true;
    }else{
        return false;
    }
}

int compareFunc(const void *first, const void *second)
{
	return strcmp((char*)first, (char*)second);
}

void deleteProperty(void * toBeDeleted)
{
    if (toBeDeleted != NULL)
        free(toBeDeleted);
    return;
}

void deleteAlarm(void * toBeDeleted)
{
    if (toBeDeleted != NULL)
    {
        Alarm * temp;
        temp = (Alarm*)toBeDeleted;
        free(temp->trigger);
        clearList(&temp->properties);
        free(temp);
    }
    return;
}

char * printAlarm(void * toBePrinted)
{
    if (toBePrinted != NULL)
    {
        char * toReturn;
        Alarm * temp = (Alarm *)toBePrinted;
        int length = strlen(temp->action) + strlen(temp->trigger);
        toReturn = (char *)malloc(sizeof(char) * (length + 50));
        sprintf(toReturn, "Action: %s\nTrigger: %s\n", temp->action, temp->trigger);
        return toReturn;
    }
    return NULL;
}

void deleteEvent(void * toBeDeleted)
{
    if (toBeDeleted != NULL)
    {
        Event * temp;
        temp = (Event*)toBeDeleted;
        clearList(&temp->alarms);
        clearList(&temp->properties);
        free(temp);
    }
    return;
}

char * printEvent(void * toBePrinted)
{
    if (toBePrinted != NULL)
    {
        char * toReturn;
        Alarm * temp = (Alarm *)toBePrinted;
        int length = strlen(temp->action) + strlen(temp->trigger);
        toReturn = (char *)malloc(sizeof(char) * (length + 50));
        sprintf(toReturn, "Action: %s\nTrigger: %s\n", temp->action, temp->trigger);
        return toReturn;
    }
    return NULL;
}

char * printProperty(void * toBePrinted)
{
    if (toBePrinted != NULL)
    {
        char * toReturn;
        Property * temp = (Property *)toBePrinted;
        int length = strlen(temp->propName + strlen(temp->propDescr));
        toReturn = (char *)malloc(sizeof(char) * (length + 50));
        sprintf(toReturn, "Name: %s\nDescription:%s\n", temp->propName, temp->propDescr);
        return toReturn;
    }
    return NULL;
}

/*
Calendar* createSimpleCalendar(char args[4][1000])
{
    int z = 0;
    printf("test%s\n", args[0]);
    printf("test%s\n", args[1]);
    printf("test%s\n", args[2]);
    printf("test%s\n", args[3]);
    Calendar * calendar = malloc(sizeof(Calendar));
    calendar->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
    calendar->events = initializeList(&printEvent, &deleteEvent, &compareFunc);
    Event * event = malloc(sizeof(Event));
    event->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
    event->alarms = initializeList(&printAlarm, &deleteAlarm, &compareFunc);

    calendar->version = atoi(args[0]);
    strcpy(calendar->prodID, args[1]);
    strcpy(event->UID, args[2]);
    char date[9];
    char time[7];
    char timeVerify[2];

    for (z = 0; z < 8; z++)
    {
        date[z] = args[3][z];
    } date[z] = '\0';

    for (z = 0; z < 6; z++)
    {
        time[z] = args[3][z+9];
    } time[z] = '\0';

    if (strlen(args[3]) == 16)
    {
        if (args[3][15] == 'Z')
        {
            timeVerify[0] = '1';
        }
    } timeVerify[1] = '\0';

    strcpy(event->creationDateTime.date, date);
    strcpy(event->creationDateTime.time, time);

    if (strcmp(timeVerify, "1") == 0)
    {
        event->creationDateTime.UTC = 1;
    }
    else
    {
        event->creationDateTime.UTC = 0;
    }

    insertBack(&calendar->events, event);
    return calendar;
}*/

Calendar* createSimpleCal(char args[4][1000])
{
    int z = 0;

    Calendar * calendar = malloc(sizeof(Calendar));
    calendar->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
    calendar->events = initializeList(&printEvent, &deleteEvent, &compareFunc);
    Event * event = malloc(sizeof(Event));
    event->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
    event->alarms = initializeList(&printAlarm, &deleteAlarm, &compareFunc);

    calendar->version = 2.0;
    strcpy(calendar->prodID, args[0]);
    strcpy(event->UID, args[1]);

    if (!(args[2] == NULL || args[2][0] == '\0'))
    {
    	char date1[9];
    	char time1[7];
    	char timeVerify1[2];

	for (z = 0; z < 8; z++)
	{
	    date1[z] = args[3][z];
	} date1[z] = '\0';

	for (z = 0; z < 6; z++)
        {
	    time1[z] = args[3][z+9];
	} time1[z] = '\0';

	if (strlen(args[3]) == 16)
	{
            if (args[3][15] == 'Z')
	    {
		timeVerify1[0] = '1';
	    }
	} timeVerify1[1] = '\0';

	strcpy(event->startDateTime.date, date1);
	strcpy(event->startDateTime.time, time1);

	if (strcmp(timeVerify1, "1") == 0)
	{
            event->startDateTime.UTC = 1;
	}
	else
	{
	    event->startDateTime.UTC = 0;
	}
    }

    char date[9];
    char time[7];
    char timeVerify[2];

    for (z = 0; z < 8; z++)
    {
        date[z] = args[3][z];
    } date[z] = '\0';

    for (z = 0; z < 6; z++)
    {
        time[z] = args[3][z+9];
    } time[z] = '\0';

    if (strlen(args[3]) == 16)
    {
        if (args[3][15] == 'Z')
        {
            timeVerify[0] = '1';
        }
    } timeVerify[1] = '\0';

    strcpy(event->creationDateTime.date, date);
    strcpy(event->creationDateTime.time, time);

    if (strcmp(timeVerify, "1") == 0)
    {
        event->creationDateTime.UTC = 1;
    }
    else
    {
        event->creationDateTime.UTC = 0;
    }

    insertBack(&calendar->events, event);
    return calendar;
}

Calendar * createEvent(char args[3][1000], Calendar** obj)
{
    int z = 0;

    Event * event = malloc(sizeof(Event));
    event->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
    event->alarms = initializeList(&printAlarm, &deleteAlarm, &compareFunc);
    strcpy(event->UID, args[0]);
    if (!(args[1] == NULL || args[1][0] == '\0'))
    {
    	char date1[9];
    	char time1[7];
    	char timeVerify1[2];

	for (z = 0; z < 8; z++)
	{
	    date1[z] = args[1][z];
	} date1[z] = '\0';

	for (z = 0; z < 6; z++)
        {
	    time1[z] = args[1][z+9];
	} time1[z] = '\0';

	if (strlen(args[1]) == 16)
	{
            if (args[1][15] == 'Z')
	    {
		timeVerify1[0] = '1';
	    }
	} timeVerify1[1] = '\0';

	strcpy(event->startDateTime.date, date1);
	strcpy(event->startDateTime.time, time1);
	if (strcmp(timeVerify1, "1") == 0)
	{
            event->startDateTime.UTC = 1;
	}
	else
	{
	    event->startDateTime.UTC = 0;
	}
    }

    char date[9];
    char time[7];
    char timeVerify[2];
    for (z = 0; z < 8; z++)
    {
        date[z] = args[2][z];
    } date[z] = '\0';

    for (z = 0; z < 6; z++)
    {
        time[z] = args[2][z+9];
    } time[z] = '\0';

    if (strlen(args[2]) == 16)
    {
        if (args[2][15] == 'Z')
        {
            timeVerify[0] = '1';
        }
    } timeVerify[1] = '\0';

    strcpy(event->creationDateTime.date, date);
    strcpy(event->creationDateTime.time, time);

    if (strcmp(timeVerify, "1") == 0)
    {
        event->creationDateTime.UTC = 1;
    }
    else
    {
        event->creationDateTime.UTC = 0;
    }

    insertBack(&(**obj).events, event);
    return *obj;
}


char * returnVersion(char * text)
{
    char textVerify[7];
    float versionConverted = 0.0;
    int j, i;
    int length;
    j = 0;
    size_t len = strlen(text);
    char * text2 = malloc(sizeof(char) * (len + 1 + 1));
    if (text[strlen(text)] != '\n')
    {
        strcpy(text2, text);
        text2[len] = '\n';
        text2[len+1] = '\0';
    }

    if (strlen(text) < 10)
    {
        free(text2);
        return NULL;
    }

    for (i = 0; i < 7; i++)
    {
         textVerify[i] = toupper(text2[i]);
    } 
    textVerify[i] = '\0';
    i++;

    if (strcmp(textVerify, "VERSION") == 0 && (text[7] == ';' || text[7] == ':'))
    {
        length = strlen(text2) - strlen(textVerify) - 1;
        char * version = malloc(sizeof(char) * (length + 1));
        while (text2[i] != '\n')
        {
             version[j] = text2[i];
             i++;
             j++;
        } version[j] = '\0';

        free(text2);
        if (sscanf(version, "%f", &versionConverted) == 1)
        {
            return version;
        }
        else
        {
            return NULL;
        }
    }
    free(text2);
    return NULL;
}

char * returnID(char * text)
{
    char textVerify[8];
    char * productID;
    int length = 0;
    int i, j;
    j = 0;
    size_t len = strlen(text);
    char * text2 = malloc(sizeof(char) * (len + 1 + 1));
    
    if (text[strlen(text)] != '\n')
    {
        strcpy(text2, text);
        text2[len] = '\n';
        text2[len+1] = '\0';
    }

    if (strlen(text) < 9)
    {
        return NULL;
    }

    for (i = 0; i < 6; i++)
    {
        textVerify[i] = text2[i];
    } 
    textVerify[i] = '\0';
    i++;

    if (strcmp(textVerify, "PRODID") == 0 && (text[6] == ';' || text[6] == ':'))
    {
        length = strlen(text2) - strlen(textVerify) - 1;
        productID = malloc(sizeof(char) * (length + 1));
        while (text2[i] != '\n')
        {
             productID[j] = text2[i];
             i++;
             j++;
        } productID[j] = '\0';
        free(text2);
        return productID;
    }
    free(text2);
    return NULL;
}

char * returnDT(char * text)
{
    char * returnAll;
    char date[9];
    char time[9];
    char timeVerify[2];

    if (!(strlen(text) == 23 || strlen(text) == 24))
    {
        return NULL;
    }

    if (!(text[7] == ':' || text[7] == ';'))
    {
        return NULL;
    }

    int i = 0;
    for (i = 0; i != strlen(text); i++)
    {
        if (text[i] == '#')
            return NULL;
    }

    for (i = 0; i < 8; i++)
    {
        date[i] = text[i+8];
    } date[i] = '\0';

    if (text[16] != 'T')
        return NULL;

    for (i = 0; i < 6; i++)
    {
        time[i] = text[i+17];
    } time[i] = '\0';

    timeVerify[0] = '0';

    if (strlen(text) == 24)
    {
        if (text[23] == 'Z')
        {
            timeVerify[0] = '1';
        }
    } timeVerify[1] = '\0';

    returnAll = malloc(sizeof(char) * (19 + 1));
    strcpy(returnAll, date);
    returnAll = strcat(returnAll, "#");
    returnAll = strcat(returnAll, time);
    returnAll = strcat(returnAll, "#");
    returnAll = strcat(returnAll, timeVerify);
    return returnAll;
}

int checkFile(char * fileName)
{
    if (fileName == NULL || fileName[0] == '\n' || fileName[0] == '\0')
    {
        return 1;
    }

    if (strlen(fileName) < 5)
    {
        return 1;
    }
    else
    {
        if (!(fileName[strlen(fileName)-1] == 's' && fileName[strlen(fileName)-2] == 'c' && fileName[strlen(fileName)-3] == 'i' && fileName[strlen(fileName)-4] == '.'))
        {
            return 1;
        }
    }

    return 0;
}

ICalErrorCode createCalendar(char* fileName, Calendar** obj)
{	
    (*obj) = malloc(sizeof(Calendar));
    (*obj)->events = initializeList(&printEvent, &deleteEvent, &compareFunc);
    (*obj)->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);

    if (checkFile(fileName) == 1)
    {
        deleteCalendar(*obj);
        *obj = NULL;
        return INV_FILE;
    }
    FILE * data = NULL;
    data = fopen(fileName, "r");
    int lineCount = 0;
    char dataText[10000];
    char * toFree = NULL;
    char * storedText[10000];
    char * stringSplit;
    int versionCount = 0;
    int idCount = 0;
    int uidCount = 0;
    int dtCount = 0;
    int startCount = 0;
    int eventCount = 0;
    int triggerCount = 0;
    int actionCount = 0;
    int t = 0;
    int i = 0;
    int z = 0;
    int lines = 0;
    int linesBackup = 0;
    //int dt = 0;
    int dtend = 0;
    int duration = 0;

    if (data != NULL)
    {
        while (fgets(dataText, 10000, data))
        {
            int p = 0;
            if (dataText[p] == ';' || dataText[p] == '\n')
            {
                continue;
            }

            if (!(dataText[strlen(dataText)-1] == '\n' && dataText[strlen(dataText)-2] == '\r'))
            {
                while (lines != 0)
                {
                    free(storedText[t]);
                    t++;
                    lines--;
                } t = 0;
                deleteCalendar(*obj);
                fclose(data);
                *obj = NULL;
                return INV_CAL;
            } 
            lineCount++;
            dataText[strlen(dataText)-2] = '\0';

                if (dataText[0] == ' ' || dataText[0] == '\t')
                {
                    char * tempLine = malloc(sizeof(char) * (strlen(dataText) + 1));
                    strcpy(tempLine, dataText+1);
                    //storedText[lineCount - 3] = realloc(storedText[lineCount - 3], strlen(storedText[lineCount - 3]) + strlen(tempLine) + 1);
                    //storedText[lineCount - 3] = strcat(storedText[lineCount - 3], tempLine);
                    storedText[lineCount - 2] = realloc(storedText[lineCount - 2], strlen(storedText[lineCount - 2]) + strlen(tempLine) + 1);
                    storedText[lineCount - 2] = strcat(storedText[lineCount - 2], tempLine);
                    memset(dataText, 0, sizeof(char));
                    free(tempLine);
                    lineCount--;
                }
                else
                {
                    //storedText[lineCount - 2] = malloc(sizeof(char) * (strlen(dataText) + 1));
                    //strcpy(storedText[lineCount - 2], dataText);
                    storedText[lineCount - 1] = malloc(sizeof(char) * (strlen(dataText) + 1));
                    strcpy(storedText[lineCount - 1], dataText);
                    memset(dataText, 0, sizeof(char));
                    lines++;
                }
        }

        while (i != strlen(storedText[lineCount - 1]))
        {
            storedText[lineCount - 1][i] = toupper(storedText[lineCount - 1][i]);
            i++;
        } storedText[lineCount - 1][i] = '\0'; 
        i = 0;

        if (!(strcmp(storedText[lineCount - 1], "END:VCALENDAR") == 0 || strcmp(storedText[lineCount - 1], "END;VCALENDAR") == 0))
        {
            while (lines != 0)
            {
                free(storedText[t]);
                t++;
                lines--;
            } t = 0;
	    deleteCalendar(*obj);
            *obj = NULL;
            fclose(data);
            return INV_CAL;
        } linesBackup = lines;

        while (lines != 0)
        {
            char * originalString = calloc(strlen(storedText[i])+1, sizeof(char));
            strcpy(originalString, storedText[i]);
            char * stringCheck = strtok(storedText[i], ";:");
            if (i == 0)
            {
                while (i != strlen(originalString))
                {
                    originalString[i] = toupper(originalString[i]);
                    i++;
                } originalString[i] = '\0';
                i = 0;
	        if (!(strcmp(originalString, "BEGIN:VCALENDAR") == 0 || strcmp(originalString, "BEGIN;VCALENDAR") == 0))
                {
                    deleteCalendar(*obj);
                    fclose(data);
                    *obj = NULL;
                    return INV_CAL;
                }
                free(originalString);
                memset(stringCheck, 0, sizeof(char));
                i++;
                lines--;
                continue;
            }
  	    if (stringCheck == NULL)
            {
                while (linesBackup != 0)
                {
                    free(storedText[t]);
                    t++;
                    linesBackup--;
                } t = 0;
                free(originalString);
                *obj = NULL;
                deleteCalendar(*obj);
                fclose(data);
                return INV_CAL;
            }

            while (t != strlen(stringCheck))
            {
                stringCheck[t] = toupper(stringCheck[t]);
                t++;
            } stringCheck[t] = '\0'; 
            t = 0;


            if (strcmp(stringCheck, "VERSION") == 0)
            {
                if (versionCount == 1)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    deleteCalendar(*obj);
                    free(originalString);
                    *obj = NULL;
                    fclose(data);
                    return DUP_VER;
                }
                toFree = returnVersion(originalString);
                if (toFree == NULL)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    free(originalString);
                    deleteCalendar(*obj);
                    *obj = NULL;
                    fclose(data);
                    return INV_VER;
                }
                (*obj)->version = strtof(toFree, NULL);
                free(toFree);
                versionCount = 1;

            }
            else if (strcmp(stringCheck, "PRODID") == 0)
            {
                if (idCount == 1)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    free(originalString);
                    deleteCalendar(*obj);
                    *obj = NULL;
                    fclose(data);
                    return DUP_PRODID;
                }

                toFree = returnID(originalString);
                if (toFree == NULL)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    free(originalString);
                    deleteCalendar(*obj);
                    *obj = NULL;
                    fclose(data);
                    return INV_PRODID;
                }
                strcpy((*obj)->prodID, toFree);
                free(toFree);
                idCount = 1;

            }
            else if (strcmp(stringCheck, "BEGIN") == 0)
            {
                while (t != strlen(originalString))
                {
                    originalString[t] = toupper(originalString[t]);
                    t++;
                } t = 0;

                if (strcmp(originalString, "BEGIN:VEVENT") != 0)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    free(originalString);
                    deleteCalendar(*obj);
                    *obj = NULL;
                    fclose(data);
                    return INV_CAL;
                }

                Event * event = malloc(sizeof(Event));
                event->properties = initializeList(&printProperty, &deleteProperty, &compareFunc);
                event->alarms = initializeList(&printAlarm, &deleteAlarm, &compareFunc);

                eventCount = 1;
                while (strcmp(originalString, "END:VEVENT") != 0)
                {
                    i++;
                    lines--;
                    free(originalString);
                    originalString = calloc(strlen(storedText[i])+1, sizeof(char));
                    strcpy(originalString, storedText[i]);
                    stringCheck = strtok(storedText[i], ";:");
                    if (stringCheck == NULL || storedText[i] == '\0')
                    {
                        while (linesBackup != 0)
                        {
                            free(storedText[t]);
                            t++;
                            linesBackup--;
                        } t = 0;
                        deleteEvent(event);
                        deleteCalendar(*obj);
                        *obj = NULL;
                        free(originalString);
                        fclose(data);
                        return INV_EVENT;
                    }

                    if (strcmp(stringCheck, "END") == 0)
                    {
                        while (t != strlen(originalString))
                        {
                            originalString[t] = toupper(originalString[t]);
                            t++;
                        } t= 0;
                        if (strcmp(originalString, "END:VCALENDAR") == 0)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            fclose(data);
                            *obj = NULL;
                            return INV_EVENT;
                        }
                        else if (strcmp(originalString, "END:VEVENT") == 0)
                        {
                            continue;
                        }
                    }

                    while (t != strlen(stringCheck))
                    {
                        stringCheck[t] = toupper(stringCheck[t]);
                        t++;
                    } t = 0;

                    if (strcmp(stringCheck, "UID") == 0)
                    {
                        if (strlen(originalString) < 5)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_EVENT;
                        }
                        if (!(originalString[3] == ':' || originalString[3] == ';'))
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_EVENT;
                        }
                        if (uidCount == 1)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            *obj = NULL;
                            fclose(data);
                            return INV_EVENT;
                        }
                        uidCount = 1;
                        stringCheck = strtok(NULL, ";:");
                        strcpy(event->UID, stringCheck);
                        memset(stringCheck, 0, sizeof(char));
                        continue;
                    }
                    else if (strcmp(stringCheck, "DTSTAMP") == 0)
                    {
                        if (dtCount == 1)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            *obj = NULL;
                            fclose(data);
                            return INV_CREATEDT;
                        }
                        toFree = returnDT(originalString);
                        if (toFree == NULL)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            *obj = NULL;
                            fclose(data);
                            return INV_CREATEDT;
                        }
                        dtCount = 1;

                        char * getDT = strtok(toFree, "#");
                        strcpy(event->creationDateTime.date, getDT);
                        getDT = strtok(NULL, "#");
                        strcpy(event->creationDateTime.time, getDT);
                        getDT = strtok(NULL, "#");

                        if (strcmp(getDT, "1") == 0)
                        {
                            event->creationDateTime.UTC = 1;
                        }
                        else
                        {
                            event->creationDateTime.UTC = 0;
                        }
                        free(toFree);
                        memset(stringCheck, 0, sizeof(char));
                        continue;
                    }
		    else if (strcmp(stringCheck, "DTSTART") == 0)
                    {
                        if (startCount == 1)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            *obj = NULL;
                            fclose(data);
                            return INV_EVENT;
                        }

                        toFree = returnDT(originalString);
                        if (toFree == NULL)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteEvent(event);
                            deleteCalendar(*obj);
                            free(originalString);
                            *obj = NULL;
                            fclose(data);
                            return INV_EVENT;
                        }
                        startCount = 1;

                        char * getDT = strtok(toFree, "#");
                        strcpy(event->startDateTime.date, getDT);
                        getDT = strtok(NULL, "#");
                        strcpy(event->startDateTime.time, getDT);
                        getDT = strtok(NULL, "#");

                        if (strcmp(getDT, "1") == 0)
                        {
                            event->startDateTime.UTC = 1;
                        }
                        else
                        {
                            event->startDateTime.UTC = 0;
                        }
                        free(toFree);
                        memset(stringCheck, 0, sizeof(char));
                        continue;
                    }

                    while (t != strlen(originalString) && strcmp(stringCheck, "BEGIN") == 0)
                    {
                        originalString[t] = toupper(originalString[t]);
                        t++;
                    } t = 0;

                    if (strcmp(originalString, "BEGIN:VALARM") == 0)
                    {
                            Alarm * alarm = malloc(sizeof(Alarm));
                            List property = initializeList(&printProperty, &deleteProperty, &compareFunc);
                            alarm->properties = property;
                            while (strcmp(originalString, "END:VALARM") != 0)
                            {
                                i++;
                                lines--;
                                free(originalString);
                                originalString = calloc(strlen(storedText[i])+1, sizeof(char));
                                if (originalString == NULL)
                                {
                                    while (linesBackup != 0)
                                    {
                                        free(storedText[t]);
                                        t++;
                                        linesBackup--;
                                    } t = 0;
                                    deleteAlarm(alarm); //check out?
                                    deleteEvent(event);
                                    deleteCalendar(*obj);
                                    free(originalString);
                                    *obj = NULL;
                                    fclose(data);
                                    return OTHER_ERROR;
                                }
                                strcpy(originalString, storedText[i]);
                                stringCheck = strtok(storedText[i], ";:");
                                if (stringCheck == NULL || originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':')
                                {
                                    while (linesBackup != 0)
                                    {
                                        free(storedText[t]);
                                        t++;
                                        linesBackup--;
                                    } t = 0;
                                    deleteAlarm(alarm);
                                    deleteEvent(event);
                                    deleteCalendar(*obj);
                                    free(originalString);
                                    *obj = NULL;
                                    fclose(data);
                                    return INV_ALARM;
                                }

                                while (t != strlen(stringCheck))
                                {
                                    stringCheck[t] = toupper(stringCheck[t]);
                                    t++;
                                } t = 0;

                                if (strcmp(stringCheck, "TRIGGER") == 0)
                                {
                                      if (originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':' || triggerCount == 1)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          deleteAlarm(alarm);
                                          deleteEvent(event);
                                          deleteCalendar(*obj);
                                          free(originalString);
                                          *obj = NULL;
                                          fclose(data);
                                          return INV_ALARM;
                                      }

                                      stringSplit = malloc(sizeof(char) * (strlen(originalString) + 1));
                                      if (stringSplit == NULL)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          deleteAlarm(alarm);
                                          deleteEvent(event);
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return OTHER_ERROR;
                                      }

                                      while (t != strlen(originalString))
                                      {
                                          t++;
                                          if (originalString[t-1] == ':' || originalString[t-1] == ';' || z > 0)
                                          {
                                              stringSplit[z] = originalString[t];
                                              z++;
                                          }
                                      } t = 0;

                                      alarm->trigger = malloc(sizeof(char) * (strlen(stringSplit) + 1));
                                      strcpy(alarm->trigger, stringSplit);
                                      free(stringSplit);
                                      triggerCount = 1;
                                }
                                else if (strcmp(stringCheck, "ACTION") == 0)
                                {
                                      if (originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':' || actionCount == 1)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          deleteAlarm(alarm);
                                          deleteEvent(event);
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);

                                          return INV_ALARM;
                                      }

                                      stringSplit = malloc(sizeof(char) * (strlen(originalString) + 1));
                                      if (stringSplit == NULL)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          deleteAlarm(alarm);
                                          deleteEvent(event);
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return OTHER_ERROR;
                                      }

                                      while (t != strlen(originalString))
                                      {
                                          t++;
                                          if (originalString[t-1] == ':' || originalString[t-1] == ';' || z > 0)
                                          {
                                              stringSplit[z] = originalString[t];
                                              z++;
                                          }
                                      } t = 0;
                                      z = 0;
                                      strcpy(alarm->action, stringSplit);
                                      free(stringSplit);
                                      actionCount = 1;
                                }
                                else if (strcmp(stringCheck, "END") == 0)
                                {
                                    while (t != strlen(originalString))
                                    {
                                        t++;
                                        originalString[t] = toupper(originalString[t]);
                                    } t = 0;
                                    if (strcmp(originalString, "END:VALARM") == 0)
                                    {
                                        continue;
                                    }
                                }
                                else
                                {
                                      if (originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':' || originalString[0] == ':')
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return INV_ALARM;
                                      }

                                      stringSplit = malloc(sizeof(char) * (strlen(originalString) + 1));
                                      if (stringSplit == NULL)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              linesBackup--;
                                              free(storedText[t]);
                                              t++;
                                          } t = 0;
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return OTHER_ERROR;
                                      }
			              z = 0;
				      t = 0;
                                      while (t != strlen(originalString))
                                      {
                                          t++;
                                          if (originalString[t-1] == ':' || originalString[t-1] == ';' || z > 0)
                                          {
                                              stringSplit[z] = originalString[t];
                                              z++;
                                          }
                                      } t = 0;
                                      z = 0;

                                      Property * property = malloc(sizeof(Property) + (strlen(originalString)+1) * sizeof(char));
 
                                      if (findElement(alarm->properties, &customCompare, stringCheck) != NULL)
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          free(property);
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return INV_ALARM;
                                      }
                                      strcpy(property->propName, stringCheck);
                                      strcpy(property->propDescr, stringSplit);

                                      if (!(strcmp(property->propName, "ATTACH") == 0 || strcmp(property->propName, "DESCRIPTION") == 0 || strcmp(property->propName, "SUMMARY") == 0 || strcmp(property->propName, "DURATION") == 0 || strcmp(property->propName, "REPEAT") == 0)) // add all accept properties here // attach lower case would work ?
                                      {
                                          while (linesBackup != 0)
                                          {
                                              free(storedText[t]);
                                              t++;
                                              linesBackup--;
                                          } t = 0;
                                          free(property);
                                          deleteCalendar(*obj);
                                          *obj = NULL;
                                          free(originalString);
                                          fclose(data);
                                          return INV_ALARM; //DESCRIPTION may have more parsing needed
                                      } //think it needs only duration? confirm

                                      insertBack(&alarm->properties, property);
                                      free(stringSplit);
                                }
                                if (strcmp(originalString, "END:VCALENDAR") == 0)
                                {
                                    while (linesBackup != 0)
                                    {
                                        free(storedText[t]);
                                        t++;
                                        linesBackup--;
                                    } t = 0;
                                    deleteCalendar(*obj);
                                    *obj = NULL;
                                    free(originalString);
                                    fclose(data);
                                    return INV_ALARM;
                                }
                                memset(stringCheck, 0, sizeof(char));
                            }
                            insertBack(&event->alarms, alarm);

                            if (!(triggerCount == 1 && actionCount == 1))
                            {
                                while (linesBackup != 0)
                                {
                                    free(storedText[t]);
                                    t++;
                                    linesBackup--;
                                } t = 0;
                                deleteCalendar(*obj);
                                free(originalString);
                                *obj = NULL;
                                fclose(data);
                                return INV_ALARM;
                            }
                            triggerCount = 0;
                            actionCount = 0;
                    }
                    else
                    {
                        if (originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':' || originalString[0] == ':')
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_EVENT;
                        }
                        Property * property = malloc(sizeof(Property) + (strlen(originalString)+1) * sizeof(char));
                        strcpy(property->propName, stringCheck);

                        if (findElement(event->properties, &customCompare, stringCheck) != NULL)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                           free(property);
                           deleteCalendar(*obj);
                           *obj = NULL;
                           free(originalString);
                           fclose(data);
                           return INV_EVENT;
                       }

                        if (!(strcmp(property->propName, "ATTACH") == 0 || strcmp(property->propName, "CATEGORIES") == 0 || strcmp(property->propName, "CLASS") == 0 || strcmp(property->propName, "COMMENT") == 0 || strcmp(property->propName, "DESCRIPTION") == 0 || strcmp(property->propName, "COMMENT") == 0 || strcmp(property->propName, "GEO") == 0 || strcmp(property->propName, "LOCATION") == 0 || strcmp(property->propName, "PRIORITY") == 0 || strcmp(property->propName, "RESOURCES") == 0 || strcmp(property->propName, "STATUS") == 0 || strcmp(property->propName, "SUMMARY") == 0 || strcmp(property->propName, "DTSTART") == 0 || strcmp(property->propName, "DTEND") == 0 || strcmp(property->propName, "DURATION") == 0 || strcmp(property->propName, "TRANSP") == 0 || strcmp(property->propName, "CONTACT") == 0 || strcmp(property->propName, "RELATED-TO") == 0 || strcmp(property->propName, "URL") == 0 || strcmp(property->propName, "EXDATE") == 0 || strcmp(property->propName, "URL") == 0 || strcmp(property->propName, "URL") ==  0 || strcmp(property->propName, "ORGANIZER") ==  0 || strcmp(property->propName, "CREATED") ==  0 || strcmp(property->propName, "LAST-MODIFIED") ==  0 || strcmp(property->propName, "SEQUENCE") ==  0 || strcmp(property->propName, "RRULE") ==  0 || strcmp(property->propName, "RDATE") ==  0 || strcmp(property->propName, "EXDATE") ==  0))
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            free(property);
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_EVENT;
                        }
                        if ((strcmp(property->propName, "DTEND") == 0 || strcmp(property->propName, "DURATION") == 0) && (startCount == 0 || dtend == 1 || duration == 1))
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            free(property);
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_EVENT;
                        }

                        if (strcmp(property->propName, "DTEND") == 0)
                            dtend = 1;

                        if (strcmp(property->propName, "DURATION") == 0)
                            duration = 1;

                        memset(stringCheck, 0, sizeof(char));
                        char * stringSplit = malloc(sizeof(char) * (strlen(originalString) + 1));
			memset(stringSplit, 0, sizeof(char));
                        if (stringSplit == NULL)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return OTHER_ERROR;
                        }
                        z = 0;
                        t = 0;

                        while (t != strlen(originalString))
                        {
                            t++;
                            if (originalString[t-1] == ':' || originalString[t-1] == ';' || z > 0)
                            {
                                stringSplit[z] = originalString[t];
                                z++;
                            }
                        } t = 0;
                        z = 0;
                        strcpy(property->propDescr, stringSplit);
                        insertBack(&event->properties, property);
                        memset(originalString, 0, sizeof(char));
                        free(stringSplit);
                    }
                }
                if (uidCount == 0 || dtCount == 0)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    deleteCalendar(*obj);
                    free(originalString);
                    *obj = NULL;
                    fclose(data);
                    return INV_EVENT;
                }  
                dtend = 0; duration = 0;
                uidCount = 0;
                dtCount = 0;
		startCount = 0;
                insertBack(&(**obj).events, event);   
            }
            else
            { //check for lowercase versions

                if (originalString[strlen(originalString)-1] == ';' || originalString[strlen(originalString)-1] == ':' || originalString[0] == ':' || stringCheck == NULL)
                {
                    while (linesBackup != 0)
                    {
                        free(storedText[t]);
                        t++;
                        linesBackup--;
                    } t = 0;
                    deleteCalendar(*obj);
                    *obj = NULL;
                    free(originalString);
                    fclose(data);
                    return INV_CAL;
                }

                if (strcmp(originalString, "END:VCALENDAR") != 0)
                {
                    if (strcmp(stringCheck, "CALSCALE") == 0 || strcmp(stringCheck, "METHOD") == 0)
                    {
                        Property * property = malloc(sizeof(Property) + (sizeof(char) * strlen(originalString)+1));

                        if (findElement((*obj)->properties, &customCompare, stringCheck) != NULL)
                        {
                            while (linesBackup != 0)
                            {
                                free(storedText[t]);
                                t++;
                                linesBackup--;
                            } t = 0;
                            free(property);
                            deleteCalendar(*obj);
                            *obj = NULL;
                            free(originalString);
                            fclose(data);
                            return INV_CAL;
                        }

                        strcpy(property->propName, stringCheck);
                        stringCheck = strtok(NULL, ";:");
                        strcpy(property->propDescr, stringCheck);
                        insertBack(&(**obj).properties, property);  
                        memset(originalString, 0, sizeof(char));
                    }
                    else
                    {
                        while (linesBackup != 0)
                        {
                            free(storedText[t]);
                            t++;
                            linesBackup--;
                        } t = 0;
                        deleteCalendar(*obj);
                        *obj = NULL;
                        free(originalString);
                        fclose(data);
                        return INV_CAL;
                    }
                }
            }
            free(originalString);
            memset(stringCheck, 0, sizeof(char));
            i++;
            lines--;
        }
    }
    else
    {
        while (linesBackup != 0)
        {
            free(storedText[t]);
            t++;
            linesBackup--;
        } t = 0;
        deleteCalendar(*obj);
        *obj = NULL;
        return INV_FILE;
    }

    if (idCount == 0 || versionCount == 0 || eventCount == 0)
    {
        while (linesBackup != 0)
        {
            free(storedText[t]);
            t++;
            linesBackup--;
        } t = 0;
        deleteCalendar(*obj);
        *obj = NULL;
        fclose(data);
        return INV_CAL;
    }
    fclose(data);
    while (linesBackup != 0)
    {
        free(storedText[t]);
        linesBackup--;
        t++;
    }
    return OK;
}

void deleteCalendar(Calendar* obj)
{
    if (obj != NULL)
    {
        clearList(&obj->events);
        clearList(&obj->properties);
        free(obj);
    }
    return;
}

/*
char* printCalendar(const Calendar* obj)
{
    ListIterator iterP, iterE, iter, iter2, iter3;
    if (obj == NULL)
    {
        return NULL;
    }
    char * string = (char*)malloc(sizeof(char) * 100);
    char * concactenate = (char*)malloc(sizeof(char) * 100);
    int eventCount, alarmCount, propCount;
    eventCount = 0;
    alarmCount = 0;
    propCount = 0;

    memset(string, 0, sizeof(char));
    memset(concactenate, 0, sizeof(char));

    sprintf(string, "%s", "Allocated object\n");
    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 100);
    strcat(concactenate, string);
    sprintf(string, "%s", "File parsed successfully\n");
    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
    strcat(concactenate, string);
    sprintf(string, "Calendar: version = %lf, prodID = %s\n", obj->version, obj->prodID);
    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
    strcat(concactenate, string);
    
    sprintf(string, "%s", "Properties\n");
    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
    strcat(concactenate, string);
    if (obj->properties.head != NULL)
    {
        iterP = createIterator(obj->properties);
        void * elemP;
        
	while ((elemP = nextElement(&iterP)) != NULL)
        {
            Property * property = (Property*)elemP;
	    string = realloc(string, 100 + strlen(property->propName) + strlen(property->propDescr));
            sprintf(string, "\t%s:%s\n", property->propName, property->propDescr);
            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            strcat(concactenate, string);
        }
    }
    
    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        void * elemE;

	while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;
            sprintf(string, "%s", "\nEvent\n");
            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            strcat(concactenate, string);
            sprintf(string, "\tUID = %s\n", event->UID);
            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            strcat(concactenate, string);
            sprintf(string, "\tcreationDateTime = %s:%s, UTC=%d\n", event->creationDateTime.date, event->creationDateTime.time, event->creationDateTime.UTC);
            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            strcat(concactenate, string);

            if (event->alarms.head != NULL)
            {
                iter = createIterator(event->alarms);
                void * elem;
                sprintf(string, "%s", "\tAlarms:");
                concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                strcat(concactenate, string);
	        while ((elem = nextElement(&iter)) != NULL)
                {
		    Alarm * alarm = (Alarm*)elem;
                    string = realloc(string, 100 + strlen(alarm->action));
                    sprintf(string, "\n\t\tAction: %s\n", alarm->action);
        	    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                    strcat(concactenate, string);
                    string = realloc(string, 100 + strlen(alarm->trigger));
                    sprintf(string, "\t\tTrigger: %s\n", alarm->trigger);
		    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                    strcat(concactenate, string);
                    sprintf(string, "%s", "\t\tProperties:\n");
		    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                    strcat(concactenate, string);
		    if (alarm->properties.head != NULL)
                    {
                        void * elem2;
                        iter2 = createIterator(alarm->properties);
                        while ((elem2 = nextElement(&iter2)) != NULL)
                        {
                            Property * propertyValues = (Property*)elem2;
                            string = realloc(string, 100 + strlen(propertyValues->propName) + strlen(propertyValues->propDescr));
                            sprintf(string, "\t\t- %s:%s\n", propertyValues->propName, propertyValues->propDescr);
                            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                            strcat(concactenate, string);
                        }
                    }
	        }
            }

            sprintf(string, "%s", "\n\n\tOther properties:\n");
            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            strcat(concactenate, string);
    
            if (event->properties.head != NULL)
            {
                void * elem3;
                iter3 = createIterator(event->properties);

                while ((elem3 = nextElement(&iter3)) != NULL)
                {
                    Property * propertyValues2 = (Property*)elem3;
	            string = realloc(string, 100 + strlen(propertyValues2->propName) + strlen(propertyValues2->propDescr));
                    sprintf(string, "\t\t-%s:%s\n", propertyValues2->propName, propertyValues2->propDescr);
                    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                    strcat(concactenate, string);
                }
            }
        }
    }

    free(string);
    return concactenate;
}
*/

char* printCalendar(const Calendar* obj)
{
    ListIterator iterE, iter, iter3; //iter2 alarms
    if (obj == NULL)
    {
        return NULL;
    }
    char * string = (char*)malloc(sizeof(char) * 100);
    char * concactenate = (char*)malloc(sizeof(char) * 100);
    //int eventCount,
    int alarmCount, propCount;
    alarmCount = 0;
    propCount = 0;
    //eventCount = 0;
    memset(string, 0, sizeof(char));
    memset(concactenate, 0, sizeof(char));

    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        void * elemE;

	while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;

	    if (event->properties.head != NULL)
            {
                void * elem3;
                iter3 = createIterator(event->properties);

                while ((elem3 = nextElement(&iter3)) != NULL)
                {
                    Property * propertyValues2 = (Property*)elem3;
		    propCount++;
                    if (strcmp(propertyValues2->propName, "SUMMARY") == 0 || strcmp(propertyValues2->propName, "summary") == 0)
                    {
	                string = realloc(string, 100 + strlen(propertyValues2->propName) + strlen(propertyValues2->propDescr));
                        sprintf(string, "%s:%s", propertyValues2->propName, propertyValues2->propDescr);
                        concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                        strcat(concactenate, string);
                    }
                }
            }

            if (event->alarms.head != NULL)
            {
                iter = createIterator(event->alarms);
                void * elem;
	        while ((elem = nextElement(&iter)) != NULL)
                {
	            alarmCount++;
	        }
            }

            string = realloc(string, 100);
	    sprintf(string, "%d", alarmCount);
	    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
	    strcat(concactenate, string);
            string = realloc(string, 100);
	    sprintf(string, "%d%s", propCount, "$*%*$");
	    concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
	    strcat(concactenate, string);
	    alarmCount = 0;
            propCount = 0;
        }
    }

    free(string);
    return concactenate;
}

char* printEventProps(const Calendar* obj, char * eventWanted)
{
    ListIterator iterE, iter3;
    if (obj == NULL)
    {
        return NULL;
    }
    int eventCount = 0;
    int eventW = atoi(eventWanted);
    char * string = (char*)malloc(sizeof(char) * 100);
    char * concactenate = (char*)malloc(sizeof(char) * 100);
    memset(string, 0, sizeof(char));
    memset(concactenate, 0, sizeof(char));

    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        void * elemE;

	while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;
	    eventCount++;

            if (eventCount == eventW)
	    {
            	sprintf(string, "%s%d%s", "\nOptional Properties of Event ", eventW, ":\n");
            	concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            	strcat(concactenate, string);
	        if (event->properties.head != NULL)
                {
                    void * elem3;
                    iter3 = createIterator(event->properties);

                    while ((elem3 = nextElement(&iter3)) != NULL)
                    {
		            Property * propertyValues2 = (Property*)elem3;
			    string = realloc(string, 100 + strlen(propertyValues2->propName) + strlen(propertyValues2->propDescr));
		            sprintf(string, "\t-%s:%s\n", propertyValues2->propName, propertyValues2->propDescr);
		            concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
		            strcat(concactenate, string);
                    }
                }
            }
        }
    }

    free(string);
    return concactenate;
}

char* printEventAlarms(const Calendar* obj, char * eventWanted)
{
    ListIterator iterE, iter, iter2;
    if (obj == NULL)
    {
        return NULL;
    }
    int eventCount = 0;
    int eventW = atoi(eventWanted);
    char * string = (char*)malloc(sizeof(char) * 100);
    char * concactenate = (char*)malloc(sizeof(char) * 100);
    memset(string, 0, sizeof(char));
    memset(concactenate, 0, sizeof(char));

    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        void * elemE;

	while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;
	    eventCount++;

            if (eventCount == eventW)
	    {
            	sprintf(string, "%s%d%s", "\nAlarms of Event ", eventW, ":\n");
            	concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
            	strcat(concactenate, string);

            	if (event->alarms.head != NULL)
           	{
                    iter = createIterator(event->alarms);
                    void * elem;

	            while ((elem = nextElement(&iter)) != NULL)
                    {
		        Alarm * alarm = (Alarm*)elem;

                        string = realloc(string, 100 + strlen(alarm->action));
                        sprintf(string, "\n\tAction: %s\n", alarm->action);
        	        concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                        strcat(concactenate, string);
                        string = realloc(string, 100 + strlen(alarm->trigger));
                        sprintf(string, "\tTrigger: %s\n", alarm->trigger);
		        concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                        strcat(concactenate, string);
                        sprintf(string, "%s", "\tProperties:\n");
		        concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                        strcat(concactenate, string);
		        if (alarm->properties.head != NULL)
                        {
                            void * elem2;
                            iter2 = createIterator(alarm->properties);
                            while ((elem2 = nextElement(&iter2)) != NULL)
                            {
                                Property * propertyValues = (Property*)elem2;
                                string = realloc(string, 100 + strlen(propertyValues->propName) + strlen(propertyValues->propDescr));
                                sprintf(string, "\t\t- %s:%s\n", propertyValues->propName, propertyValues->propDescr);
                                concactenate = realloc(concactenate, strlen(string) + strlen(concactenate) + 10);
                                strcat(concactenate, string);
                            }
                        }
	            }
                }
 	    }
        }
    }
    free(string);
    return concactenate;
}

ICalErrorCode writeCalendar(char* fileName, const Calendar * obj)
{
    if (obj == NULL || fileName == NULL)
    {
        return WRITE_ERROR;
    } 

    if (strlen(fileName) < 5)
    {
        return WRITE_ERROR;
    }

    if (!(fileName[strlen(fileName)-1] == 's' || fileName[strlen(fileName)-2] == 'c' || fileName[strlen(fileName)-3] == 'i' ||  fileName[strlen(fileName)-4] == '.'))
    {
        return WRITE_ERROR;
    }

    if (strcmp(fileName, "") == 0 || strcmp(fileName, " ") == 0)
    {
        return WRITE_ERROR;
    } 

    char * temp = malloc(sizeof(char) * 10);
    temp = printError(validateCalendar(obj));
    if (strcmp(temp, "OK") != 0)
    {
        return WRITE_ERROR;
    }
/*
    FILE * file = fopen(fileName, "r");
    char input[1000];

    memset(input, 0, sizeof(char));
    if (file != NULL)
    {
        printf("Would you like to overwrite the existing file? Enter Y/N\n");
        getchar();
        fgets(input, 1000, stdin);
        input[strlen(input)-1] = '\0';
        if (strcmp(input, "Y") != 0)
        {
            fclose(file);
            return WRITE_ERROR;
        }
    }
*/

    FILE * newFile = fopen(fileName, "w");
    fprintf(newFile, "BEGIN:VCALENDAR\r\n");
    fprintf(newFile, "VERSION:%f\r\n", obj->version);
    fprintf(newFile, "PRODID:%s\r\n", obj->prodID);
    ListIterator iterP, iterE, iter, iter2, iter3;  

    if (obj->properties.head != NULL)
    {
        iterP = createIterator(obj->properties);
        void * elemP;

        while ((elemP = nextElement(&iterP)) != NULL)
        {
            Property * property = (Property*)elemP;
            fprintf(newFile, "%s:%s\r\n", property->propName, property->propDescr);
        }
    }

    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        void * elemE;

        while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;
            fprintf(newFile, "BEGIN:VEVENT\r\n");
            fprintf(newFile, "UID:%s\r\n", event->UID);
            fprintf(newFile, "DTSTAMP:%sT%s", event->creationDateTime.date, event->creationDateTime.time);
            if (event->creationDateTime.UTC)
            {
                fprintf(newFile, "Z\r\n");
            }
            else
            {
                fprintf(newFile, "\r\n");
            }

            if (strcmp(event->startDateTime.date, "") != 0)
            {
	        fprintf(newFile, "DTSTART:%sT%s", event->startDateTime.date, event->startDateTime.time);
                if (event->startDateTime.UTC)
                {
                     fprintf(newFile, "Z\r\n");
                }
                 else
                {
                    fprintf(newFile, "\r\n");
                }
            }


            if (event->properties.head != NULL)
            {
                void * elem3;
                iter3 = createIterator(event->properties);

                while ((elem3 = nextElement(&iter3)) != NULL)
                {
                    Property * propertyValues = (Property*)elem3;
                    fprintf(newFile, "%s:%s\r\n", propertyValues->propName, propertyValues->propDescr);
                }
            }

            if (event->alarms.head != NULL)
            {
                iter = createIterator(event->alarms);
                void * elemA;
	        while ((elemA = nextElement(&iter)) != NULL)
                {
                    Alarm * alarm = (Alarm*)elemA;
                    fprintf(newFile, "BEGIN:VALARM\r\n");
                    fprintf(newFile, "ACTION:%s\r\n", alarm->action);
                    fprintf(newFile, "TRIGGER:%s\r\n", alarm->trigger);


	                if (alarm->properties.head != NULL)
                        {
                        void * elem2;
                        iter2 = createIterator(alarm->properties);
                        while ((elem2 = nextElement(&iter2)) != NULL)
                        {
                            Property * propertyValues2 = (Property*)elem2;
                            fprintf(newFile, "%s:%s\r\n", propertyValues2->propName, propertyValues2->propDescr);
                        }
                    }
                    fprintf(newFile, "END:VALARM\r\n");
                }
            }
        fprintf(newFile, "END:VEVENT\r\n");
        }
    fprintf(newFile, "END:VCALENDAR\r\n");
    }    
    fclose(newFile);
    return OK;
}

ICalErrorCode validateCalendar(const Calendar * obj)
{
    if (obj == NULL)
    {
        return OTHER_ERROR;
    }

    int eventCheck, dtCheck, dtendCheck, durationCheck, methodCheck, calCheck;
    methodCheck = 0;
    calCheck = 0;
    eventCheck = 0;
    dtCheck = 0;
    dtendCheck = 0;
    durationCheck = 0;
    ListIterator iterP, iterE, iter, iter2, iter3;
    char * duplicates = malloc(sizeof(char));
    memset(duplicates, 0, sizeof(char));

    if (obj->version == 0)
    {
        return INV_CAL;
    }
    if (obj->prodID == NULL || strcmp(obj->prodID, "") == 0)
    {
        return INV_CAL;
    }

    if (obj->properties.head != NULL)
    {
        iterP = createIterator(obj->properties);
        void * elemP;
        
	while ((elemP = nextElement(&iterP)) != NULL)
        {
            Property * property = (Property*)elemP;
            if (property->propDescr == NULL || strcmp(property->propDescr, "") == 0)
            {
                free(duplicates);
                return INV_CAL;
            }

            if (!(strcmp(property->propName, "CALSCALE") == 0 || strcmp(property->propName, "METHOD") == 0))
            {
                free(duplicates);
                return INV_CAL;
            }

            if (strcmp(property->propName, "CALSCALE") == 0)
            {
                if (calCheck == 0)
                {
                    calCheck = 1;
                }
                else
                {
                    free(duplicates);
                    return INV_CAL;
                }
            }

            if (strcmp(property->propName, "METHOD") == 0)
            {
                if (methodCheck == 0)
                {
                    methodCheck = 1;
                }
                else
                {
                    free(duplicates);
                    return INV_CAL;
                }
            }
        }
    }

    if (obj->events.head != NULL)
    {
        iterE = createIterator(obj->events);
        eventCheck = 1;
        void * elemE;

        while ((elemE = nextElement(&iterE)) != NULL)
        {
            Event * event = (Event*)elemE;
            if (event->UID == NULL || strcmp(event->UID, "") == 0)
            {
                free(duplicates);
                return INV_EVENT;
            }

            if (event->creationDateTime.time == NULL || event->creationDateTime.date == NULL)
            {
                free(duplicates);
                return INV_EVENT;
            }

            if (!(event->creationDateTime.time == NULL || strcmp(event->creationDateTime.date, "") == 0))
            {
                dtCheck = 1;
            }

            if (strcmp(event->creationDateTime.time, "") == 0 || strcmp(event->creationDateTime.time, "") == 0)
            {
                free(duplicates);
                return INV_EVENT;
            }

            if (strcmp(event->creationDateTime.time, "") == 0 || strcmp(event->creationDateTime.time, "") == 0)
            {
                free(duplicates);
                return INV_EVENT;
            }

            if (event->properties.head != NULL)
            {
                void * elem3;
                iter3 = createIterator(event->properties);
                while ((elem3 = nextElement(&iter3)) != NULL)
                {
                    Property * propertyValues2 = (Property*)elem3;
                    if (propertyValues2->propDescr == NULL || strcmp(propertyValues2->propDescr, "") == 0)
                    {
                        return INV_EVENT;
                    }
                    if (strstr(duplicates, propertyValues2->propName) != NULL)
                        return INV_EVENT;

	            duplicates = realloc(duplicates, strlen(duplicates) + strlen(propertyValues2->propName) + 1);
                    duplicates = strcat(duplicates, propertyValues2->propName);
		    //took out dtstart
                    if (!(strcmp(propertyValues2->propName, "ATTACH") == 0 || strcmp(propertyValues2->propName, "CATEGORIES") == 0 || strcmp(propertyValues2->propName, "CLASS") == 0 || strcmp(propertyValues2->propName, "COMMENT") == 0 || strcmp(propertyValues2->propName, "DESCRIPTION") == 0 || strcmp(propertyValues2->propName, "COMMENT") == 0 || strcmp(propertyValues2->propName, "GEO") == 0 || strcmp(propertyValues2->propName, "LOCATION") == 0 || strcmp(propertyValues2->propName, "PRIORITY") == 0 || strcmp(propertyValues2->propName, "RESOURCES") == 0 || strcmp(propertyValues2->propName, "STATUS") == 0 || strcmp(propertyValues2->propName, "SUMMARY") == 0 || strcmp(propertyValues2->propName, "DTEND") == 0 || strcmp(propertyValues2->propName, "DURATION") == 0 || strcmp(propertyValues2->propName, "TRANSP") == 0 || strcmp(propertyValues2->propName, "CONTACT") == 0 || strcmp(propertyValues2->propName, "RELATED-TO") == 0 || strcmp(propertyValues2->propName, "URL") == 0 || strcmp(propertyValues2->propName, "EXDATE") == 0 || strcmp(propertyValues2->propName, "URL") == 0 || strcmp(propertyValues2->propName, "URL") ==  0 || strcmp(propertyValues2->propName, "ORGANIZER") ==  0 || strcmp(propertyValues2->propName, "CREATED") ==  0 || strcmp(propertyValues2->propName, "LAST-MODIFIED") ==  0 || strcmp(propertyValues2->propName, "SEQUENCE") ==  0 || strcmp(propertyValues2->propName, "RRULE") ==  0 || strcmp(propertyValues2->propName, "RDATE") ==  0 || strcmp(propertyValues2->propName, "EXDATE") ==  0))
                    {
                        return INV_EVENT;
                    }
                    if ((strcmp(propertyValues2->propName, "DTEND") == 0 || strcmp(propertyValues2->propName, "DURATION") == 0) && (dtCheck != 1 || dtendCheck == 1 || durationCheck == 1))
                    {
                        return INV_EVENT;
                    }

                    if (strcmp(propertyValues2->propName, "DTEND") == 0)
                        dtendCheck = 1;

                    if (strcmp(propertyValues2->propName, "DURATION") == 0) 
                        durationCheck = 1;
                }
                free(duplicates);
                duplicates = malloc(sizeof(char));
                memset(duplicates, 0, sizeof(char));
                dtCheck = 0; dtendCheck = 0; durationCheck = 0;
            }

            if (event->alarms.head != NULL)
            {
                iter = createIterator(event->alarms);
                void * elem;
	        while ((elem = nextElement(&iter)) != NULL)
                {
		    Alarm * alarm = (Alarm*)elem;
                    if (alarm->action == NULL || strcmp(alarm->action, "") == 0 || alarm->trigger == NULL || strcmp(alarm->trigger, "") == 0)
                    {
                        free(duplicates);
                        return INV_ALARM;
                    }

		    if (alarm->properties.head != NULL)
                    {
                        void * elem2;
                        iter2 = createIterator(alarm->properties);

                        while ((elem2 = nextElement(&iter2)) != NULL)
                        {
                            Property * propertyValues = (Property*)elem2;
                            if (propertyValues->propDescr == NULL || strcmp(propertyValues->propDescr, "") == 0)
                            {
                                free(duplicates);
                                return INV_ALARM;
                            }
                            if (strstr(duplicates, propertyValues->propName) != NULL)
                            {
                                free(duplicates);
                                return INV_ALARM;
                            }
			    duplicates = realloc(duplicates, strlen(duplicates) + strlen(propertyValues->propName) + 1);
                            duplicates = strcat(duplicates, propertyValues->propName);
                            
                            if (!(strcmp(propertyValues->propName, "ATTACH") == 0 || strcmp(propertyValues->propName, "DESCRIPTION") == 0 || strcmp(propertyValues->propName, "SUMMARY") == 0 || strcmp(propertyValues->propName, "DURATION") == 0 || strcmp(propertyValues->propName, "REPEAT") == 0))
                            {
                                free(duplicates);
                                return INV_ALARM;
                            }
                        }
                    }
                    free(duplicates);
                    duplicates = malloc(sizeof(char));
                    memset(duplicates, 0, sizeof(char));
	        }
            }
        }
    }

    if (eventCheck == 0)
        return INV_EVENT;

    free(duplicates);
    return OK;
}

char* printError(ICalErrorCode err) //const again? tf
{
    if (err == OK)
    {
        return "OK";
    }
    else if (err == INV_FILE)
    {
        return "INV_FILE";
    }
    else if (err == INV_CAL)
    {
        return "INV_CAL";
    }
    else if (err == INV_VER)
    {
        return "INV_VER";
    }
    else if (err == DUP_VER)
    {
        return "DUP_VER";
    }
    else if (err == INV_PRODID)
    {
        return "INV_PRODID";
    }
    else if (err == DUP_PRODID)
    {
        return "DUP_PRODID";
    }
    else if (err == INV_EVENT)
    {
        return "INV_EVENT";
    }
    else if (err == INV_ALARM)
    {
        return "INV_ALARM";
    }
    else if (err == INV_CREATEDT)
    {
        return "INV_CREATEDT";
    }
     else if (err == WRITE_ERROR)
    {
        return "WRITE_ERROR";
    }
    return "OTHER_ERROR";
}
