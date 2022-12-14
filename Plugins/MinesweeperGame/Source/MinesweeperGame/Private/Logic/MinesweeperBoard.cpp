#include "Logic/MinesweeperBoard.h"

void FMinesweeperBoard::GetNearbyCells(TSet<FCell*>& Cells, uint32 Row, uint32 Column)
{
    // Adjacent cells.
    FCell* Cell = GetCell(Row - 1, Column);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row + 1, Column);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row, Column - 1);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row, Column + 1);
    if (Cell != nullptr) Cells.Add(Cell);

    // Diagonal cells.
    Cell = GetCell(Row - 1, Column - 1);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row - 1, Column + 1);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row + 1, Column - 1);
    if (Cell != nullptr) Cells.Add(Cell);

    Cell = GetCell(Row + 1, Column + 1);
    if (Cell != nullptr) Cells.Add(Cell);
}

void FMinesweeperBoard::Expand(uint32 Row, uint32 Column)
{
    TSet<FCell*> CellsToUpdate;

    // Initial cell to update.
    FCell* Cell = GetCell(Row, Column);

    CellsToUpdate.Add(Cell);

    while (CellsToUpdate.Num() > 0)
    {
        auto CurrentCellIt = CellsToUpdate.begin();
        FCell* CurrentCell = *CurrentCellIt;

		SetCellTested(CurrentCell);

		TSet<FCell*> NearbyCells;
        GetNearbyCells(NearbyCells, CurrentCell->Row, CurrentCell->Column);

        for (auto& NearbyCell : NearbyCells)
        {
			// Nearby cells are added if the following conditions are met:
			// - the nearby cell has 0 nearby mines
			// - the current cell has 0 nearby mines and the nearby cell has 0 or more nearby mines
            if (!NearbyCell->bIsTested)
            {
                if (NearbyCell->NearbyMines == 0)
                {
                    CellsToUpdate.Add(NearbyCell);
                }
                else if (CurrentCell->NearbyMines == 0 && NearbyCell->NearbyMines > 0)
                {
                    CellsToUpdate.Add(NearbyCell);
                }
            }
        }

        CellsToUpdate.Remove(CurrentCell);
    }
}

bool FMinesweeperBoard::PlaceMine(uint32 Row, uint32 Column)
{
    auto Cell = GetCell(Row, Column);
    if (Cell->bIsTested || Cell->CellType == ECellType::Mine) return false;
    Cell->CellType = ECellType::Mine;
    Cell->NearbyMines = -1;
	return true;
}

bool FMinesweeperBoard::SetCellTested(FCell* Cell)
{
    if (Cell->bIsTested) return false;
	Cell->bIsTested = true;

    if (Cell->CellType == ECellType::Mine)
    {
        bGameOver = true;
        Cell->bExploded = true;
        return true;
    }

    TestedCells++;

    if (TestedCells >= AmountOfRows * AmountOfColumns - AmountOfMines)
    {
        bGameOver = true;
        bPlayerWon = true;
    }
    return false;
}

FCell* FMinesweeperBoard::GetCell(uint32 Row, uint32 Column)
{
    if (Row < 0 || Column < 0 || Row >= AmountOfRows || Column >= AmountOfColumns) return nullptr;
    auto Cell = &Board[Row * AmountOfColumns + Column];
    return Cell;
}

void FMinesweeperBoard::Setup(uint32 Rows, uint32 Columns, uint32 Mines)
{
    AmountOfRows = Rows;
    AmountOfColumns = Columns;

    // Clamp amount of mines to be less than rows * columns.
    AmountOfMines = FMath::Clamp<uint32>(Mines, 1, (Rows * Columns) - 1);
    TestedCells = 0;

    // Reset flags.
    bStarted = false;
    bGameOver = false;
    bPlayerWon = false;

    Board.Init(FCell(), Rows * Columns);
}

void FMinesweeperBoard::PlaceMines()
{
    for (uint32 i = 0; i < AmountOfMines; i++)
    {
        uint32 Row = FMath::RandRange(0, AmountOfRows - 1);
        uint32 Column = FMath::RandRange(0, AmountOfColumns - 1);
        while (!PlaceMine(Row, Column))
        {
            Row = FMath::RandRange(0, AmountOfRows - 1);
            Column = FMath::RandRange(0, AmountOfColumns - 1);
        }
    }

	for (int32 i = 0; i < Board.Num(); i++)
	{
        uint32 Row = i / AmountOfColumns;
        uint32 Column = i % AmountOfColumns;

		FCell* Cell = &Board[i];
		Cell->Row = Row;
		Cell->Column = Column;

        if (Cell->CellType == ECellType::Empty)
        {
            TSet<FCell*> NearbyCells;
            GetNearbyCells(NearbyCells, Row, Column);
            uint32 MineCount = 0;
            for (auto& NearbyCell : NearbyCells)
            {
                if (NearbyCell->CellType == ECellType::Mine)
                    MineCount++;
            }
            Cell->NearbyMines = MineCount;
        }
	}
}

bool FMinesweeperBoard::TestCell(uint32 Row, uint32 Column)
{
    auto Cell = GetCell(Row, Column);

    // Test the cell, we return true immediately if a mine is found in this cell.
    if (SetCellTested(Cell)) return true;

    if (!bStarted)
    {
        PlaceMines();
        bStarted = true;
    }

    // Expand all nearby cells automatically.
    Expand(Row, Column);
    return false;
}
