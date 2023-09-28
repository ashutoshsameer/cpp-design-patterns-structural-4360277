#include <iostream>
using namespace std;

class Pizza
{
public:
    virtual string description() const = 0;
    virtual double price() const = 0;
    virtual ~Pizza() = default;
};

class MargheritaPizza : public Pizza
{
public:
    string description() const override
    {
        return "Margherita Pizza";
    }

    double price() const override
    {
        return 9.99;
    }
};

class HawaiianPizza : public Pizza
{
public:
    string description() const override
    {
        return "Hawaiian Pizza";
    }

    double price() const override
    {
        return 11.99;
    }
};

class PepperoniPizza : public Pizza
{
public:
    string description() const override
    {
        return "Pepperoni Pizza";
    }

    double price() const override
    {
        return 12.99;
    }
};

class ToppingDecorator : public Pizza
{
public:
    explicit ToppingDecorator(unique_ptr<Pizza> pizza): m_pizza(std::move(pizza)) {};
    
    string description() const
    {
        return m_pizza->description();
    }

    double price() const
    {
        return m_pizza->price();
    }

    // virtual ~ToppingDecorator() = default;

protected:
    const unique_ptr<Pizza> m_pizza;
};

class MushroomDecorator : public ToppingDecorator
{
public:
    explicit MushroomDecorator(unique_ptr<Pizza> pizza): ToppingDecorator(std::move(pizza)) {}

    string description() const
    {
        return ToppingDecorator::description() + " with mushrooms";
    }

    double price() const
    {
        return ToppingDecorator::price() + 0.99;
    } 
};

class TomatoDecorator : public ToppingDecorator
{
public:
    explicit TomatoDecorator(unique_ptr<Pizza> pizza): ToppingDecorator(std::move(pizza)) {}

    string description() const
    {
        return ToppingDecorator::description() + ", plus tomatoes";
    }

    double price() const
    {
        return ToppingDecorator::price() + 0.79;
    } 
};

class ExtraCheeseDecorator : public ToppingDecorator
{
public:
    explicit ExtraCheeseDecorator(unique_ptr<Pizza> pizza): ToppingDecorator(std::move(pizza)) {}

    string description() const
    {
        return ToppingDecorator::description() + ", plus extra cheese";
    }

    double price() const
    {
        return ToppingDecorator::price() + 1.99;
    } 
};

int main()
{
    auto margheritaPizza = make_unique<MargheritaPizza>();
    auto margheritaPizzaWithMushrooms = make_unique<MushroomDecorator>(std::move(margheritaPizza));
    auto margheritaPizzaWithMushroomsEC = make_unique<ExtraCheeseDecorator>(std::move(margheritaPizzaWithMushrooms));

    cout << margheritaPizzaWithMushroomsEC->description() << " costs $" << margheritaPizzaWithMushroomsEC->price() << endl;

    // auto pepperoniPizza = make_unique<PepperoniPizza>();

    // const std::unique_ptr<Pizza> pizzas[]{
    //     make_unique<MargheritaPizza>(),
    //     make_unique<PepperoniPizza>(),
    //     make_unique<HawaiianPizza>()};

    // for (const auto &pizza : pizzas)
    // {
    //     cout << pizza->description() << " costs $" << pizza->price() << endl;
    // }

    return 0;
}
