#include "Widgets/SMinesweeperWidget.h"

#define LOCTEXT_NAMESPACE "MinesweeperWidget"

void SMinesweeperWidget::Construct(const FArguments& InArgs, const TSharedRef<FMinesweeperWindow>& Window)
{
    MinesweeperWindow = Window;
	FText NewGameText = LOCTEXT("NewGame", "New Game");
	this->ChildSlot
	[
        SNew(SVerticalBox)
        +SVerticalBox::Slot().VAlign(VAlign_Top).HAlign(HAlign_Center)
        .AutoHeight()
        [
            SNew(SHorizontalBox)

            // Rows input.
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                    .Text(LOCTEXT("Rows", "Rows: "))
            ]
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SAssignNew(RowsBox, SSpinBox<int32>)
                    .Value(5)
                    .MinValue(2)
                    .MaxValue(100)
            ]

            // Columns input.
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                    .Text(LOCTEXT("Columns", "Columns: "))
            ]
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SAssignNew(ColumnsBox, SSpinBox<int32>)
                    .Value(5)
                    .MinValue(2)
                    .MaxValue(100)
            ]

            // Mines input.
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                    .Text(LOCTEXT("Mines", "Mines: "))
            ]
            +SHorizontalBox::Slot().HAlign(HAlign_Center)
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SAssignNew(MinesBox, SSpinBox<int32>)
                    .Value(5)
                    .MinValue(1)
                    .MaxValue(100)
            ]
        ]

        // New Game Button
        +SVerticalBox::Slot().VAlign(VAlign_Top)
        .AutoHeight()
        [
            SNew(SButton)
            .Text(NewGameText)
            .OnClicked(FOnClicked::CreateSP(MinesweeperWindow.ToSharedRef(), &FMinesweeperWindow::OnNewGameClick))
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
        ]

        // Status Text
        +SVerticalBox::Slot().VAlign(VAlign_Top)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        .AutoHeight()
        [
            SAssignNew(StatusText, STextBlock)
        ]

        // Game button grid
        +SVerticalBox::Slot().VAlign(VAlign_Top)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        .AutoHeight()
        [
            SAssignNew(Grid, SUniformGridPanel)
                .MinDesiredSlotHeight(48)
                .MinDesiredSlotWidth(32)
                .SlotPadding(5)
        ]
    ];
}

int32 SMinesweeperWidget::GetRows()
{
    return RowsBox->GetValue();
}

int32 SMinesweeperWidget::GetColumns()
{
    return ColumnsBox->GetValue();
}

int32 SMinesweeperWidget::GetMines()
{
    return MinesBox->GetValue();
}

void SMinesweeperWidget::RefreshGame()
{
	Grid->ClearChildren();

    // GameOver flag allows displaying the location of all mines.
    bool bGameOver = false;
    StatusText->SetText(LOCTEXT("Empty", ""));

    if (MinesweeperWindow->IsGameOver())
    {
        bGameOver = true;
        if (MinesweeperWindow->HasPlayerWon())
        {
            StatusText->SetText(LOCTEXT("PlayerWon", "You won!"));
        }
        else
        {
            StatusText->SetText(LOCTEXT("PlayerLose", "You lost!"));
        }
    }

    // Update UI buttons according to the status of the game.
	for (int32 i = 0; i < MinesweeperWindow->GetRows(); i++)
	{
		for (int32 j = 0; j < MinesweeperWindow->GetColumns(); j++)
		{
            FCell* Cell = MinesweeperWindow->GetCell(i, j);
            FCellData CellData(i, j);
            FText ButtonText;
            if (Cell->CellType != ECellType::Mine && Cell->bIsTested)
            {
                ButtonText = FText::AsNumber(Cell->NearbyMines);
            }
            else if (bGameOver && Cell->CellType == ECellType::Mine)
            {
                ButtonText = LOCTEXT("Mine", "X");
            }
            else
            {
                ButtonText = LOCTEXT("Space", " ");
            }
			Grid->AddSlot(i, j).AttachWidget(
				SNew(SButton)
					.Text(ButtonText)
                    .OnClicked(FOnClicked::CreateSP(MinesweeperWindow.ToSharedRef(), &FMinesweeperWindow::OnCellClick, CellData))
                    .HAlign(HAlign_Center)
                    .VAlign(VAlign_Center)
			);
		}
	}
}

void SMinesweeperWidget::SetStatusText(FText Text)
{
    StatusText->SetText(Text);
}

TSharedRef<SMinesweeperWidget> SMinesweeperWidget::New()
{
	return MakeShareable(new SMinesweeperWidget());
}

#undef LOCTEXT_NAMESPACE