
  //2048 clone in the linux terminal.
  //Copyright (C) 2025 River Knuuttila, common alias, Annie.

  //This program is free software: you can redistribute it and/or modify
  //it under the terms of the GNU General Public License as published by
  //the Free Software Foundation, either version 3 of the License, or
  //(at your option) any later version.

  //This program is distributed in the hope that it will be useful,
  //but WITHOUT ANY WARRANTY; without even the implied warranty of
  //MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //GNU General Public License for more details.

  //You should have received a copy of the GNU General Public License
  //along with this program.  If not, see <https://www.gnu.org/licenses/>.
  
  //Concerns or questions? Reach out at: riverknuuttila2@outlook.com

#include <sstream>
#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <random>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "projectfiles/projectLibrary.hpp" //change depending on your file path.
  
string tileColor(int value)
{
  switch (value)
  {
    case 0:    return "\033[48;5;187m"; // empty (#cdc1b4)
    case 2:    return "\033[48;5;254m"; // #eee4da
    case 4:    return "\033[48;5;230m"; // #ede0c8
    case 8:    return "\033[48;5;215m"; // #f2b179
    case 16:   return "\033[48;5;209m"; // #f59563
    case 32:   return "\033[48;5;208m"; // #f67c5f
    case 64:   return "\033[48;5;202m"; // #f65e3b
    case 128:  return "\033[48;5;221m"; // #edcf72
    case 256:  return "\033[48;5;220m"; // #edcc61
    case 512:  return "\033[48;5;178m"; // #edc850
    case 1024: return "\033[48;5;178m"; // #edc53f
    case 2048: return "\033[48;5;220m"; // #edc22e
    default:   return "\033[48;5;187m"; // fallback (empty)
  }
}

void emptyBox()
{
  cout << "|" << tileColor(0) << "    " << "\033[0m";
}

void printBox(int displayNumber)
{
  string bg = tileColor(displayNumber);
  string fg = "\033[38;5;0m"; // black text

  if (displayNumber > 0)
  {
    if (displayNumber >= 1000)
      {
      cout << "|" << bg << fg << displayNumber << "\033[0m";
      }
    else if (displayNumber >= 100)
      {
      cout << "|" << bg << fg << displayNumber << " " << "\033[0m";
      }
    else if (displayNumber >= 10)
      {
      cout << "|" << bg << fg << displayNumber << "  " << "\033[0m";
      }
    else
    {
      cout << "|" << bg << fg << " " << displayNumber << "  " << "\033[0m";
    }
  }
  else
  {
    emptyBox();
  }
}

void printGame(int playingGrid[4][4]) //prints the playingGrid and cubes containing numbers.
{
  for (int i = 0; i < 4; i++)
  {
    cout<<"_____________________" << endl;
    for (int j = 0; j < 4; j++)
    {
      printBox(playingGrid[i][j]);
    }
    cout<<"|"<<endl;
  }
  cout<<"_____________________" << endl;
}

int main(){

  int score = 0;
  
  ifstream file("projectfiles/copywriteNotice.txt"); //change depending on your file path.
    
  if (!file) 
  {
    cerr<<"Could not open the file!"<<endl;
    return 1;
  }

  stringstream uffer;
  uffer<<file.rdbuf();

  string contentS=uffer.str();

  cout<<contentS<<endl;

  string noticeA;

  cin>>noticeA;

if (noticeA=="r")
{
  int playingGrid[4][4] = {0}; //multidimensional array initialized to zero. represented by logic of functions above.

  newRandomBox(playingGrid);
    newRandomBox(playingGrid);

  clearScreen();
    printGame(playingGrid);

  setBufferedInput(false);

  while (true) //main gamestate.
  {
    char cont = getchar();

    if (cont == 'q')
      break;

    bool moved = false;

    if (cont == '\033')
    {
      if (getchar() == '[')
      {
        char direction = getchar();
        switch (direction) //switch statement for player inputs
        {
        case 'A': // up key
          moved = moveUp(playingGrid);
            break;
        case 'B': // down key
            moved = moveDown(playingGrid);
            break;
        case 'C': // right key
          moved = moveRight(playingGrid);
            break;
        case 'D': // left key
          moved = moveLeft(playingGrid);
            break;
        }
      }
    }

    if (moved)
    {
      newRandomBox(playingGrid);
        clearScreen();
          printGame(playingGrid);

      if (!canMove(playingGrid)) //lose condition.
      {
        getScore(playingGrid,score);
        cout<<"Game Over!"<<endl<<"score: "<<score<<endl;
        break;
      }
    }

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j<4; j++)
      {
        if (playingGrid[i][j]==2048)
        {
          getScore(playingGrid,score);
          cout<<" GG, you win! :3"<<endl<<"score : "<<score<<endl; //win condition
          break;
        }
      }
    }
  }

  setBufferedInput(true);
}
else if (noticeA=="d")
{
  
  ifstream file("projectfiles/License text"); //change depending on your file path.
    
  if (!file) 
  {
    cerr<<"Could not open the file!"<<endl;
    return 1;
  }

  stringstream uuffer;
  uuffer<<file.rdbuf();

  string ccontentS=uuffer.str();

  cout<<ccontentS<<endl;
}
else if (noticeA=="q")
{
  cout<<"Exiting!";
}
return 0;}
