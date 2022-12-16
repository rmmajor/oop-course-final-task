#include <bits/stdc++.h>
#include "boost/di.hpp"

using namespace std;
namespace di = boost::di;

class IGameMode
{
public:
    virtual void printWinner() = 0;
};

class IPlayer
{
public:
    virtual string makeChoice() = 0;
};

class IWinner
{
public:
    virtual void   setChoices(IPlayer* player1, IPlayer* player2) = 0;
    virtual string setWinner()  = 0;

};


class Human : public IPlayer
{
public:
    string choice;

    string makeChoice() override
    {
        cout << "Enter Rock, Paper or Scissors\n";
        cin >> (this->choice);
        return choice;

    }

    Human() {};
};


class Winner : public IWinner
{
private:
    string win1 = "First player won\n",
           win2 = "Second player won\n",
           draw = "It`s a draw\n";

public:
    string player1, player2;

    Winner () {};

    void setChoices(IPlayer* player1, IPlayer* player2)
    {
        this->player1 = player1->makeChoice();
        this->player2 = player2->makeChoice();
        //cout << "here\n";
    }

    string setWinner() override
    {

        if (this->player1 == "Rock")
        {
            if (this->player2 == "Scissors") return win1;
            if (this->player2 == "Paper") return win2;
            if (this->player2 == "Rock") return draw;
        }

        if (this->player1 == "Scissors")
        {
            if (this->player2 == "Paper") return win1;
            if (this->player2 == "Rock") return win2;
            if (this->player2 == "Scissors") return draw;
        }

        if (this->player1 == "Paper")
        {
            if (this->player2 == "Rock") return win1;
            if (this->player2 == "Scissors") return win2;
            if (this->player2 == "Paper") return draw;
        }
    }
};

class PvP : public IGameMode
{
private:
    IPlayer* player1 = nullptr;
    IPlayer* player2 = nullptr;
    IWinner* winner  = nullptr;

public:
    PvP(IPlayer* playerA, IPlayer* playerB, IWinner* winnerA) : player1(playerA), player2(playerB), winner(winnerA)
    {}

    void printWinner() override
    {
        //cout << player1;
        winner->setChoices(player1, player2);
        cout << winner->setWinner();
    }
};

class PvE : public IGameMode
{
private:
    IPlayer* player1 = nullptr;
    IPlayer* player2 = nullptr;
    IWinner* winner  = nullptr;

public:
    PvE (IPlayer* playerA, IPlayer* playerB, IWinner* winnerA) : player1(playerA), player2(playerB), winner(winnerA)
    {}

    void printWinner() override
    {
        winner->setChoices(player1, player2);
        cout << winner->setWinner();
    }
};

class Game
{
public:
    IGameMode* gameMode = nullptr;

    Game(IGameMode* gameM) : gameMode(gameM) {};

    void play()
    {

        gameMode->printWinner();
    }
};

int main()
{
    auto inject_PvP = di::make_injector(
                          di::bind<IGameMode>.to<PvP>(),
                          di::bind<IWinner>.to<Winner>(),
                          di::bind<IPlayer>.to<Human>()
                      );

    string gameMode;
    cout << "Choose PvP or PvE\n";
    cin >> gameMode;
    if (gameMode == "PvP")
    {
        auto game = inject_PvP.create<Game>();
        //cout << "here\n";
        game.play();
    }
    else if (gameMode == "PvE")
    {
        cout << "Comming soon\n";
        return 0;
    }
    else
    {
        cout << "There is some issue\n";
        return 0;
    }
}
