#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Mock class for database library
class Database
{
public:
    void storeReservation(const string &reservation)
    {
        cout << "Database: Storing reservation: " << reservation << endl;
    }
};

// Mock class for payment gateway
class PaymentGateway
{
public:
    void processPayment(const string &paymentInfo)
    {
        cout << "Payment Gateway: Processing payment with info: " << paymentInfo << endl;
    }
};

// Mock class for messaging service
class MessagingService
{
public:
    void sendConfirmation(const string &message)
    {
        cout << "Messaging Service: Sending confirmation message: " << message << endl;
    }
};

class ReservationSystemFacade
{
public:
    ReservationSystemFacade()
    : m_database()
    , m_payment()
    , m_messaging()
    {}

    void makeReservation(const string& reservationInfo, const string& paymentInfo)
    {
        m_database.storeReservation(reservationInfo);
        m_payment.processPayment(paymentInfo);
        m_messaging.sendConfirmation("Reservation Confirmed.");
    }

private:
    Database m_database;
    PaymentGateway m_payment;
    MessagingService m_messaging;
};

int main()
{
    /*
    Database db;
    PaymentGateway paymentGateway;
    MessagingService messagingService;

    const string reservation = "Room reservation info";
    db.storeReservation(reservation);

    const string paymentInfo = "Payment info";
    paymentGateway.processPayment(paymentInfo);

    messagingService.sendConfirmation("Reservation confirmed.");
    */

   ReservationSystemFacade rsf;
   const string reservation = "Room reservation info";
   const string paymentInfo = "Payment info";
   rsf.makeReservation(reservation, paymentInfo);

    return 0;
}
