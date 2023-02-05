#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

class Player
{
public:
    Player(const std::string &name, int points = 0);
    std::string get_name();
    int get_points();
    void add_points(int amount);
    bool has_won();
private:
    std::string name_;
    int points_;
};

#endif // PLAYER_HH
