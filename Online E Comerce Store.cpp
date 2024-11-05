
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Product
{                                  // Abstract base class
protected:
    string name;
    float price;
    int quantity;

public:
    Product(string name, float price, int quantity)                        // Parameterized constructor
        : name(name), price(price), quantity(quantity) {}

    virtual void display() = 0;                         // Display product details (virtual function)

    string getName() const
    {
        return name;
    }
    float getPrice() const
    {
        return price;
    }
    int getQuantity() const
    {
        return quantity;
    }
    void setQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }

    friend class Dealer;                                    // Friend function (to access private members of Product in other classes)
};

class ElectronicProduct : public Product
{
private:
    string brand;
public:
    ElectronicProduct(string name, float price, int quantity, string brand)                  // Parameterized constructor
        : Product(name, price, quantity), brand(brand) {}

    void display() override
    {
        cout << "\n\tName: " << name << endl;
        cout << "\tBrand: " << brand << endl;
        cout << "\tPrice: " << price << endl;
        cout << "\tQuantity: " << quantity << endl;
    }
};

class ClothingProduct : public Product
{
private:
    string size;
public:
    ClothingProduct(string name, float price, int quantity, string size)              // Parameterized constructor
        : Product(name, price, quantity), size(size) {}

    void display() override
    {
        cout << "\n\tName: " << name << endl;
        cout << "\tSize: " << size << endl;
        cout << "\tPrice: " << price << endl;
        cout << "\tQuantity: " << quantity << endl;
    }
};
class Dealer                            // Dealer class managing a collection of products
{
private:
    static const int MAX_PRODUCTS = 10;
    Product* products[MAX_PRODUCTS];
    int size;

public:
    Dealer() : size(0)
    {
    }

    ~Dealer()
    {
        for (int i = 0; i < size; i++)
        {
            delete products[i];
        }
    }

    void addProduct(Product* product)                   // Add a new product
    {
        if (size < MAX_PRODUCTS) {
            products[size] = product;
            size++;
            cout << "\n\t\tProduct Added Successfully" << endl;
        }
        else
        {
            cout << "\n\t\tMax limit reached. Cannot add more products!" << endl;
        }
    }

    void displayStock()                                  // Display the stock
    {
        if (size > 0)
        {
            cout << "\n\n\t\t\t****** Current Stock *******" << endl;
            for (int i = 0; i < size; i++)
            {
                cout << "\n\t\t Product " << (i + 1) << "\n" << endl;
                products[i]->display();
                cout << endl;
            }
        }
        else
        {
            cout << "\n\t\tNo products in stock! " << endl;
        }
    }

    void removeItem()                                            // Remove an item from the stock
    {
        if (size > 0)
        {
            string productName;
            cout << "\n\tEnter product name to remove : ";
            cin >> productName;
            for (int i = 0; i < size; i++)
            {
                if (products[i]->getName() == productName)
                {
                    delete products[i];
                    products[i] = nullptr;

                    for (int j = i; j < size - 1; j++)                                // Shift the remaining products to fill empty space
                    {
                        products[j] = products[j + 1];
                    }

                    products[size - 1] = nullptr;
                    size--;

                    cout << "\n\t\tProduct Removed Successfully" << endl;
                    return;
                }
            }
            cout << "\n\t\tProduct not found!" << endl;
        }
        else
        {
            cout << "\n\t\tNo products in stock!" << endl;
        }
    }

    void refillStock()                                       // Refill the stock  
    {
        if (size > 0)
        {
            string productName;
            cout << "\n\tEnter Product Name to Refill : ";
            cin >> productName;

            for (int i = 0; i < size; i++)
            {
                if (products[i]->getName() == productName)
                {
                    int quantity;
                    cout << "\tEnter quantity to refill: ";
                    cin >> quantity;

                    int newQuantity = products[i]->getQuantity() + quantity;
                    products[i]->setQuantity(newQuantity);

                    cout << "\n\t\tStock Refilled Successfully" << endl;
                    return;
                }
            }

            cout << "\n\t\tProduct not found!" << endl;
        }
        else
        {
            cout << "No products in stock!" << endl;
        }
    }
    void saveToFile()                                               // Save products to a file
    {
        if (size > 0)
        {
            ofstream file("products.txt");
            if (file.is_open())
            {
                for (int i = 0; i < size; i++)
                {
                    file << products[i]->getName() << endl;
                    file << products[i]->getPrice() << endl;
                    file << products[i]->getQuantity() << endl;
                }
                file.close();
                cout << "\n\n\t\tProducts saved to file successfully!" << endl;
            }
            else
            {
                cout << "\n\t\tError opening file!" << endl;
            }
        }
        else
        {
            cout << "\n\t\tNo products in stock!" << endl;
        }
    }
};

int main()
{
    Dealer dealer;
    ifstream file("products.txt");
    if (file.is_open())
    {
        string name;
        float price;
        int quantity;

        while (file >> name >> price >> quantity)
        {
            cout << "\n\n\t\tLoading product: " << name << endl;
            if (name == "ElectronicProduct")
            {
                string brand;
                file >> brand;
                Product* product = new ElectronicProduct(name, price, quantity, brand);
                dealer.addProduct(product);
            }
            else if (name == "ClothingProduct")
            {
                string size;
                file >> size;
                Product* product = new ClothingProduct(name, price, quantity, size);
                dealer.addProduct(product);
            }
        }

        file.close();
        cout << "\n\n\t\tProducts loaded from file successfully!" << endl;
    }

    int choice;
    do
    {
        cout << "\n\n\t\t\t\t\t\tKHRB STORE\n\n" << endl;
        cout << "\n\t\t\t\tWelcome To Our Store Management System" << endl;
        cout << "\n\n\t\t*** MENU ***\n\n" << endl;
        cout << "\tPress 1 For Add New Product" << endl;
        cout << "\tPress 2 For Display Stock" << endl;
        cout << "\tPress 3 For Refill Stock" << endl;
        cout << "\tPress 4 For Remove an Item" << endl;
        cout << "\tPress 5 For Save Products to File" << endl;
        cout << "\tPress 6 For Exit" << endl;
        cout << "\n\tEnter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int productType;
            cout << "\n\n\t\t\tSelect product type" << endl;
            cout << "\n\t1. ElectronicProduct\t\t2. ClothingProduct" << endl;
            cout << "\n\tEnter your choice : ";
            cin >> productType;

            string name;
            float price;
            int quantity;
            cout << "\n" << endl;
            cout << "\tEnter Product Name : ";
            cin >> name;
            cout << "\tEnter Price : ";
            cin >> price;
            cout << "\tEnter Quantity : ";
            cin >> quantity;

            if (productType == 1)
            {
                string brand;
                cout << "\tEnter Brand : ";
                cin >> brand;
                Product* product = new ElectronicProduct(name, price, quantity, brand);
                dealer.addProduct(product);
            }
            else if (productType == 2)
            {
                string size;
                cout << "\tEnter Size : ";
                cin >> size;
                Product* product = new ClothingProduct(name, price, quantity, size);
                dealer.addProduct(product);
            }
            else
            {
                cout << "\n\tInvalid Product Type!" << endl;
            }
            break;
        }
        case 2:
            dealer.displayStock();
            break;
        case 3:
            dealer.refillStock();
            break;
        case 4:
            dealer.removeItem();
            break;
        case 5:
            dealer.saveToFile();
            break;
        case 6:
            cout << "\n\tExiting..." << endl;
            break;
        default:
            cout << "\n\tInvalid choice !! Try Again." << endl;
        }
        cout << endl;
    }
    while (choice != 0);
    return 0;
}
