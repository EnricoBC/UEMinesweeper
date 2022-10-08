#pragma once

#include "CoreMinimal.h"

enum ECellType
{
	Empty, Mine
};

struct FCell
{
	uint32 Row, Column;

	ECellType CellType = ECellType::Empty;

	bool bIsTested = false;

	/**
	* Determines if the cell has been flagged.
	*/
	bool bIsFlagged = false;

	bool bExploded = false;

	/**
	* Amount of Nearby mines.
	*/
	uint32 NearbyMines = 0;
};

/**
* Represents a minesweeper game board.
* Contains all the logic of the game.
*/
class FMinesweeperBoard
{
private:
	/**
	* Contains each cell's information for the minesweeper game.
	*/
	TArray<FCell> Board;

	uint32 AmountOfRows;
	uint32 AmountOfColumns;
	uint32 AmountOfMines;

	bool bStarted = false;
	bool bGameOver = false;
	bool bPlayerWon = false;

	uint32 TestedCells;

protected:
	/**
	* Obtains the cells that are Nearby to the cell at the specified row & column.
	*
	* @param Cells a reference to a set that will contain the Nearby cells.
	* @param Row the row of the cell in the board.
	* @param Column the column of the cell in the board.
	*/
	void GetNearbyCells(TSet<FCell*>& Cells, uint32 Row, uint32 Column);

	/**
	* Expands the board from where it was triggered.
	*
	* @param Row the row of the cell in the board.
	* @param Column the column of the cell in the board.
	*/
	void Expand(uint32 Row, uint32 Column);

	/**
	* Places a mine in the cell at the specified row & column.
	*
	* @param Row the row of the cell in the board.
	* @param Column the column of the cell in the board.
	* @return true if the mine was placed, otherwise false.
	*/
	bool PlaceMine(uint32 Row, uint32 Column);

	/**
	* Sets the cell as tested, checks if the game is finished.
	*
	* @param Cell the cell to set as tested.
	* @return true if the cell has a mine.
	*/
	bool SetCellTested(FCell* Cell);
public:
	/**
	* Finds the cell at the specified row & column.
	* @param Row the row of the cell in the board.
	* @param Column the column of the cell in the board.
	* @return the cell at the specified row & column.
	*/
	FCell* GetCell(uint32 Row, uint32 Column);

	/**
	* Configures a new game of Minesweeper with the specified amount of rows, columns and mines.
	* @param Rows the amount of rows for the board.
	* @param Columns the amount of columns for the board.
	* @param Mines the amount of mines to place in the board, this value must be lower than Rows * Columns.
	*/
	void Setup(uint32 Rows, uint32 Columns, uint32 Mines);

	/**
	* Places mines randomly across the board.
	* This should be used after the first click on the board to guarantee the first click to be safe.
	*/
	void PlaceMines();

	/**
	* Tests a cell to see if it has a mine.
	* 
	* @param Row the row of the cell in the board.
	* @param Column the column of the cell in the board.
	* @return true if a mine was triggered, false if it's safe.
	*/
	bool TestCell(uint32 Row, uint32 Column);

	inline uint32 GetAmountOfRows()
	{
		return AmountOfRows;
	};

	inline uint32 GetAmountOfColumns()
	{
		return AmountOfColumns;
	};

	inline bool IsGameOver()
	{
		return bGameOver;
	};

	inline bool HasPlayerWon()
	{
		return bPlayerWon;
	}
};
