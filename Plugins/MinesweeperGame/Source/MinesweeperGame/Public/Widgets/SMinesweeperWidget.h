#pragma once

#include "CoreMinimal.h"
#include "Windows/MinesweeperWindow.h"
#include "Widgets/Layout/SUniformGridPanel.h" 
#include "Widgets/Input/SSpinBox.h" 
#include "Widgets/SUserWidget.h"

/**
 * @brief Utility struct that contains a cell's row and column.
 * 
 * This data is passed to each button on click.
 */
struct FCellData
{
	int32 CellRow;
	int32 CellColumn;

	FCellData(int32 Row, int32 Column)
	{
		CellRow = Row;
		CellColumn = Column;
	};
};

/**
 * @brief Slate widget that contains all the widgets required to configure and play the Minesweeper game.
 */
class SMinesweeperWidget : public SUserWidget
{
public:
	SLATE_USER_ARGS(SMinesweeperWidget)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<class FMinesweeperWindow>& Window);

	/**
	 * @brief Obtains the amount of rows set in the `Rows` text box.
	 * 
	 * @return int32 the amount of rows.
	 */
	int32 GetRows();

	/**
	 * @brief Obtains the amount of columns set in the `Columns` text box.
	 * 
	 * @return int32 the amount of columns.
	 */
	int32 GetColumns();

	/**
	 * @brief Obtains the amount of mines set in the `Mines` text box.
	 * 
	 * @return int32 the amount of mines.
	 */
	int32 GetMines();

	/**
	 * @brief Updates the UI according to the current state of the game.
	 */
	void RefreshGame();

	/**
	 * @brief Sets the `StatusText` Text property.
	 * 
	 * @param Text The text to set in the UI.
	 */
	void SetStatusText(FText Text);
private:
	/**
	 * @brief Reference to the active window.
	 */
	TSharedPtr<class FMinesweeperWindow> MinesweeperWindow;

	/**
	 * @brief The grid that contains the buttons for the game.
	 */
	TSharedPtr<SUniformGridPanel> Grid;

	/**
	 * @brief Reference to the status text that displays the state of the game (game over, win, lose).
	 */
	TSharedPtr<STextBlock> StatusText;

	/**
	 * @brief Text box that contains the amount of rows for the game.
	 */
	TSharedPtr<SSpinBox<int32>> RowsBox;

	/**
	 * @brief Text box that contains the amount of columns for the game.
	 */
	TSharedPtr<SSpinBox<int32>> ColumnsBox;

	/**
	 * @brief Text box that contains the amount of mines for the game.
	 */
	TSharedPtr<SSpinBox<int32>> MinesBox;
};