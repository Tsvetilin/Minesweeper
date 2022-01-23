#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "State.hpp"

// Writes on the console 
struct Display {

	/// <summary>
	/// Write the pause menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="statusMessage">Game status message</param>
	void WritePauseMenu(short currentIndexSelected, const char* const statusMessage);

	/// <summary>
	/// Write the main menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteMainMenu(short currentIndexSelected, const char* const statusMessage);

	/// <summary>
	/// Write the settings menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteSettingsMenu(short currentIndexSelected, const char* const statusMessage);

	/// <summary>
	/// Write the game look menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="currentUsedIndex">The index of the currently active setting</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteLookSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);

	/// <summary>
	/// Write the game control menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="currentUsedIndex">The index of the currently active setting</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteControlSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);

	/// <summary>
	/// Write the game uncover settings menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="currentUsedIndex">The index of the currently active setting</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteUncoverSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);

	/// <summary>
	/// Write the game board size settings menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="options">The count of currently available board sizes</param>
	/// <param name="sizes">List of the sizes to choose from. See <see cref="Size"></param>
	/// <param name="currentUsedIndex">The index of the currently active setting</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteSizeSettingsMenu(short currentIndexSelected,
							   ushort options,
							   std::vector<Size*> sizes, 
							   ushort currentUsedIndex,
							   const char* const statusMessage);

	/// <summary>
	/// Write the game board symbols settings menu to the console
	/// </summary>
	/// <param name="currentIndexSelected">Current selected option</param>
	/// <param name="options">The count of currently available board symbols</param>
	/// <param name="sizes">List of the sizes to choose from</param>
	/// <param name="currentUsedIndex">The index of the currently active setting</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteSymbolsSettingsMenu(short currentIndexSelected, 
								  ushort options,
								  std::vector<char*> sizes,
								  ushort currentUsedIndex, 
								  const char* const statusMessage);

	/// <summary>
	/// Writes current game board according to the settings passed
	/// </summary>
	/// <param name="boardLook">The board look settigns. See <see cref="BoardLook"></param>
	/// <param name="boardSize">The board settigns. See <see cref="BoardSettings"</param>
	/// <param name="currentRowIndex">The current player position's row</param>
	/// <param name="currentColIndex">The current player position's colum</param>
	/// <param name="board">Pointer to the board to be printed</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteBoard(BoardLook boardLook, 
					BoardSettings boardSize,
					int currentRowIndex, 
					int currentColIndex,
					const char* const* const board,
					const char* const statusMessage);
	
	/// <summary>
	/// Writes the game board with revealed mines.
	/// </summary>
	/// <param name="boardLook">The board look settigns. See <see cref="BoardLook"></param>
	/// <param name="boardSize">The board settigns. See <see cref="BoardSettings"</param>
	/// <param name="playerBoard">Pointer to the player's current board</param>
	/// <param name="board">Pointer to the revealed board to be printed</param>
	/// <param name="statusMessage">Game status message</param>
	void WriteFinishBoard(BoardLook boardLook, 
						  BoardSettings boardSize,
						  const char* const* const playerBoard,
						  const char* const* const board,
						  const char* const statusMessage);
	
	/// <summary>
	/// Writes exit message.
	/// </summary>
	/// <param name="statusMessage">Game status message</param>
	void WriteExit(const char* const statusMessage);

	/// <summary>
	/// Writes game settings manual.
	/// </summary>
	void WriteManual();

private:

	/// <summary>
	/// Clears the screen using ANSII escape sequence
	/// </summary>
	void clearScreen();

	/// <summary>
	/// Colorizes the console output using ANSII escape sequence. To reset the colors, invoke the function with no params
	/// </summary>
	/// <param name="foregroundColor">The code for the foreground coloring</param>
	/// <param name="backgroundColor">The code for background coloring</param>
	void colorizeOutput(const char foregroundColor[] = "", const char backgroundColor[] = "");

	/// <summary>
	/// Write game name
	/// </summary>
	void writeHeader();

	/// <summary>
	/// Write the board coordinates and borders where necessary according to the settings passed
	/// </summary>
	/// <param name="isFancyBoard">Indicates whether fancy game setting is chosen</param>
	/// <param name="isSmallBoard">Indicates whether the board is smaller than 10x10</param>
	/// <param name="cols">The number of columns of the board</param>
	void writeBoardTop(bool isFancyBoard, bool isSmallBoard, ushort cols);

	/// <summary>
	/// Write the board walls at the bottom
	/// </summary>
	/// <param name="isSmallBoard">Indicates whether the board is smaller than 10x10</param>
	/// <param name="cols">The number of columns of the board</param>
	void writeBoardBottom(bool isSmallBoard, ushort cols);
};

#endif // !DISPLAY_H_
