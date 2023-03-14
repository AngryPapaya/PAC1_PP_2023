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



// Get the number of donations
int donationData_len (tDonationData data)
{
    // TODO
    return -1;
}

// Parse input from CSVEntry
void donation_parse (tDonation* donation, tCSVEntry entry)
{
    // TODO
}

// Add a new donation
void donationData_add (tDonationData* data, tDonation donation)
{
    // TODO
}

// Get a donation
void donationData_get (tDonationData data, int index, char* buffer)
{
    // TODO
}

// Remove a donation



