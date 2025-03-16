#include "conver.hpp"

void CoordFormatStr(std::string& str) {
  if (str[0] - 'a' >= FSize || str[0] - 'a' < 0) {
    throw std::exception();
  }

  if (str.size() == 3) {
    if (!(str[1] == '1' && str[2] == '0')) {
      throw std::exception();
    }
    return;
  } else if (str.size() == 2) {
    if (!(str[1] - '0' < FSize && str[1] - '0' > 0)) {
      throw std::exception();
    }
    return;
  }

  throw std::exception();
}
void CoordMatch(std::string& begin, std::string& end) {
  if (begin[0] != end[0]) {
    if (begin.size() != begin.size()) {
      throw std::exception();
    }
    if (begin[1] != end[1]) {
      throw std::exception();
    }
  }
}
void CoordFormat(Coord cr) { // for GenerateBotField
  if (cr.first >= FSize || cr.first < 0 || cr.second >= FSize || cr.second < 0) {
    throw std::exception();
  }
}
void CheckingLength(Coord begin, Coord end, int len) {
  if (begin.first == end.first) {
    auto [a, b] = (begin.second < end.second) ?
                  std::make_pair(begin.second, end.second) :
                  std::make_pair(end.second, begin.second);
    if (b - a + 1 != len) {
      throw std::exception();
    }
  } else {
    auto [a, b] = (begin.first < end.first) ?
                  std::make_pair(begin.first, end.first) :
                  std::make_pair(end.first, begin.first);
    if (b - a + 1 != len) {
      throw std::exception();
    }
  }
}

Field::Field() : matrix_(10, std::vector<int> (FSize, water)), HPs_(FSize) {
  for (int i = 0; i < 4; ++i) { HPs_[i] = 1; }
  for (int i = 4; i < 7; ++i) { HPs_[i] = 2; }
  for (int i = 7; i < 9; ++i) { HPs_[i] = 3; }
  HPs_[9] = 4;
  ships_alive_ = 10;
}
void Field::MarkLocality(int x_1, int x_2, int y_1, int y_2) {
  bool a, b, c, d;
  a = (0 < x_1);
  b = (x_2 < 9);
  c = (0 < y_1);
  d = (y_2 < 9);

  if (a) {
    for (int i = y_1; i <= y_2; ++i) {
      matrix_[x_1 - 1][i] = not_suited;
    }
  }

  if (b) {
    for (int i = y_1; i <= y_2; ++i) {
      matrix_[x_2 + 1][i] = not_suited;
    }
  }

  if (c) {
    for (int i = x_1; i <= x_2; ++i) {
      matrix_[i][y_1 - 1] = not_suited;
    }
  }

  if (d) {
    for (int i = x_1; i <= x_2; ++i) {
      matrix_[i][y_2 + 1] = not_suited;
    }
  }

  if (a && c) {
    matrix_[x_1 - 1][y_1 - 1] = not_suited;
  }
  if (a && d) {
    matrix_[x_1 - 1][y_2 + 1] = not_suited;
  }
  if (b && c) {
    matrix_[x_2 + 1][y_1 - 1] = not_suited;
  }
  if (b && d) {
    matrix_[x_2 + 1][y_2 + 1] = not_suited;
  }
}
void Field::PlaceShip(int ship_number, Coord begin, Coord end) {
  // корректность координат гарантированна
  if (begin.first == end.first) { // заполняем "корабль" по вертикале
    auto [a, b] = (begin.second < end.second) ?
                  std::make_pair(begin.second, end.second) :
                  std::make_pair(end.second, begin.second);
    int keep;
    try {
      for (keep = a; keep <= b; ++keep) {
        if (matrix_[begin.first][keep] != water) {
          throw std::exception();
        }
        matrix_[begin.first][keep] = ship_number;
      }
    } catch (...) { // обработка ошибки
      --keep;
      for (; keep >= a; --keep) { // возвращаем все на место
        matrix_[begin.first][keep] = water;
      }
      throw std::exception();
    }
    MarkLocality(begin.first, begin.first, a, b);

  } else { // заполняем "корабль" по горизонтале
    auto [a, b] = (begin.first < end.first) ?
                  std::make_pair(begin.first, end.first) :
                  std::make_pair(end.first, begin.first);
    int keep;
    try {
      for (keep = a; keep <= b; ++keep) { // возвращаем все на место
        if (matrix_[keep][begin.second] != water) {
          throw std::exception();
        }
        matrix_[keep][begin.second] = ship_number;
      }
    } catch (...) { // обработка ошибки
      --keep;
      for (; keep >= a; --keep) {
        matrix_[keep][begin.second] = water;
      }
      throw std::exception();
    }
    MarkLocality(a, b, begin.second, begin.second);
  }
}
int Field::Shot(Coord coord) {
  int indicator = matrix_[coord.first][coord.second];

  if (indicator == missed || indicator == hitted) {
    throw std::exception();
  }

  if (indicator == water ||
      indicator == not_suited) {
    matrix_[coord.first][coord.second] = missed;
    return 0;
  }

  matrix_[coord.first][coord.second] = hitted;
  --HPs_[indicator];
  if (HPs_[indicator] == 0) {
    --ships_alive_;
    return 2;
  } else {
    return 1;
  }
}
void Field::ShowMyField() {
  std::cout << "   A B C D E F G H I J" << '\n';
  for (int i = 0; i < FSize; ++i) {
    if (FSize - i == 10) {
      std::cout << FSize - i << ' ';
    } else {
      std::cout << FSize - i << "  ";
    }

    for (int j = 0; j < FSize; ++j) {
      if (matrix_[j][FSize - 1 - i] == water || matrix_[j][FSize - 1 - i] == not_suited) {
        std::cout << '.' << ' ';
      } else if (matrix_[j][FSize - 1 - i] == hitted) {
        std::cout << 'X' << ' ';
      } else if (matrix_[j][FSize - 1 - i] == missed) {
        std::cout << 'm' << ' ';
      } else {
        std::cout << '#' << ' ';
      }
    }
    std::cout << '\n';
  }
}
void Field::ShowOpponentsField() {
  std::cout << "   A B C D E F G H I J" << '\n';
  for (int i = 0; i < FSize; ++i) {
    if (FSize - i == 10) {
      std::cout << FSize - i << ' ';
    } else {
      std::cout << FSize - i << "  ";
    }

    for (int j = 0; j < FSize; ++j) {
      if (matrix_[j][FSize - 1 - i] == hitted) {
        std::cout << 'X' << ' ';
      } else if (matrix_[j][FSize - 1 - i] == missed) {
        std::cout << 'm' << ' ';
      } else {
        std::cout << '.' << ' ';
      }
    }
    std::cout << '\n';
  }
}
int Field::GetShipsCnt() const {
  return ships_alive_;
}

void GeneratePlayerField(Field& player_field) {
  int ship_number = 0;
  for (int slen = 1; slen < 5; ++slen) { // we had to be able to use "10" at second argument
    for (int num = 0; num < 5 - slen; ++num) {
      std::cout << "Place " << slen << "-deck ship" << '\n';

      std::string begin_coord;
      std::string end_coord;
      std::cin >> begin_coord >> end_coord;

      try {
        CoordFormatStr(begin_coord);
        CoordFormatStr(end_coord);
        CoordMatch(begin_coord, end_coord);
      } catch (...) {
        std::cout << "Incorrect coordinate format, try again" << '\n';
        --num;
        continue;
      } // checking for valid input

      Coord b_c;
      Coord e_c;

      if (begin_coord.size() == 3) {
        b_c = Coord(begin_coord[0] - 'a', FSize - 1);
      } else {
        b_c = Coord(begin_coord[0] - 'a', begin_coord[1] - '1');
      }

      if (end_coord.size() == 3) {
        e_c = Coord(end_coord[0] - 'a', FSize - 1);
      } else {
        e_c = Coord(end_coord[0] - 'a', end_coord[1] - '1');
      }

      try {
        CheckingLength(b_c, e_c, slen);
      } catch (...) {
        std::cout << "Wrong size" << '\n';
        --num;
        continue;
      }

      try {
        player_field.PlaceShip(ship_number, b_c, e_c);
      } catch (...) {
        std::cout << "You can't put here your ship" << '\n';
        --num;
        continue;
      }
      ++ship_number;
      player_field.ShowMyField();
    }
  }
}
void GenerateBotField(Field& bot_field) {
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<> u_d1{0, FSize - 1};
  std::uniform_int_distribution<> u_d2{0, 3};

  int ship_number = 0;
  for (int slen = 1; slen < 5; ++slen) {
    for (int num = 0; num < 5 - slen; ++num) {
      std::string begin_coord;
      std::string end_coord;

      int char_coord = u_d1(mt);
      int int_coord = u_d1(mt);
      int direction = u_d2(mt);

      Coord b_c;
      Coord e_c;

      if (direction == 0) {
        b_c = Coord(char_coord, int_coord);
        e_c = Coord(char_coord + slen - 1, int_coord);
      } else if (direction == 1) {
        b_c = Coord(char_coord, int_coord);
        e_c = Coord(char_coord, int_coord + slen - 1);
      } else if (direction == 2) {
        b_c = Coord(char_coord, int_coord);
        e_c = Coord(char_coord - slen + 1, int_coord);
      } else if (direction == 3) {
        b_c = Coord(char_coord, int_coord);
        e_c = Coord(char_coord, int_coord - slen + 1);
      }

      try {
        CoordFormat(b_c);
        CoordFormat(e_c);
      } catch (...) {
        --num;
        continue;
      }

      try {
        bot_field.PlaceShip(ship_number, b_c, e_c);
      } catch (...) {
        --num;
        continue;
      }
      ++ship_number;
    }
  }
}
void Shootout(Field& player_field, Field& bot_field) {
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<> u_d{0, FSize - 1};

  int get;
  for (int turn = 1;; ++turn) {
    if (turn % 2 == 1) { //// Player's move
      player_field.ShowMyField();
      bot_field.ShowOpponentsField();
      std::string hit_str;
      std::cin >> hit_str;

      try {
        CoordFormatStr(hit_str);
      } catch (...) {
        std::cout << "Incorrect coordinate format, try again" << '\n';
        --turn;
        continue;
      }

      Coord hit_p;
      if (hit_str.size() == 3) {
        hit_p = Coord(hit_str[0] - 'a', 9);
      } else {
        hit_p = Coord(hit_str[0] - 'a', hit_str[1] - '1');
      }

      try {
        get = bot_field.Shot(hit_p);
      } catch (...) {
        std::cout << "You have already shot this cell, try again" << '\n';
        --turn;
        continue;
      }

      if (get == 0) {
        std::cout << "Miss" << '\n';
      } else if (get == 1) {
        std::cout << "Got it!" << '\n';
        --turn;
        bot_field.ShowOpponentsField();
        continue;
      } else {
        std::cout << "Destroyed it!" << '\n';
        if (bot_field.GetShipsCnt() == 0) {
          std::cout << "Congratulations on your victory, You won!!!" << '\n';
          break;
        }
        --turn;
        bot_field.ShowOpponentsField();
        continue;
      }
    } else { //// Bot's move
      int pin_str = u_d(mt);
      int pin_num = u_d(mt);
      Coord hit_b(pin_str, pin_num);

      try {
        get = player_field.Shot(hit_b);
      } catch (...) {
        --turn;
        continue;
      }

      if (get == 0) {
        std::cout << "Bot Missed" << '\n';
      } else if (get == 1) {
        std::cout << "Bot Got it!" << '\n';
        --turn;
        continue;
      } else {
        std::cout << "Bot Destroyed" << '\n';
        if (player_field.GetShipsCnt() == 0) {
          std::cout << "Long live the machine revolution!!!" << '\n';
          break;
        }
        --turn;
        continue;
      }
    }
  }
}