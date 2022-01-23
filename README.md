# Minesweeper

Console implementation of the famous Minesweeper game with customizable features made as a Course project for the Introduction to programming course in Faculty of Mathematics and Informatics of Sofia University
<br/><br/>

## Prerequisites and compilation
**Prerequisites:**  
Not all functionality may be supported on your OS and the Console you're using:
- Escape codes support required!
- Fancy board mode available only if Extended ASCII is spported!
- Advanced keyboard input available only if the libraries required are available!

**Compilation:**
- If using MSBuild run `msbuild Minesweeper.csproj`
- If using g++ run `g++ -Wall -std=c++20 lib/*.cpp src/Minesweeper.cpp -o Minesweeper.out` (or .exe)
- If using clang++ run `clang++ -Wall -std=c++20 lib/*.cpp src/Minesweeper.cpp -o Minesweeper.out` (or .exe)

**Running**
- Run `./Minesweeper.out` (or .exe) in the game directory
<br/><br/>

## Playing
**Settings:**
- Can be changed in the settings menu
- You can copy the `settings.json` file from the `assets` folder and use it as template to write your own board sizes and symbols! ***Important***: It must be named `settingsTemplate.minesweeper.json` and placed in the same directory as the .exe (or .out) file. The json syntax must strictly follow the example.
- The current game settings are saved in the file `settings.minesweeper`
- If a game is saved, it is placed in the `game.minesweeper` file

**Gameplay:**
- You can always go back by pressing (or writitng) `Escape` or `Q`!
- You can select by pressing `Enter`
- `F` stands for flag -> marking a position as bomb or removing an already placed flag
- `R` stands for reveal -> revealing the current position (or position specified)
<br/><br/>

## License
Minesweeper is distributed under the GNU General Public License GPLv3 or higher, see the file LICENSE for details.