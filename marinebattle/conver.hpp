#include <iostream>
#include <vector>
#include <random>

//#ifndef CONVER_HPP
//#define CONVER_HPP

using Coord = std::pair<int, int>;
enum kConst{
  FSize = 10,// Field size

  water = 20, // 20
  not_suited = 30, //30
  hitted = 31, // 31
  missed = 32
};


void CoordFormatStr(std::string& str);
void CoordMatch(std::string& begin, std::string& end);
void CoordFormat(Coord cr);
void CheckingLength(Coord begin, Coord end, int len);

class Field {
 public:
  Field();
  void MarkLocality(int x_1, int x_2, int y_1, int y_2);
  void PlaceShip(int ship_number, Coord begin, Coord end);
  int Shot(Coord coord);
  void ShowMyField();
  void ShowOpponentsField();
  int GetShipsCnt() const;


 private:
  std::vector<std::vector<int>> matrix_;
  std::vector<int> HPs_;
  int ships_alive_;
};


void GeneratePlayerField(Field& player_field);
void GenerateBotField(Field& bot_field);
void Shootout(Field& player_field, Field& bot_field);

//#endif