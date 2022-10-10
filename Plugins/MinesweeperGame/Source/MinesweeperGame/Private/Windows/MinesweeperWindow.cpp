#include "Windows/MinesweeperWindow.h"
#include "Widgets/SMinesweeperWidget.h"

#define LOCTEXT_NAMESPACE "MinesweeperWindow"

FMinesweeperWindow::FMinesweeperWindow()
{
    SAssignNew(Widget, SMinesweeperWidget, MakeShareable(this));
}

FReply FMinesweeperWindow::OnNewGameClick()
{
    int32 Size = Widget->GetRows() * Widget->GetColumns();
    if (Widget->GetMines() >= Size)
    {
        // Having this condition be true creates an infinite loop because there is nowhere to put all the mines.
        Widget->SetStatusText(LOCTEXT("ErrorWrongAmountOfMines", "ERROR: make sure that the amount of mines is lower than Rows * Columns."));
    }
    else if (Widget->GetRows() <= 0 || Widget->GetColumns() <= 0 || Widget->GetMines() <= 0)
    {
        // This case shouldn't happen as the input is being constrainted to a specific range, but just in case there's a way to bypass that range.
        Widget->SetStatusText(LOCTEXT("ErrorNegativeValues", "ERROR: make sure the amount of rows, columns and mines are higher than 0"));
    }
    else
    {
        Board.Setup(Widget->GetRows(), Widget->GetColumns(), Widget->GetMines());
        Widget->RefreshGame();
    }
	return FReply::Handled();
}

FReply FMinesweeperWindow::OnCellClick(FCellData CellData)
{
    if (!Board.IsGameOver())
    {
        Board.TestCell(CellData.CellRow, CellData.CellColumn);
        Widget->RefreshGame();
    }
	return FReply::Handled();
}

int32 FMinesweeperWindow::GetRows()
{
    return Board.GetAmountOfRows();
}

int32 FMinesweeperWindow::GetColumns()
{
    return Board.GetAmountOfColumns();
}

TSharedRef<class SMinesweeperWidget> FMinesweeperWindow::GetWidget()
{
    return Widget.ToSharedRef();
}

FCell* FMinesweeperWindow::GetCell(uint32 Row, uint32 Column)
{
    return Board.GetCell(Row, Column);
}

#undef LOCTEXT_NAMESPACE