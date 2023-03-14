#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "donation.h"

// Parse a tDate from string information
void date_parse(tDate* date, const char* text)
{
    // Check output data
    assert(date != NULL);
    
    // Check input date
    assert(text != NULL);
    assert(strlen(text) == 10);
    
    // Parse the input date
    sscanf(text, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Compare two tDate structures and return true if they contain the same value or false otherwise.
bool date_equals(tDate date1, tDate date2)
{
    return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year); 
}

////////////////////////////////////////
// EX2: Implement your methods here....

// Initialize the donations data 
void donationData_init(tDonationData* donationData) {
    donationData->count = 0;
}

// Get the number of donations
int donationData_len (tDonationData data) {
    return data.count;
}

// Parse input from CSVEntry
void donation_parse(tDonation* donation, tCSVEntry entry) {
    // Parse date
    sscanf(entry.fields[0], "%d/%d/%d", &donation->date.day, &donation->date.month, &donation->date.year);

    // Copy document and NGO
    strcpy(donation->document, entry.fields[1]);
    strcpy(donation->ngo, entry.fields[2]);

    // Copy project code
    strcpy(donation->projectCode, entry.fields[3]);

    // Parse amount
    sscanf(entry.fields[4], "%f", &donation->amount);
}

void donationData_add (tDonationData* data, tDonation donation)
{
    // Check if the donation already exists in the list
    for (int i = 0; i < data->count; i++)
    {
        if (strcmp(data->donations[i].document, donation.document) == 0 &&
            date_equals(data->donations[i].date, donation.date) &&
            strcmp(data->donations[i].projectCode, donation.projectCode) == 0)
        {
            // The donation already exists, so we don't add it again
            return;
        }
    }

    // Find the position to insert the new donation based on the project code
    int insertPosition = data->count;
    for (int i = 0; i < data->count; i++)
    {
        if (strcmp(data->donations[i].projectCode, donation.projectCode) > 0)
        {
            insertPosition = i;
            break;
        }
    }

    // Insert the new donation at the correct position
    if (insertPosition == data->count)
    {
        data->donations[data->count] = donation;
    }
    else
    {
        for (int i = data->count - 1; i >= insertPosition; i--)
        {
            data->donations[i + 1] = data->donations[i];
        }
        data->donations[insertPosition] = donation;
    }

    // Update the count of donations in the list
    data->count++;
}

void donationData_get(tDonationData data, int index, char* buffer)
{
    // Verificar si el índice es válido
    if (index < 0 || index >= data.count) {
        buffer[0] = '\0'; // Establecer el buffer como una cadena vacía
        return;
    }

    // Obtener la donación correspondiente
    tDonation donation = data.donations[index];

    // Formatear los campos de la donación en una cadena de caracteres
    sprintf(buffer, "%02d/%02d/%04d;%s;%s;%s;%.2f",
            donation.date.day, donation.date.month, donation.date.year,
            donation.document, donation.ngo, donation.projectCode, donation.amount);
}

// Remove a donation
void donationData_del (tDonationData* data, tDate date, char* document, char* projectCode)
{
    // Find the donation with the given date, document and project code
    int i, foundIndex = -1;
    for (i = 0; i < data->count; i++) {
        if (date_equals(data->donations[i].date, date) &&
            strcmp(data->donations[i].document, document) == 0 &&
            strcmp(data->donations[i].projectCode, projectCode) == 0) {
            foundIndex = i;
            break;
        }
    }

    // Delete the donation if found
    if (foundIndex != -1) {
        int j;
        for (j = foundIndex; j < data->count - 1; j++) {
            data->donations[j] = data->donations[j+1];
        }
        data->count--;
    }
}



