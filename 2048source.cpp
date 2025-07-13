
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
#include "/home/ami3/codejunks/finishedProjects/2048/projectfiles/projectLibrary.hpp" //change depending on your file path.

int main(){
  
  ifstream file("/home/ami3/codejunks/finishedProjects/2048/projectfiles/copywriteNotice.txt"); //change depending on your file path.
    
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
  
  ifstream file("/home/ami3/codejunks/finishedProjects/2048/projectfiles/License text"); //change depending on your file path.
    
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
