#pragma once

#include <any>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/Account/AccountHandler.hpp"
#include "Domain/Account/Reward.hpp"

namespace Domain::Account
{
  class CustomerAccount : public AccountHandler
  {
    public:
      // using AccountHandler::AccountHandler;  // inherit constructors
      CustomerAccount() {
        _logger << "Customer Account being used and has been successfully initialized";
      }

      // Operations
      std::string spendRewardPoints(std::string reward);
      int  getRewardPointBalance();
      void applyRewardToPurchase(std::string reward);
      std::vector<std::string> getOwnedRewards();

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~CustomerAccount() noexcept override;
    private:
      std::shared_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;
      std::list<Domain::Account::Reward *> _ownedRewards;
      int _rewardPoints = 1000;
  }; // class BorrowerAccount

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline CustomerAccount::~CustomerAccount() noexcept
  {
    _logger << "Customer Account shutdown successfully";
  }

  inline std::string CustomerAccount::spendRewardPoints(std::string reward)
  {
    if (reward == "Basic Reward") {
      _rewardPoints -= 100;
      Domain::Account::BasicReward *basic = new Domain::Account::BasicReward();
      _ownedRewards.push_back(basic);
    }
    _logger << "Responding to spendRewardPoints request with parameters: " + reward;
    _logger << "Added " + reward + " to owned rewards list";

    std::string results = "You got a " + reward + ". " + std::to_string(_rewardPoints) + " reward points remaining.";
    _logger << "Responding with: " + results;
    return results;
  }

  inline int CustomerAccount::getRewardPointBalance()
  {
    _logger << "Responding to getRewardPointBalance request with parameters: ";
    _logger << "Current Reward Point Balance: " + std::to_string(_rewardPoints);
    return _rewardPoints;
  }

  inline void CustomerAccount::applyRewardToPurchase(std::string reward)
  {
    _logger << "Responding to applyRewardToPurchase request with parameters: " + reward;
    _logger << "Applied " + reward + " to current purchase";
    return;
  }

  inline std::vector<std::string> CustomerAccount::getOwnedRewards()
  {
    _logger << "Responding to getOwnedRewards request with parameters: ";
    _logger << "You have a Basic Reward";
    std::vector<std::string> results;
    results.push_back("Basic Reward");
    return results;
  }
} // namespace Domain::Library
