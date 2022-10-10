#pragma once

#include "CoreMinimal.h"
#include "Widgets/Views/STileView.h"
#include "Widgets/Layout/SUniformGridPanel.h" 
#include "Modules/ModuleManager.h"

#include "Windows/MinesweeperWindow.h"

class FToolBarBuilder;
class FMenuBuilder;

/**
 * @brief Module class for the Minesweeper game plugin.
 */
class FMinesweeperGameModule : public IModuleInterface, public TSharedFromThis<FMinesweeperGameModule>
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
private:
	TSharedPtr<class FUICommandList> PluginCommands;

	/**
	 * @brief Reference to the active Minesweeper game window.
	 */
	TSharedPtr<FMinesweeperWindow> MinesweeperWindow;
};
