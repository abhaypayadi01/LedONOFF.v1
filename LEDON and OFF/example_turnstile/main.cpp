#include "FiniteStateMachine.h"
#include <memory>
#include <iostream>
#include <conio.h>
#include <string>

using namespace Patterns;

bool KeyPresses[255];

enum class LED
{
  OFF,
  ON,
};


class TurnstileOFFState : public State<LED>
{
public:
  TurnstileOFFState(FiniteStateMachine<LED>& fsm)
    : State<LED>(fsm,
      LED::OFF, 
      "OFF")
  {
  }

  void enter()
  {
    State<LED>::enter();
    printf("led state: off \n");
  }

  void update()
  {
    State<LED>::update();
    if (KeyPresses['c'])
    {
      printf(" - coin inserted, unlocking turnstile\n");
      mFsm.setCurrentState(LED::ON);
    }
    else
    {
      printf("Please insert a coin by pressing c to unlock the turnstile.\n");
    }
  }
}; 

class TurnstileONState : public State<LED>
{
public:
  TurnstileONState(FiniteStateMachine<LED>& fsm)
    : State<LED>(fsm,LED::ON, "ON")
  {
  }

  void enter()
  {
    State<LED>::enter();
    printf("LED state: ON \n");
  }

  void update()
  {
    State<LED>::update();
    if (KeyPresses['p'])
    {
      printf(" - pushed, locking turnstile\n");
      mFsm.setCurrentState(LED::OFF);
    }
  }
};

int main(int argc, char* argv)
{
  printf("--------------------------------------------\n");
  printf("An example demo for the Finite State Machine\n");
  printf("--------------------------------------------\n");
  printf("  Press the c key to insert coin.\n");
  printf("  Press the p key to open the turnstile\n");
  printf("  Press the q key to quit\n");
  printf("--------------------------------------------\n");

  
  std::unique_ptr<FiniteStateMachine<LED>> fsm = std::make_unique<FiniteStateMachine<LED>>();

  State<LED>& state_locked = fsm->add<TurnstileOFFState>(LED::OFF);
  State<LED>& state_unlocked = fsm->add<TurnstileONState>(LED::ON);

  fsm->setCurrentState(LED::OFF);

  bool done = false;
  while (!done)
  {
    char input = _getch();
    KeyPresses[input] = true;
    if (KeyPresses['q'])
    {
      done = true;
      break;
    }

    fsm->update();

    for (int i = 0; i < 255; ++i)
      KeyPresses[i] = false;
  }
  printf("You have exited the program. Good bye!\n");
}