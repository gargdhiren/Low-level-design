#include <bits/stdc++.h>
using namespace std;

enum class VehicleSize
{
    Small,
    Medium,
    Large
};

class Vehicle
{
    string licenseNumber;
    VehicleSize size;

public:
    Vehicle(string licenseNumber, VehicleSize size)
    {
        this->licenseNumber = licenseNumber;
        this->size = size;
    }

    string getLicenseNumber()
    {
        return this->licenseNumber;
    }

    VehicleSize getSize()
    {
        return this->size;
    }
};

enum class SpotType
{
    Small,
    Medium,
    Large
};

class Spot
{
    SpotType type;
    int id;
    static int nextSpotid;
    bool empty;

public:
    Spot(SpotType type)
    {
        id = ++nextSpotid;
        this->type = type;
        empty = true;
    }

    int getId()
    {
        return this->id;
    }

    SpotType getType()
    {
        return this->type;
    }

    void setEmpty(bool empty)
    {
        this->empty = empty;
    }

    bool isEmpty()
    {
        return empty;
    }
};

int Spot::nextSpotid = 0;

class ComparatorFarthest
{
public:
    bool operator()(Spot *a, Spot *b)
    {
        if (a->getId() < b->getId())
        {
            return true;
        }

        return false;
    }
};

class ComparatorNearest
{
public:
    bool operator()(Spot *a, Spot *b)
    {
        if (a->getId() > b->getId())
        {
            return true;
        }

        return false;
    }
};

class Level
{
    int emptySpots;
    map<SpotType, priority_queue<Spot *, vector<Spot *>, ComparatorFarthest>> farthestAvailableSpots;
    map<SpotType, priority_queue<Spot *, vector<Spot *>, ComparatorNearest>> nearestAvailableSpots;
    int number;
    int entryGate;
    int exitGate;
    map<int, Spot *> spots;

public:
    Level(int number, int entryGate, int exitGate, int capacity)
    {
        this->number = number;
        this->entryGate = entryGate;
        this->exitGate = exitGate;
        this->emptySpots = capacity;
    }

    int getLevelNumber()
    {
        return number;
    }

    map<int, Spot *> getSpots()
    {
        return spots;
    }

    void addSpot(Spot *spot)
    {
        spots[spot->getId()] = spot;
        addFarthestSpot(spot);
        addNearestSpot(spot);
    }

    void emptySpot(int spotId)
    {
        spots[spotId]->setEmpty(true);
        addFarthestSpot(spots[spotId]);
        addNearestSpot(spots[spotId]);
        emptySpots++;
    }

    void addNearestSpot(Spot *spot)
    {
        nearestAvailableSpots[spot->getType()].push(spot);
    }

    void addFarthestSpot(Spot *spot)
    {
        farthestAvailableSpots[spot->getType()].push(spot);
    }

    bool isFull()
    {
        if (!emptySpots)
        {
            cout << "\nSorry, no available spot at level " << number << endl;
        }

        return !emptySpots;
    }

    Spot *getFarthestAvailableSpot(SpotType type)
    {
        if (farthestAvailableSpots[type].empty())
        {
            cout << "\nSorry, no available spot at level " << number << endl;
            return nullptr;
        }
        Spot *farthestSpot = farthestAvailableSpots[type].top();
        spots[farthestSpot->getId()]->setEmpty(false);
        farthestAvailableSpots[type].pop();
        emptySpots--;
        return farthestSpot;
    }

    Spot *getNearestAvailableSpot(SpotType type)
    {
        if (nearestAvailableSpots[type].empty())
        {
            cout << "\nSorry, no available spot at level " << number << endl;
            return nullptr;
        }
        Spot *nearestSpot = nearestAvailableSpots[type].top();
        spots[nearestSpot->getId()]->setEmpty(false);
        nearestAvailableSpots[type].pop();
        emptySpots--;
        return nearestSpot;
    }
};

class PaymentStrategy
{
public:
    virtual void pay(double amount) = 0;
};

class UPIPaymentStrategy : public PaymentStrategy
{
public:
    void pay(double totalAmount)
    {
        cout << "Paying Rs. " << totalAmount << " using UPI" << endl;
    }
};

class CashPaymentStrategy : public PaymentStrategy
{
public:
    void pay(double totalAmount)
    {
        cout << "Paying Rs. " << totalAmount << " using Cash" << endl;
    }
};

class FeeStrategy
{
public:
    virtual double calculateFee(time_t enteredTime, time_t exitTime) = 0;
};

class FlatFeeStrategy : public FeeStrategy
{

public:
    double calculateFee(time_t enteredTime, time_t exitTime)
    {
        double hours = difftime(exitTime, enteredTime) / 3600;
        return hours * 20;
    }
};

class VehicleSpecificFeeStrategy : public FeeStrategy
{

public:
    double calculateFee(time_t enteredTime, time_t exitTime, VehicleSize size)
    {
        double hours = difftime(exitTime, enteredTime) / 3600;
        if (size == VehicleSize::Small)
        {
            return hours * 10;
        }
        else if (size == VehicleSize::Medium)
        {
            return hours * 20;
        }
        return hours * 40;
    }
};

class ParkingLot
{
    static ParkingLot *instance;
    vector<Level *> levels;
    ParkingLot()
    {
        // private constructor
    }

public:
    static ParkingLot *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new ParkingLot();
        }
        return instance;
    }

    vector<Level *> getLevels()
    {
        return levels;
    }

    void addLevel(Level *level)
    {
        levels.push_back(level);
    }

    void printParkingLot()
    {
        for (Level *level : levels)
        {
            cout << "\n*******Level " << level->getLevelNumber() << " ******************" << endl;
            cout << "Spot ID ";
            for (auto it : level->getSpots())
            {
                cout << it.first << "  ";
            }
            cout << endl;
            cout << "isEmpty ";
            for (auto it : level->getSpots())
            {
                cout << it.second->isEmpty() << "  ";
            }
            cout << endl;
            cout << "**********************************\n";
        }
    }
};

ParkingLot *ParkingLot::instance = nullptr;

class ParkingStrategy
{
public:
    virtual pair<Spot *, int> getSpot(VehicleSize size, ParkingLot *lot) = 0;
};

class NearestSpotParkingStrategy : public ParkingStrategy
{
public:
    pair<Spot *, int> getSpot(VehicleSize size, ParkingLot *lot)
    {
        for (Level *level : lot->getLevels())
        {
            if (!level->isFull())
            {
                return {level->getNearestAvailableSpot(static_cast<SpotType>(size)), level->getLevelNumber()};
            }
        }

        return {nullptr, -1};
    }
};

class FarthestSpotParkingStrategy : public ParkingStrategy
{
public:
    pair<Spot *, int> getSpot(VehicleSize size, ParkingLot *lot)
    {
        for (Level *level : lot->getLevels())
        {
            if (!level->isFull())
            {
                return {level->getFarthestAvailableSpot(static_cast<SpotType>(size)), level->getLevelNumber()};
            }
        }

        return {nullptr, -1};
    }
};

class ParkingTicket
{
    string licenseNumber;
    int levelNumber;
    int spotId;
    time_t enteredTime;
    int ticketId;
    static int nextTicketId;

public:
    ParkingTicket(string licenseNumber, int levelNumber, int spotId)
    {
        this->licenseNumber = licenseNumber;
        this->levelNumber = levelNumber;
        this->spotId = spotId;
        this->enteredTime = time(0);
        this->ticketId = ++nextTicketId;
    }

    time_t getEnteredTime()
    {
        return enteredTime;
    }

    string getLicenseNumber()
    {
        return licenseNumber;
    }

    int getSpotId()
    {
        return spotId;
    }

    int getLevelNumber()
    {
        return levelNumber;
    }
};

int ParkingTicket::nextTicketId = 0;

class TicketManager
{
    static TicketManager *instance;
    set<ParkingTicket *> activeTickets;

    TicketManager()
    {
        // private constructor to prevent instantiation
    }

public:
    static TicketManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new TicketManager();
        }
        return instance;
    }
    void addTicket(ParkingTicket *ticket)
    {
        activeTickets.insert(ticket);
    }

    void removeTicket(ParkingTicket *ticket)
    {
        activeTickets.erase(ticket);
    }

    ParkingTicket *getTicket(string licenseNumber)
    {
        for (ParkingTicket *ticket : activeTickets)
        {
            if (ticket->getLicenseNumber() == licenseNumber)
            {
                return ticket;
            }
        }

        return nullptr;
    }
};

TicketManager *TicketManager::instance = nullptr;

class EntryGate
{
    TicketManager *ticketManager;
    ParkingStrategy *parkingStrategy;

public:
    EntryGate(ParkingStrategy *parkingStrategy)
    {
        this->ticketManager = TicketManager::getInstance();
        this->parkingStrategy = parkingStrategy;
    }

    void parkVehicle(Vehicle *vehicle, ParkingLot *lot)
    {
        pair<Spot *, int> spotInfo = parkingStrategy->getSpot(vehicle->getSize(), lot);
        if (spotInfo.first == nullptr)
        {
            cout << "Sorry, no available spot for your vehicle size" << endl;
            return;
        }
        else
        {
            ticketManager->addTicket(new ParkingTicket(vehicle->getLicenseNumber(), spotInfo.second, spotInfo.first->getId()));
            cout << "Vehicle Parked" << endl;
        }
    }
};

class ExitGate
{
    TicketManager *ticketManager;
    PaymentStrategy *paymentStrategy;
    FeeStrategy *feeStrategy;

public:
    ExitGate(PaymentStrategy *paymentStrategy, FeeStrategy *feeStrategy)
    {
        this->ticketManager = TicketManager::getInstance();
        this->paymentStrategy = paymentStrategy;
        this->feeStrategy = feeStrategy;
    }

    void exitVehicle(Vehicle *vehicle, ParkingLot *lot)
    {
        time_t exitTime = time(0);
        ParkingTicket *ticket = ticketManager->getTicket(vehicle->getLicenseNumber());
        double totalAmount = feeStrategy->calculateFee(ticket->getEnteredTime(), exitTime);
        if (paymentStrategy)
        {
            paymentStrategy->pay(totalAmount);
        }
        else
        {
            cout << "\nPayement unsuccessful\n"
                 << endl;
            return;
        }
        int spotId = ticket->getSpotId();
        int level = ticket->getLevelNumber();
        lot->getLevels()[level]->emptySpot(spotId);
        ticketManager->removeTicket(ticket);
        cout << "Vehicle Exited" << endl;
    }
};

// client
int main()
{
    // creating new Levels
    ParkingLot *lot = ParkingLot::getInstance();
    for (int i = 0; i < 3; i++)
    {
        Level *level = new Level(i, i, 3 + i, 5);
        for (int i = 0; i < 5; i++)
        {
            SpotType type = i % 2 ? SpotType::Small : SpotType::Large;
            Spot *spot = new Spot(type);
            level->addSpot(spot);
        }
        lot->addLevel(level);
    }

    lot->printParkingLot();
    cout << endl;

    Vehicle *vehicle = new Vehicle("PB110049", VehicleSize::Small);

    EntryGate *entrygate = new EntryGate(new FarthestSpotParkingStrategy());
    entrygate->parkVehicle(vehicle, lot);

    lot->printParkingLot();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ExitGate *exitGate = new ExitGate(new CashPaymentStrategy(), new FlatFeeStrategy());
    exitGate->exitVehicle(vehicle, lot);

    lot->printParkingLot();
    return 0;
}