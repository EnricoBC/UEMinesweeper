#pragma once

#include "Logic/MinesweeperBoard.h"

struct FCell;

/**
 * @brief Represents a window containing the Minesweeper widget & game logic.
 */
class FMinesweeperWindow : public TSharedFromThis<FMinesweeperWindow>
{
public:
    FMinesweeperWindow();

    /**
     * @brief Callback when the user presses the `New Game` button.
     * 
     * Configures a new game of Minesweeper to play in the Editor.
     * 
     * @return FReply 
     */
    FReply OnNewGameClick();

    /**
     * @brief Callback when the user presses any of the game's grid buttons.
     * 
     * Tests a field in the board to see if there's a mine.
     * 
     * @param CellData The data associated to the clicked button.
     * @return FReply 
     */
    FReply OnCellClick(struct FCellData CellData);

    /**
	 * @brief Obtains the current amount of rows configured for the game.
	 * 
	 * @return int32 the amount of rows.
     */
    int32 GetRows();

    /**
	 * @brief Obtains the current amount of columns configured for the game.
	 * 
	 * @return int32 the amount of columns.
     */
    int32 GetColumns();

    /**
     * @brief Gets the slate UI widget.
     * 
     * @return TSharedRef<class SMinesweeperWidget> The widget associated to this window instance.
     */
    TSharedRef<class SMinesweeperWidget> GetWidget();

    /**
     * @brief Gets the board cell object reference at the specified position.
     * 
     * @param Row the cell's row.
     * @param Column the cell's column.
     * @return FCell* the cell at the specified position.
     */
	FCell* GetCell(uint32 Row, uint32 Column);

    /**
     * @brief Checks the status of the game.
     * 
     * @return true if the game is over, otherwise false.
     */
	inline bool IsGameOver()
	{
		return Board.IsGameOver();
	};

    /**
     * @brief Checks if the player won the game.
     * 
     * @return true if the game is over and the player won, otherwise false.
     */
	inline bool HasPlayerWon()
	{
		return Board.HasPlayerWon();
	}
private:
    /**
     * @brief The board of the game.
     */
    FMinesweeperBoard Board;

    /**
     * @brief The UI widget.
     */
    TSharedPtr<class SMinesweeperWidget> Widget;
};