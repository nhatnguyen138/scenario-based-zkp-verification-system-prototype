#include <fstream>
#include <libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp>
#include "include/run_r1cs_ppzksnark.hpp"	// R1CS ppzkSNARK system
#include "include/sha256.h"			// SHA256 hash function
#include "include/verification.cpp"		// Scenario-based verification

using namespace std;
using namespace libsnark;

string fetch_data(int command);
void verification(const string digest);

int main()
{
    // Print menu
    cout << "CHOOSE COMMAND:\n";
    cout << "   1 - age verification\n";
    cout << "   2 - address verification\n";
    cout << "   3 - phone number verification\n";
    cout << "   4 - cancel\n";
    cout << "Command: "; char command; cin >> command;
    switch(command)
    {
        case '1':
        {
            cout << "Enter the age requirement: "; int number; cin >> number;
            bool result = age_verification(number);
            printf("\nzkSNARK verification %s\n\n", (result ? "SUCCESSFUL." : "FAILED."));
            break;
        }
        case '2':
        {
            bool result = address_verification();
            printf("\nzkSNARK verification %s\n\n", (result ? "SUCCESSFUL." : "FAILED."));
            break;
        }
        case '3':
        {
            bool result = phone_number_verification();
            printf("\nzkSNARK verification %s\n\n", (result ? "SUCCESSFUL." : "FAILED."));
            break;
        }
        case '4':
            exit(0);
        default:
        {
            cerr << "Invalid command. Please try again.\n\n";
            exit(1);
        }
    }

    return 0;
}
