#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <math.h>

using namespace std;

class Spaceship {
    private:
        string mName;
        int mAttack;
        int mShield;

    public:
        Spaceship() {
            this->mName = "nedefinit";
            this->mAttack = 0;
            this->mShield = 0;
        }

        Spaceship(string mName, int mAttack, int mShield) {
            this->mName = mName;
            this->mAttack = mAttack;
            this->mShield = mShield;
        }

        Spaceship(const Spaceship& ship) {
            this->mName = ship.mName;
            this->mAttack = ship.mAttack;
            this->mShield = ship.mShield;
        }

        string getName() {
          return mName;
        }

        int getAttack() {
          return mAttack;
        }

        int getShield() {
          return mShield;
        }

        void setName(string mName) {
          this->mName = mName;
        }

        void setAttack(int mAttack) {
          this->mAttack = mAttack;
        }

        void setShield(int mShield) {
          this->mShield = mShield;
        }

        Spaceship& operator= (const Spaceship& ship) {
          this->mName = ship.mName;
          this->mAttack = ship.mAttack;
          this->mShield = ship.mShield;

          return *this;
        }

        Spaceship operator+= (const Spaceship& ship) {
          this->mAttack += ship.mAttack;
          this->mShield += ship.mShield;

          return *this;
        }

        Spaceship operator-= (const Spaceship& ship) {
          this->mShield -= ship.mAttack;

          return *this;
        }

        Spaceship operator^ (const Spaceship& ship) {
          Spaceship selfCopy(*this);
          Spaceship enemyCopy(ship);

          while (true) {
            selfCopy -= enemyCopy;
            if (selfCopy.mShield <= 0) {
              return enemyCopy;
            }
            enemyCopy -= selfCopy;
            if (enemyCopy.mShield <= 0) {
              return selfCopy;
            }
          }
        }

        bool operator< (const Spaceship& ship) {
          return ((this->mAttack + this->mShield) > (ship.mAttack + ship.mShield));
        }
};

int main() {
    unordered_map<string, Spaceship> ships;
    int numShips;
    string name;
    int attack, shield;
    cin >> numShips;

    for (int i = 0; i < numShips; i++) {
      cin >> name >> attack >> shield;
      ships[name] = Spaceship(name, attack, shield);
    }

    int numActions;
    string action, ship1, ship2;
    cin >> numActions;
    for (int i = 0; i < numActions; i++) {
      cin >> action >> ship1 >> ship2;

      if (action == "lupta" || action == "fight") {
        Spaceship winner = ships[ship2] ^ ships[ship1];
        ships[ship1] = winner;
        if (winner.getName() == ship1) {
          ships.erase(ship2);
        } else {
          ships.erase(ship1);
        }
      } else if (action == "combina" || action == "transfer") {
        ships[ship1] += ships[ship2];
        ships.erase(ship2);
      }
    }

    vector<Spaceship> spaceshipVector;
    for (auto& it: ships) {
      spaceshipVector.push_back(it.second);
    }

    sort(spaceshipVector.begin(), spaceshipVector.end());
    for (Spaceship& ship : spaceshipVector) {
      cout << ship.getName() << "\n";
    }

    return 0;
}