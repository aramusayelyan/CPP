#include <iostream>
#include <vector>
#include <string>

int _id = 1;

class Product
{
private:
    int id;
    std::string product_name;
    double product_price;
    int percent;

public:
    Product() : id(_id++), percent(0), product_price(0) {}

    void set_percent(int p) { percent = p; }
    int get_percent() const { return percent; }

    void set_product_name(const std::string &name) { product_name = name; }
    void set_product_price(double price) { product_price = price; }

    std::string get_product_name() const { return product_name; }
    double get_product_price() const { return product_price; }

    void print_product_info() const
    {
        std::cout << "Product ID: " << id << std::endl;
        std::cout << "Product Name: " << product_name << std::endl;
        std::cout << "Product Price: $" << product_price << std::endl
                  << std::endl;
    }

    int get_id() const { return id; }

    virtual void discount() {}

    virtual ~Product() {}
};

class Laptop : public Product
{
public:
    Laptop()
    {
        set_product_name("Laptop");
        set_product_price(100);
        set_percent(5);
    }

    void discount() override
    {
        set_product_price(get_product_price() - ((get_product_price() * get_percent()) / 100));
    }
};

class Headphones : public Product
{
public:
    Headphones()
    {
        set_product_name("Headphones");
        set_product_price(500);
        set_percent(10);
    }

    void discount() override
    {
        set_product_price(get_product_price() - ((get_product_price() * get_percent()) / 100));
    }
};

class Watch : public Product
{
public:
    Watch()
    {
        set_product_name("Watch");
        set_product_price(250);
        set_percent(15);
    }

    void discount() override
    {
        set_product_price(get_product_price() - ((get_product_price() * get_percent()) / 100));
    }
};

class Cart
{
private:
    std::vector<Product *> cart;
    double total_amount;

public:
    Cart() : total_amount(0) {}

    void add_product(Product *_new)
    {
        cart.push_back(_new);
    }

    void delete_product()
    {
        int id;
        std::cout << "-------------------------------------------------" << std::endl;
        print_product_info();
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "Select the product ID to delete: ";
        std::cin >> id;

        for (auto it = cart.begin(); it != cart.end(); ++it)
        {
            if ((*it)->get_id() == id)
            {
                delete *it;
                cart.erase(it);
                break;
            }
        }
    }

    double calculate_total_amount()
    {
        total_amount = 0;
        for (auto *product : cart)
        {
            total_amount += product->get_product_price();
        }
        return total_amount;
    }

    void print_product_info()
    {
        for (auto *product : cart)
        {
            product->print_product_info();
        }
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "Total Amount: $" << calculate_total_amount() << std::endl;
    }

    void products_discount()
    {
        for (auto *product : cart)
        {
            product->discount();
        }
        print_product_info();
    }

    ~Cart()
    {
        for (auto *product : cart)
        {
            delete product;
        }
    }
};

class Customer
{
private:
    Cart cart;

public:
    void view_cart()
    {
        cart.print_product_info();
        std::cout << std::endl;
    }

    void add_product_to_cart(Product *_new)
    {
        cart.add_product(_new);
    }

    void delete_product_by_cart()
    {
        cart.delete_product();
    }

    void discount()
    {
        cart.products_discount();
    }
};

void _comands(Customer &obj, int option)
{
    switch (option)
    {
    case 1:
        obj.add_product_to_cart(new Laptop());
        break;
    case 2:
        obj.add_product_to_cart(new Headphones());
        break;
    case 3:
        obj.add_product_to_cart(new Watch());
        break;
    case 4:
        obj.view_cart();
        break;
    }
}

void active(Customer &obj)
{
    int option = 0;
    do
    {
        std::cout << "Products:" << std::endl
                  << "[ 1. Laptop ]" << std::endl
                  << "[ 2. Headphones  ]" << std::endl
                  << "[ 3. Watch ]" << std::endl
                  << "[ 4. View Cart ]" << std::endl
                  << "[ -1. Exit ]" << std::endl;
        std::cin >> option;
        if (option == -1)
            break;
        _comands(obj, option);
    } while (true);
}

int main()
{
    Customer customer;
    std::cout << "Welcome to the cozy little stall of Half-Blood Prince. We present to you the unique assortment of the store." << std::endl;
    active(customer);
    return 0;
}
