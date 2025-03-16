#include "conver.hpp"

int main() {
  std::cout << "Greetings Captain" << '\n';
  std::cout << "Let's, place your ships" << '\n';
  std::cout << "Place them at the format \" a1 - beginning of the ship, b1 - ending of the ship\"" << '\n';

  Field player_field;
  GeneratePlayerField(player_field);

  Field bot_field;
  GenerateBotField(bot_field);

  std::cout << "Let's start our fight" << '\n';
  std::cout << "Make a move at the format \"a1 - the shot coordinate\"" << '\n';
  Shootout(player_field, bot_field);

  std::cout << "Thank you for game, come back again ;)";
  return 0;
}