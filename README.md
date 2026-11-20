# LUNA_RICHARD_CSREPO

A C++20 console game about running a grocery store. Begin with $500 and six products, then manage stock, shelf prices, employees, security, and daily customer sales. The cash milestone is $1,000, and the store can keep trading after reaching it.

## Build and run

1. Open `dev/StoreSim/StoreSim.slnx` in Visual Studio 2026 with the **Desktop development with C++** workload and Windows SDK installed.
2. Select **StoreSim** as the startup project, **Debug**, and **x64**.
3. Choose **Build → Build Solution**, then **Debug → Start Without Debugging**.

The project uses C++20 and toolset v145. Debug and Release also support Win32. Build outputs and Visual Studio caches are ignored by Git.

## Play

| Option | Action |
|---|---|
| 1 | View inventory, wholesale costs, shelf prices, and low-stock notices |
| 2 | Purchase stock using the store's cash |
| 3 | Sell products manually at the shelf price |
| 4 | Change a shelf price or discount an item |
| 5 | View transaction history |
| 6 | View cash flow, stock value, and upcoming daily expenses |
| 7 | Hire/fire employees or install security |
| 8 | Open for one day of customer sales and expenses |
| 9 | Save the store |
| 10 | Load a saved store |
| 11 | Read help and gameplay costs |
| 0 | Exit, with a save/discard/back choice after changes |

Prices are entered in dollars and rounded to cents. Enter 0 at product, quantity, or price prompts to cancel.

Each simulated day costs $10 rent. Employees cost $25 to hire, $5 per day, and $15 severance to fire. They increase customer demand. Security costs $75 to install and $3 per day, and prevents theft. One product's wholesale price changes each day. Review costs, stock, and shelf prices before opening again.

## Save and load

`store_save.txt` is stored in the working directory. Its absolute location is displayed when the game starts. Visual Studio is configured to use the project directory.

Saving includes cash, day, staffing, security, product quantities, wholesale and selling prices, and transaction history. Choose Load after restarting to continue. Loading validates the entire file before replacing the active store. Saving writes a temporary file before replacing the previous save. Normal exit offers to save. Ending input with Ctrl+Z exits and reports unsaved changes.

The save format is versioned text with integer cents. It supports up to 100,000 transactions. Daily simulation runs through day 3,650, after which manual trading, history, and persistence remain available. Future random outcomes are generated when a day is opened.

## Code organization

- `Product.h/.cpp` stores and displays grocery information.
- `Store.h/.cpp` manages the product and transaction vectors, store rules, daily simulation, and persistence.
- `Transaction.h/.cpp` records the day, action, and cash change.
- `StoreSim.cpp` contains the application's single entry point, menus, and numeric-input validation.
- `main.cpp` remains an empty project file and defines no additional entry point.

Product lookup returns a pointer to an existing inventory object. Display and iteration use references. Standard containers own the objects' memory.

## Verification

From the repository root, after building Debug x64, run the optional integration checks with Python 3.

```text
python dev/StoreSim/verify_store_sim.py
```

The application itself uses the C++ standard library and Windows file replacement API. Python is used by the verification script.

The 27 checks cover trading, financial calculations, pricing, staff limits, daily simulation, save/load across process restarts, malformed saves, failed writes, menu input, cancellation, and exit behavior. All checks passed against Debug and Release for both x64 and Win32 on November 20, 2026. See [Milestone 4](docs/Milestone4.md) for the final development record and remaining submission steps.

## Final Project Stand-Up

The completed Final Project Stand-Up still needs to be copied here from the course activity. This section awaits the author's existing reflection about accomplishments, improvements, challenges, the biggest takeaway, and future ideas.

## Earlier development notes

GROCERY STORE SIMULATOR
This will be what my store simulator game will be about. Its going to be like managing a grocery store with buying items, them going out of stock, special items, surging items and more. The use will need to restock items, discount items not selling, and increase prices of those selling too much. This project will be called Realistic Store Simulator.
Three core features will be
BUYING STOCK - This will be you having to buy stock for surging prices and those going out of stock too quickly. Wholesale prices may rise or fall due to random occurances
CHANGING PRICES/DISCOUNTS - This is for the player to change prices and give discounts so items that have too many in stock can sell.
EMPLOYEES SYSTEM - This will be firing employees when you have too many but you may lose money with severance. Then hiring more employees. Buying security for stealing.

Product.h/cpp - This is where the products will be stored and where they can buy more if possible. It will be a long list to ensure a fun experience.
Store.h/cpp - This is going to be the storefront so you can see whats in stock, whats selling hot, on discounts, and more.
Transaction.h/cpp - This is what will show you if you can buy items, buy new stock, buy employees, and fire employees.

Current Focus: Creating a foundation for my game with having all the files and some code setup.


UPDATE: I currently have made all the files and began my projects idea which will be a store simulator. I am currently adding code to the project but everything else has been completed like the git repo and reflection items. Hoping not to run into any errors but I want a solid starting foundation of running code for the milestone.
