#pragma once

#include "CoreMinimal.h"

/**
 * @brief Determines the type of cell.
 */
enum ECellType
{
	Empty, Mine
};

struct FCell
{
	/**
	 * @brief The row of the cell.
	 */
	uint32 Row;

	/**
	 * @brief The column of the cell.
	 */
	uint32 Column;

	/**
	 * @brief The type of cell.
	 */
	ECellType CellType = ECellType::Empty;

	/**
	 * @brief Determines if the cell has been checked for mines.
	 */
	bool bIsTested = false;

	/**
	 * @brief Determines if the cell has exploded due to a mine check.
	 */
	bool bExploded = false;

	/**
	 * @brief Amount of Nearby mines.
	 */
	uint32 NearbyMines = 0;
};

/**
 * @brief Represents a minesweeper game board.
 * Contains all the logic of the game.
 */
class FMinesweeperBoard
{
public:
	/**
	 * @brief Finds the cell at the specified row & column.
	 * @param Row the row of the cell in the board.
	 * @param Column the column of the cell in the board.
	 * @return the cell at the specified row & column.
	 */
	FCell* GetCell(uint32 Row, uint32 Column);

	/**
	 * @brief Configures a new game of Minesweeper with the specified amount of rows, columns and mines.
	 * 
	 * @param Rows the amount of rows for the board.
	 * @param Columns the amount of columns for the board.
	 * @param Mines the amount of mines to place in the board, this value must be lower than Rows * Columns.
	 */
	void Setup(uint32 Rows, uint32 Columns, uint32 Mines);

	/**
	 * @brief Places mines randomly across the board.
	 * 
	 * This should be used after the first click on the board to guarantee the first click to be safe.
	 */
	void PlaceMines();

	/**
	 * @brief Tests a cell to see if it has a mine.
	 * 
	 * @param Row the row of the cell in the board.
	 * @param Column the column of the cell in the board.
	 * @return true if a mine was triggered, false if it's safe.
	 */
	bool TestCell(uint32 Row, uint32 Column);

	/**
	 * @brief Gets the amount of rows setup.
	 * 
	 * @return uint32 the amount of rows.
	 */
	inline uint32 GetAmountOfRows()
	{
		return AmountOfRows;
	};

	/**
	 * @brief Gets the amount of columns setup.
	 * 
	 * @return uint32 the amount of columns.
	 */
	inline uint32 GetAmountOfColumns()
	{
		return AmountOfColumns;
	};

	/**
	 * @brief Returns the bGameOver flag.
	 * 
	 * @return true if the game is over, otherwise false.
	 */
	inline bool IsGameOver()
	{
		return bGameOver;
	};

	/**
	 * @brief Returns the bPlayerWon flag.
	 * 
	 * @return true if the player has won the game, otherwise false. 
	 */
	inline bool HasPlayerWon()
	{
		return bPlayerWon;
	}
protected:
	/**
	 * @brief Obtains the cells that are Nearby to the cell at the specified row & column.
	 *
	 * @param Cells a reference to a set that will contain the Nearby cells.
	 * @param Row the row of the cell in the board.
	 * @param Column the column of the cell in the board.
	 */
	void GetNearbyCells(TSet<FCell*>& Cells, uint32 Row, uint32 Column);

	/**
	 * @brief Expands the board from where it was triggered.
	 *
	 * @param Row the row of the cell in the board.
	 * @param Column the column of the cell in the board.
	 */
	void Expand(uint32 Row, uint32 Column);

	/**
	 * @brief Places a mine in the cell at the specified row & column.
	 *
	 * @param Row the row of the cell in the board.
	 * @param Column the column of the cell in the board.
	 * @return true if the mine was placed, false if a mine already existed in the cell.
	 */
	bool PlaceMine(uint32 Row, uint32 Column);

	/**
	 * @brief Sets the cell as tested, checks if the game is finished.
	 *
	 * @param Cell the cell to set as tested.
	 * @return true if the cell has a mine.
	 */
	bool SetCellTested(FCell* Cell);
private:
	/**
	 * @brief Contains each cell's information for the minesweeper game.
	 */
	TArray<FCell> Board;

	/// @brief The amount of rows.
	uint32 AmountOfRows;

	/// @brief The amount of columns.
	uint32 AmountOfColumns;

	/// @brief The amount of mines.
	uint32 AmountOfMines;

	/// @brief Flag to determine if the game has started.
	bool bStarted = false;

	/// @brief Flag to determine if the game has ended.
	bool bGameOver = false;

	/// @brief Flag to determine if the player won the game.
	bool bPlayerWon = false;

	/**
	 * @brief Contains the amount of tested cells.
	 * 
	 * This is used to check if the game has finished.
	 */
	uint32 TestedCells;
};
