#include "player.hh"
#include <string>
#include "iostream"

using namespace std;

Player::Player(const std::string &name, int points):
    name_(name), points_(points){
}

std::string Player::get_name(){
    return name_;
}

int Player::get_points(){
    return points_;
}


void Player::add_points(int amount){
    if (points_ + amount > 50){
        points_ = 25;
        std::cout << name_ << " gets penalty points!" << std::endl;
    } else {
        points_ += amount;
    }
}

bool Player::has_won(){
    if (points_ == 50){
        return true;
    } else return false;
}
