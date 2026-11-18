#include <iostream>
#include<fstream>
#include <string>
#include <limits>
#include <cstring>
#include <cstdio>

using namespace std;
// Structure for binary file records
struct ProduceRecord
{
    int batchID;
    char produceName[50];
    float quantity;
    float temperature;
    char storageLocation[50];
};
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
  // Constructor
  Produce()
 {
    batchID = 0;
    quantity = 0;
    temperature = 0;
 }

   // Destructor
  ~Produce()
 {
    cout << "\nProduce object destroyed." << endl;
 }

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
    // Save produce details to file
void saveToFile()
{
    ofstream file("produce.txt", ios::app);

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    file << batchID << endl;
    file << produceName << endl;
    file << quantity << endl;
    file << temperature << endl;
    file << storageLocation << endl;

    file.close();

    cout << "Produce saved to file successfully!" << endl;
}
    // Read produce details from file
void readFromFile()
{
    ifstream file("produce.txt");

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    int id;
    string name, location;
    float qty, temp;

    cout << "\n===== RECORDS FROM FILE =====\n";

    while (file >> id)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, name);

        file >> qty >> temp;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, location);

        cout << "\nBatch ID: " << id << endl;
        cout << "Produce Name: " << name << endl;
        cout << "Quantity: " << qty << " kg" << endl;
        cout << "Temperature: " << temp << " C" << endl;
        cout << "Storage Location: " << location << endl;
    }

    file.close();
}
 // Save produce details in binary file
void saveBinaryToFile()
{
    ofstream file("produce.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "Error opening binary file!" << endl;
        return;
    }

    ProduceRecord record{};

    record.batchID = batchID;

    strncpy(record.produceName, produceName.c_str(), 49);
    record.quantity = quantity;
    record.temperature = temperature;

    strncpy(record.storageLocation, storageLocation.c_str(), 49);

    file.write((char*)&record, sizeof(record));

    file.close();

    cout << "Binary record saved successfully!" << endl;
}

void readBinaryFromFile()
{
    ifstream file("produce.dat", ios::binary);

    if (!file)
    {
        cout << "Error opening binary file!" << endl;
        return;
    }

    ProduceRecord record;

    cout << "\n===== RECORDS FROM BINARY FILE =====\n";

    while (file.read((char*)&record, sizeof(record)))
    {
        cout << "\nBatch ID: " << record.batchID << endl;
        cout << "Produce Name: " << record.produceName << endl;
        cout << "Quantity: " << record.quantity << " kg" << endl;
        cout << "Temperature: " << record.temperature << " C" << endl;
        cout << "Storage Location: " << record.storageLocation << endl;
    }

    file.close();
}


void searchBinaryFile()
{
    ifstream file("produce.dat", ios::binary);

    if (!file)
    {
        cout << "Error opening binary file!" << endl;
        return;
    }

    int searchID;
    cout << "\nEnter Batch ID to search: ";
    cin >> searchID;

    ProduceRecord record;
    bool found = false;

    while (file.read((char*)&record, sizeof(record)))
    {
        if (record.batchID == searchID)
        {
            cout << "\nRecord Found!\n";
            cout << "Batch ID: " << record.batchID << endl;
            cout << "Produce Name: " << record.produceName << endl;
            cout << "Quantity: " << record.quantity << " kg" << endl;
            cout << "Temperature: " << record.temperature << " C" << endl;
            cout << "Storage Location: " << record.storageLocation << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Record not found!" << endl;
    }

    file.close();
}

void directSearchBinaryFile()
{
    ifstream file("produce.dat", ios::binary);

    if (!file)
    {
        cout << "Error opening binary file!" << endl;
        return;
    }

    int position;
    cout << "\nEnter record position (1, 2, 3...): ";
    while (!(cin >> position) || position < 1)
{
    cout << "Invalid position! Enter a positive number: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    ProduceRecord record;

    // Move directly to the selected record
    file.seekg((position - 1) * sizeof(ProduceRecord));

    if (file.read((char*)&record, sizeof(record)))
    {
        cout << "\nRecord Found!\n";
        cout << "Batch ID: " << record.batchID << endl;
        cout << "Produce Name: " << record.produceName << endl;
        cout << "Quantity: " << record.quantity << " kg" << endl;
        cout << "Temperature: " << record.temperature << " C" << endl;
        cout << "Storage Location: " << record.storageLocation << endl;
    }
    else
    {
        cout << "Record not found!" << endl;
    }

    file.close();
}

void updateBinaryFile()
{
    fstream file("produce.dat",
                 ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "Error opening binary file!" << endl;
        return;
    }

    int position;

    cout << "\nEnter record position to update: ";

while (!(cin >> position) || position < 1)
{
    cout << "Invalid position! Enter a positive number: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    ProduceRecord record;

    // Calculate the position of the record
    streamoff location =
        (position - 1) * sizeof(ProduceRecord);

    file.seekg(location, ios::beg);

    if (!file.read((char*)&record, sizeof(record)))
    {
        cout << "Record not found!" << endl;
        file.close();
        return;
    }

    cout << "\nCurrent Produce: "
         << record.produceName << endl;

    string name, storage;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new produce name: ";
getline(cin, name);

while (name.empty())
{
    cout << "Name cannot be empty. Enter again: ";
    getline(cin, name);
}

    cout << "Enter new quantity: ";
while (!(cin >> record.quantity) || record.quantity <= 0)
{
    cout << "Invalid quantity! Enter again: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

cout << "Enter new temperature: ";
while (!(cin >> record.temperature) ||
       record.temperature < -50 || record.temperature > 50)
{
    cout << "Invalid temperature! Enter between -50 and 50: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new storage location: ";
    getline(cin, storage);

    // Copy updated details
    strncpy(record.produceName, name.c_str(), 49);
    record.produceName[49] = '\0';

    strncpy(record.storageLocation, storage.c_str(), 49);
    record.storageLocation[49] = '\0';

    // Move writing pointer to the same record
    file.seekp(location, ios::beg);

    file.write((char*)&record, sizeof(record));

    cout << "\nBinary record updated successfully!" << endl;

    file.close();
}
void deleteBinaryRecord()
{
    ifstream in("produce.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    if (!in || !out)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    int position;
    cout << "\nEnter record position to delete: ";

    while (!(cin >> position) || position < 1)
    {
        cout << "Invalid position! Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ProduceRecord record;
    int count = 0;
    bool found = false;

    while (in.read((char*)&record, sizeof(record)))
    {
        count++;

        if (count == position)
        {
            found = true;
            continue;
        }

        out.write((char*)&record, sizeof(record));
    }

    in.close();
    out.close();

    if (!found)
    {
        cout << "Record not found!" << endl;
        std::remove("temp.dat");
        return;
    }

    if (std::remove("produce.dat") != 0)
{
    cout << "Error deleting original file!" << endl;
    std::remove("temp.dat");
    return;
}

if (std::rename("temp.dat", "produce.dat") != 0)
{
    cout << "Error renaming temporary file!" << endl;
    return;
}
    cout << "Record deleted successfully!" << endl;
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
        // save batch details to file
        batches[i].saveToFile();
        // save batch details to binary file
        batches[i].saveBinaryToFile();
    }

       // Read records from file
batches[0].readFromFile();
batches[0].readBinaryFromFile();
batches[0].searchBinaryFile();
batches[0].directSearchBinaryFile();
batches[0].updateBinaryFile();
batches[0].readBinaryFromFile();
batches[0].deleteBinaryRecord();
batches[0].readBinaryFromFile();
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
if (n > 0)
{
    batches[0].readBinaryFromFile();
}
    return 0;
}
