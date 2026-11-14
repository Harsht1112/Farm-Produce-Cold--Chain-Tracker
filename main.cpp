
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Produce
{
private:
    int batchID;
    string produceName;
    float quantity;
    float temperature;
    string storageLocation;

    // Static data member
    static int totalBatches;

public:

    // Function to add produce details
    void addProduce(int id)
    {
        this->batchID = id;

        cout << "Enter produce name: ";
        getline(cin, produceName);

        while (produceName.empty())
        {
            cout << "Name cannot be empty. Enter again: ";
            getline(cin, produceName);
        }

        // Validate quantity
        cout << "Enter quantity (kg): ";
        while (!(cin >> quantity) || quantity <= 0)
        {
            cout << "Invalid quantity! Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Validate temperature
        cout << "Enter temperature (Celsius): ";
        while (!(cin >> temperature) ||
               temperature < -50 || temperature > 50)
        {
            cout << "Invalid temperature! Enter between -50 and 50: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter storage location: ";
        getline(cin, storageLocation);

        while (storageLocation.empty())
        {
            cout << "Location cannot be empty. Enter again: ";
            getline(cin, storageLocation);
        }

        // Increase total batch count
        totalBatches++;

        cout << "\nBatch added successfully!\n";
    }

    // Getter function
    int getBatchID() const
    {
        return batchID;
    }

    // Inline function
    inline float getQuantity() const
    {
        return quantity;
    }

    // Display batch details
    void displayProduce() const
    {
        cout << "\n------ Produce Details ------\n";
        cout << "Batch ID: " << batchID << endl;
        cout << "Produce Name: " << produceName << endl;
        cout << "Quantity: " << quantity << " kg" << endl;
        cout << "Temperature: " << temperature << " C" << endl;
        cout << "Storage Location: " << storageLocation << endl;
    }
    
void updateProduce()
{
    cout << "\n--- Update Produce Details ---\n";

    cout << "Enter new produce name: ";
    getline(cin, produceName);

    while (produceName.empty())
    {
        cout << "Name cannot be empty. Enter again: ";
        getline(cin, produceName);
    }

    cout << "Enter new quantity (kg): ";
    while (!(cin >> quantity) || quantity <= 0)
    {
        cout << "Invalid quantity! Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter new temperature: ";
    while (!(cin >> temperature) ||
           temperature < -50 || temperature > 50)
    {
        cout << "Invalid temperature! Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new storage location: ";
    getline(cin, storageLocation);

    while (storageLocation.empty())
    {
        cout << "Location cannot be empty. Enter again: ";
        getline(cin, storageLocation);
    }

    cout << "\nBatch updated successfully!\n";
}


    // Static member function
    static void showTotalBatches()
    {
        cout << "\nTotal batches added: " << totalBatches << endl;
    }

    // Friend function declaration
    friend void showTemperature(const Produce &p);

    // this pointer example
    void setBatchID(int batchID)
    {
        this->batchID = batchID;
    }
};

// Definition of static data member
int Produce::totalBatches = 0;

// Friend function definition
void showTemperature(const Produce &p)
{
    cout << "Temperature using friend function: "
         << p.temperature << " C" << endl;
}

int main()
{
    Produce batches[5];

    int n;

    // Validate number of batches
    cout << "Enter number of batches (1-5): ";

    while (!(cin >> n) || n < 1 || n > 5)
    {
        cout << "Invalid number! Enter between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Add batches
    for (int i = 0; i < n; i++)
    {
        int id;
        bool duplicate;

        cout << "\nEnter details for batch " << i + 1 << endl;

        do
        {
            cout << "Enter Batch ID: ";

            while (!(cin >> id) || id <= 0)
            {
                cout << "Invalid ID! Enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            duplicate = false;

            // Check duplicate ID
            for (int j = 0; j < i; j++)
            {
                if (batches[j].getBatchID() == id)
                {
                    duplicate = true;
                    cout << "Batch ID already exists! Try another ID.\n";
                    break;
                }
            }

        } while (duplicate);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        batches[i].addProduce(id);
    }

    // Display all batches
    cout << "\n========== ALL BATCHES ==========\n";

    for (int i = 0; i < n; i++)
    {
        batches[i].displayProduce();
    }

    // Search batch by ID
    int searchID;
    bool found = false;

    cout << "\nEnter Batch ID to search: ";

    while (!(cin >> searchID) || searchID <= 0)
    {
        cout << "Enter a valid positive Batch ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < n; i++)
    {
        if (batches[i].getBatchID() == searchID)
        {
            cout << "\nBatch found!\n";
            batches[i].displayProduce();
            found = true;

            // Call friend function
            showTemperature(batches[i]);

            // Call inline function
            cout << "Quantity using inline function: "
                 << batches[i].getQuantity() << " kg\n";

            break;
        }
    }

    if (!found)
    {
        cout << "\nBatch not found!\n";
    }

    // Static member function call
    Produce::showTotalBatches();

    // Pointer to object
    Produce *ptr = &batches[0];

    cout << "\nDisplaying first batch using pointer:\n";
    ptr->displayProduce();

    // UPDATE OPERATION
int updateID;
bool foundUpdate = false;

cout << "\nEnter Batch ID to update: ";
while (!(cin >> updateID) || updateID <= 0)
{
    cout << "Invalid ID! Enter a positive Batch ID: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

for (int i = 0; i < n; i++)
{
    if (batches[i].getBatchID() == updateID)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        batches[i].updateProduce();
        foundUpdate = true;
        break;
    }
}

if (!foundUpdate)
{
    cout << "Batch not found!\n";
}
    
    // DELETE OPERATION
    int deleteID;
    bool foundDelete = false;

    cout << "\nEnter Batch ID to delete: ";

while (!(cin >> deleteID) || deleteID <= 0)
{
    cout << "Invalid ID! Enter a positive Batch ID: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    for (int i = 0; i < n; i++)
    {
        if (batches[i].getBatchID() == deleteID)
        {
            char confirm;

            cout << "Are you sure you want to delete? (y/n): ";
            cin >> confirm;
            while (confirm != 'y' && confirm != 'Y' &&
       confirm != 'n' && confirm != 'N')
{
    cout << "Please enter y or n: ";
    cin >> confirm;
}

            if (confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < n - 1; j++)
                {
                    batches[j] = batches[j + 1];
                }

                n--;

                cout << "Batch deleted successfully!\n";
            }
            else
            {
                cout << "Deletion cancelled.\n";
            }

            foundDelete = true;
            break;
        }
    }

    if (!foundDelete)
    {
        cout << "Batch not found!\n";
    }
    // Display batches after deletion
cout << "\n========== REMAINING BATCHES ==========\n";

for (int i = 0; i < n; i++)
{
    batches[i].displayProduce();
}
if (n == 0)
{
    cout << "No batches available.\n";
}

    return 0;
}
