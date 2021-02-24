#include "UI/SystemDriverUI.hpp"

#include "Domain/Session/SessionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"
#include "Domain/Account/AccountHandler.hpp"

namespace UI
{
  // Default constructor
  SystemDriverUI::SystemDriverUI()
  : _loggerPtr( TechnicalServices::Logging::LoggerHandler::create() )
  {
    _logger << "Contracted UI being used and has been successfully initialized";
  }




  // Destructor
  SystemDriverUI::~SystemDriverUI() noexcept
  {
    _logger << "Contracted UI shutdown successfully";
  }




  // Operations
  void SystemDriverUI::launch()
  {
    {
      _logger << "Starting scenario 1: Purchase Products";

      auto session     = Domain::Session::SessionHandler::createSession( {"James", "Vu", {"Customer"}} );
      auto cart        = Domain::ShoppingCart::ShoppingCartHandler::createShoppingCart();
      auto productList = cart->viewProducts();
                         cart->addProduct("Pizza", 1);
      auto order       = cart->initiateCheckout();
                         order->setOrderInstruction("123 Street", "Keep warm");
      auto total       = order->calculateTotal();
      auto message     = order->makePayment(1234, "12/06", 567);
                         session->signOff();
      _logger << "Completed scenario 1";

      _logger << "Starting scenario 2: Manage Reward Points";
      auto session2  = Domain::Session::SessionHandler::createSession( {"James", "Vu", {"Customer"}} );
      auto account2  = Domain::Account::AccountHandler::createAccount();
      auto balance2  = account2->getRewardPointBalance();
      auto messsage2 = account2->spendRewardPoints("Basic Reward");
      auto rewards2  = account2->getOwnedRewards();
                      account2->applyRewardToPurchase("Basic Reward");
      session2->signOff();
      _logger << "Completed scenario 2";
    }
  }
}    // namespace UI
