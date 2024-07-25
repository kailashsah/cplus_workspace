
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void assert(bool condition, string errorMsg) {
    if (!condition)
        throw std::runtime_error(errorMsg);
}

class IComputationResults {};

/** Valuation and Delta sensitivity. */
class ComputationResults : public IComputationResults {
public:
    ComputationResults();
    double GetPrice() const;
    double GetDelta(long underlyingCode) const;
    void SetPrice(double price);
    // double SetDeltas(map<long, double> deltas);
private:
    double fPrice;
    map<long, double> fDeltas;
};

ComputationResults::ComputationResults() : fPrice(0.0) {}

double ComputationResults::GetPrice() const { return fPrice; }

double ComputationResults::GetDelta(long underlyingCode) const {
    auto iter = fDeltas.find(underlyingCode);
    assert(iter != fDeltas.end(),
        "failed to find delta for underlying " + to_string(underlyingCode));
    return iter->second;
}

void ComputationResults::SetPrice(double price) { fPrice = price; }

class ComputationResultsStore {
public:
    const ComputationResults* GetComputationResults(long code) const;
    void RegisterComputationResults(long code,
        const ComputationResults& compuationResults);
    void ClearComputationResults(long code);
    void ResetComputationResults();

private:
    map<long, const ComputationResults*> fComputationResultsContainer;
};

const ComputationResults*
ComputationResultsStore::GetComputationResults(long code) const {
    auto iter = fComputationResultsContainer.find(code);
    assert(iter != fComputationResultsContainer.end(),
        "failed to find computation results for " + to_string(code));
    return iter->second;
}

void ComputationResultsStore::RegisterComputationResults(
    long code, const ComputationResults& computationResults) {
    fComputationResultsContainer[code] = &computationResults;
}

void ComputationResultsStore::ClearComputationResults(long code) {
    fComputationResultsContainer.erase(code);
}

void ComputationResultsStore::ResetComputationResults() {
    fComputationResultsContainer.clear();
}

ComputationResultsStore computationResultsStore;

/** Security base class. */
class Instrument {
public:
    Instrument(long);
    const Instrument& operator=(const Instrument&);
    virtual ~Instrument();
    long GetCode() const; // identifies the security.
private:
    long fCode;
};

Instrument::Instrument(long code) { fCode = code; }

Instrument::~Instrument() {}

long Instrument::GetCode() const { return fCode; }

/** Basket component. */
struct BasketComponent {
    long code;
    double quantity;
};

/** Basket contains multiple securities
 *
 *  For instance (pseudo-code):
 *  long IBM = 42;  // ID means nothing.
 *  long AAPL = 43;
 *  basket[0] = BasketComponent { IBM, 100 };
 *  basket[1] = BasketComponent { AAPL, 200 };
 *  ...
 */
class Basket : public Instrument {
public:
    Basket(long code);
    /** Number of component in the basket. Loop from 0 to that number to retrieve
     * all components.
     *  @seealso GetNthBasketComponent. */
    int GetComponentCount() const noexcept;
    /** @return true if the (out) component argument was correctly updated */
    bool GetNthBasketComponent(/* in */ int which,
        /* out */ BasketComponent* component) const;
    /** { *component= GetComponent(which); return true; } */

    void SetComponents(const std::vector<BasketComponent>& components);

private:
    std::vector<BasketComponent> fComponents;
};

Basket::Basket(long code) : Instrument(code) {}

int Basket::GetComponentCount() const noexcept { return fComponents.size(); }

bool Basket::GetNthBasketComponent(int which,
    BasketComponent* component) const {
    if (which < 0 || which >= fComponents.size())
        return false;
    *component = fComponents[which];
    return true;
}

void Basket::SetComponents(const std::vector<BasketComponent>& components) {
    fComponents = components;
}

/** @param basket whose composition is to be returned.
 *  @return composition map of components and weights where the key is the
 * component code. */
map<long, double>  GetBasketCompositionWithWeight(const Basket* basket) {
    map<long, double> results;
    if (basket->GetComponentCount() < 1) { return results; }
    double sum = 0;
    for (int i = 0; i < basket->GetComponentCount(); i++)
    {
        BasketComponent component;
        double marketvalue = 0;

        if (basket->GetNthBasketComponent(i, &component))
        {

            const ComputationResults* pResults = computationResultsStore.GetComputationResults(component.code);
            marketvalue = pResults->GetPrice() * component.quantity;
            results[component.code] = marketvalue;
            sum += marketvalue;
        }


    }

    if (sum == 0)
    {
        results.clear();
        return results;
    }
    for (auto basket : results)
    {
        basket.second = basket.second / sum;
    }
        
    return results;

}
//for (int i = 0; i < basket->GetComponentCount(); i++)
//{
//    BasketComponent component;
//    double marketvalue = 0;
//    double sum = 0;
//    if (basket->GetNthBasketComponent(i, &component))// this is not needed
//    {
//        marketvalue = results[component.code];
//        results[component.code] = marketvalue / sum;
//    }
//
//}

void TestBasketWithZeroPriceComponents() {
    computationResultsStore.ResetComputationResults();
    Instrument component1(123);
    Instrument component2(456);

    ComputationResults computationResults;
    computationResults.SetPrice(0.0);

    computationResultsStore.RegisterComputationResults(component1.GetCode(),
        computationResults);

    computationResultsStore.RegisterComputationResults(component2.GetCode(),
        computationResults);

    BasketComponent basketComponent1, basketComponent2;
    basketComponent1.code = component1.GetCode();
    basketComponent1.quantity = 1.0;
    basketComponent2.code = component2.GetCode();
    basketComponent2.quantity = 1.0;

    Basket basket(12345);
    basket.SetComponents({ basketComponent1, basketComponent2 });

    auto componentsWithWeights = GetBasketCompositionWithWeight(&basket);
    assert((componentsWithWeights.size() == 0),
        "component count incorrect. Expected: 0, Found: " +
        to_string(componentsWithWeights.size()));
    cout << "TestBasketWithZeroPriceComponents passed!" << endl;
    computationResultsStore.ResetComputationResults();
}

//
//int main() {
//    TestBasketWithZeroPriceComponents();
//    return 0;
//}