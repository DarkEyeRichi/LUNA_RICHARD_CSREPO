# Milestone 4 — Realistic Store Simulator

Final development and verification date: November 20, 2026.

## Application changes

The starting checkout contained a Product constructor and display method, empty Store and Transaction classes, and a Hello World entry point. The final local implementation connects all three classes through a persistent console menu.

- Added six starting groceries and $500 initial cash. Inventory shows IDs, wholesale costs, shelf prices, quantities, and low/out-of-stock warnings.
- Added stock purchasing. Successful purchases deduct the wholesale total and increase stock. Unknown IDs, insufficient cash, and quantities exceeding the 10,000-unit product capacity are rejected before changes.
- Added manual sales. Stock decreases and cash increases at the current shelf price. Sales cannot exceed available stock.
- Added repricing and discounts from $0.01 to $10,000.00. Discounts below current wholesale cost produce an explanation.
- Added employee hiring, payroll, firing with severance, and a ten-employee limit. Security installation prevents daily theft and adds a daily operating cost.
- Added daily simulation. Customer demand responds to shelf price and employee count, available stock limits sales, expenses are recorded, and a wholesale-price event changes one product's cost. Opening requires enough cash to cover expenses.
- Added finances and a transaction ledger covering stock, sales, pricing, staffing, security, rent, and market/theft events.
- Added versioned save/load for the complete store state. A restarted process restores the cash, quantities, both prices, day, staffing, security, and history.

## Refactoring and correctness

- Store owns vectors of Product and Transaction objects. Product lookup uses a pointer to an existing object, and display loops pass objects by const reference.
- Product retains its original dollar-based constructor. Monetary fields and calculations use integer cents to keep account balances exact.
- Input is read as complete lines through one numeric-input function. Blank input, extra characters, overflow, non-finite prices, and values outside allowed ranges are rejected.
- There is one main function in StoreSim.cpp. The separate main.cpp is empty.
- Load parses a separate candidate Store and validates it before replacing the active store. It checks format version, record counts, catalog identity, price/quantity ranges, chronological transaction days, printable descriptions, and cash reconciliation.
- Damaged, truncated, missing, unsupported, and oversized saves produce clear feedback. Failed loads preserve the current game.
- Save writes and closes a temporary file before atomically replacing the previous save on Windows. Failed replacement preserves the existing target.
- Added a stable Visual Studio working directory. Saves and temporary save files are ignored by Git.

## Usability improvements

- Every main-menu action is numbered, and the cash balance and current day remain visible.
- Inventory is displayed before trading or repricing, so product IDs and available quantities are visible when needed.
- Trade failures explain the purchase cost, available cash, available stock, or capacity limit.
- Product, quantity, price, and day-opening prompts offer cancellation. Leaving a changed store offers Save, Discard, or Back.
- Help lists the gameplay objective, costs, demand behavior, and persistence controls.
- The absolute save location is printed at startup.

## Verification performed

Builds used Visual Studio 2026 MSBuild, C++20, warning level 4, and warnings treated as errors.

| Configuration | Build | Integration checks |
|---|---|---|
| Debug x64 | Passed | 27 passed |
| Release x64 | Passed | 27 passed |
| Debug Win32 | Passed | 27 passed |
| Release Win32 | Passed | 27 passed |

The checks in `dev/StoreSim/verify_store_sim.py` launch the real console executable with isolated temporary save folders. They exercise financial arithmetic, restocking, overselling, repricing, staffing/severance/security, daily expenses, menu validation, cancellation, missing/damaged/oversized saves, failed writes, and exit handling. Two round-trip scenarios compare the saved bytes after loading in a separate process and saving again.

The verification uses temporary files and leaves the player's save outside the test folders unchanged.

## Local development commits

1. Implement grocery inventory, stock purchases, sales and transaction history.
2. Add employee management, security and daily grocery simulation.
3. Add validated save and load with console regression checks.
4. Document final gameplay, verification and milestone readiness.

These changes were made in this final development session. Their actual commit dates are retained. They do not establish that development commits were spread throughout the preceding week.

## Remaining submission work

- Capture genuine screenshots in `images/` showing successful compilation, the running menu/inventory, trading/staffing, and restored save data. Suggested names are `milestone4-build-success.png`, `milestone4-running-inventory.png`, `milestone4-trading-staff.png`, and `milestone4-save-load.png`.
- Copy the author's completed Final Project Stand-Up into README.md.
- Review any additional instructor feedback supplied outside the repository. The existing repository Issues and comments were reviewed and contain no instructor-authored bug reports.
- Verify Issues #7, #8, and #9 move from In Progress to Done when the final Pull Request is merged.
- Finish the evidence and reflection for Pull Request #10, connect it to the board, mark it ready, merge it, and verify main contains the completed project.
- Capture the completed Project board with its Issues and final Pull Request.
- Submit the public repository link and Project board screenshot to Full Sail.

GitHub authentication recovered on retry. The development commits are pushed to dev. The three development Issues below have been created and assigned to DarkEyeRichi, and [Pull Request #10](https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO/pull/10) is open as a draft from dev into main. Its diff is mergeable and passes the local checks. The draft links all three Issues for automatic closure when merged. The Project board was inspected and all three Issues are linked in In Progress through its existing automation.

The signed-in Full Sail Milestone 4 page is accessible. Its final reflection is a Discord Week 4 reply that still needs to be copied from the author's existing post. Windows screenshot capture currently times out and mouse clicks report missing geometry. The GitHub credential can access repository features but does not have the Projects scope, so adding the Pull Request to the board requires working browser controls or the author adding it manually.

After the author's explicit approval, the repository was changed to Public and anonymous GitHub API access returned HTTP 200. The repository history was scanned for common GitHub-token, AWS-key, and private-key patterns with zero matches. Screenshots, the final reflection, linking the Pull Request to the board, the final merge, and Full Sail submission remain pending.

### Final development Issues

| Issue | Acceptance criteria already verified locally |
|---|---|
| [#7 Complete grocery trading and store operations](https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO/issues/7) | Restock/sell update cash and stock together, price changes work, and staffing/security/daily simulation record their costs |
| [#8 Add durable store save and load](https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO/issues/8) | State survives restart, invalid files preserve the active game, and failed writes report an error |
| [#9 Validate console navigation and final regressions](https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO/issues/9) | All 27 integration checks pass in each of the four build configurations |

Future ideas, such as new grocery categories or richer customer behavior, can remain in Backlog.

Repository: [LUNA_RICHARD_CSREPO](https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO)

Project board: [Store project board](https://github.com/users/DarkEyeRichi/projects/4/views/1)
