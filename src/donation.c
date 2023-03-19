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
void donationData_init(tDonationData* data) 
{    
    assert(data != NULL); // Verify that the pointer is not null

    // Initialize the donationData counter 
    data->count = 0;

    assert(data->count == 0); // Verify that the counter has been initialized correctly
}

// Get the number of donations
int donationData_len (tDonationData data) 
{
    return data.count;
}

// Parse input from CSVEntry
void donation_parse(tDonation* donation, tCSVEntry entry) 
{
    // Parse date
    sscanf(entry.fields[0], "%d/%d/%d", &donation->date.day, &donation->date.month, &donation->date.year);

    // Allocate memory for document, ngo and projectCode
    donation->document = malloc(strlen(entry.fields[1]) + 1);
    donation->ngo = malloc(strlen(entry.fields[2]) + 1);
    donation->projectCode = malloc(strlen(entry.fields[3]) + 1);

    // Copy data
    strcpy(donation->document, entry.fields[1]);
    strcpy(donation->ngo, entry.fields[2]);
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
    // Check if the index is valid
    if (index < 0 || index >= data.count) {
        buffer[0] = '0'; // Set buffer as empty string
        return;
    }

    // Get the corresponding donation.
    tDonation donation = data.donations[index];

    // Format the donation fields into a string.
    sprintf(buffer, "%02d/%02d/%04d;%s;%s;%s;%.2f",
            donation.date.day, donation.date.month, donation.date.year,
            donation.document, donation.ngo, donation.projectCode, donation.amount);
}

// Remove a donation
void donationData_del (tDonationData* data, tDate date, char* document, char* projectCode)
{
    // Check for null pointers
    assert(data != NULL);
    assert(document != NULL);
    assert(projectCode != NULL);

    // Check date values
    assert(date.day > 0 && date.day <= 31);
    assert(date.month > 0 && date.month <= 12);
    assert(date.year >= 1900 && date.year <= 2100);

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
    } else {
         assert(foundIndex == -1); // No donation found or removed
    }
}



