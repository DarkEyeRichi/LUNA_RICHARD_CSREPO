"""Run console integration checks against a built StoreSim executable.

Uses only Python's standard library and isolated temporary save folders.
Usage: python dev/StoreSim/verify_store_sim.py [path/to/StoreSim.exe]
"""
import pathlib
import subprocess
import sys
import tempfile

executable = (pathlib.Path(sys.argv[1]) if len(sys.argv) > 1 else
              pathlib.Path(__file__).parent / "StoreSim/x64/Debug/StoreSim.exe").resolve()
passed = []

with tempfile.TemporaryDirectory(prefix="storesim-verify-") as directory:
    root = pathlib.Path(directory)
    save = root / "store_save.txt"

    def run(lines):
        result = subprocess.run(
            [str(executable)], input="\n".join(map(str, lines)) + "\n",
            text=True, capture_output=True, cwd=root, timeout=15)
        assert result.returncode == 0, result.stderr
        return result.stdout

    def check(name, condition):
        assert condition, name
        passed.append(name)
        print("PASS: " + name)

    output = run(["abc", "3abc", "-1", "99", "1", "2", "999", "1",
                  "2", "101", "1000", "3", "101", "9999", "0"])
    check("menu validation, unknown ID, insufficient cash and overselling",
          "Enter a number" in output and "Product ID not found" in output
          and "Purchase costs" in output and "available stock (10)" in output)

    output = run([2, 101, 3, 3, 101, 2, 4, 102, 1.99, 7, 1, 7, 3, 9, 0])
    check("restock, sale, price, staff, security and save",
          "Store saved successfully" in output and "Store cash: $400.98" in output)
    original = save.read_bytes()
    output = run([10, 1, 6, 7, 0, 9, 1, 0])
    check("all state survives restart and a second save",
          "Store loaded successfully" in output and "400.98" in output
          and "Employees: 1/10" in output and "Security: ACTIVE" in output
          and save.read_bytes() == original)

    output = run([10, 4, 102, 3.50, 10, 0, 1, 0, 2])
    check("cancelled load and discarded exit preserve saved data",
          "3.50" in output and save.read_bytes() == original)
    output = run([10, 7, 2, 0, 1])
    check("save-on-exit persists severance and staff",
          "Store saved successfully" in output and "38598 0 1" in save.read_text())

    output = run([10, 8, 1, 9, 1, 0])
    check("daily sales, rent, market event and security service",
          "Day 2" in output and "Wholesale update" in output
          and "Paid daily expenses of $13.00" in output)
    day_save = save.read_bytes()
    output = run([10, 9, 1, 0])
    check("simulated-day state round trip", save.read_bytes() == day_save)

    valid = save.read_text()
    corruptions = [
        "", "STORESIM 99\n", valid[:len(valid) // 2],
        valid.replace("STORESIM 1", "STORESIM 1\nBAD"),
        valid + "TRAILING", valid.replace('"Milk"', '"Other"'),
        valid.replace("\n6\n", "\n-6\n", 1),
        valid.replace("\n6\n", "\n999999999\n", 1),
        valid.replace('"Milk"', "Milk"),
        valid.replace("2 ", "-2 ", 1),
    ]
    for index, damaged in enumerate(corruptions):
        save.write_text(damaged)
        output = run([3, 101, 1, 10, 1, 6, 0, 2])
        check(f"damaged save {index + 1} preserves active cash",
              "damaged or unsupported" in output and "Store cash: $503.49" in output)

    save.unlink()
    output = run([10, 0])
    check("missing save handled", "No readable save file" in output)
    save.mkdir()
    output = run([2, 101, 1, 9, 1, 6, 0, 2])
    check("unwritable target preserves the current game",
          "Cannot replace the save file" in output and "Store cash: $498.00" in output)
    save.rmdir()

    output = run([3, 101, 10, 1, 4, 102, 0.001, 4, 102, 0, 5, 0, 2])
    check("empty stock, sub-cent rejection and price cancellation",
          "OUT OF STOCK" in output and "Enter a price between" in output)
    output = run([7, 2, 7, 3, 7, 3, 7, 1, 7, 2, 6, 0, 2])
    check("empty staff, repeat security purchase and severance safeguards",
          "There are no employees" in output and "Security is already installed" in output
          and "Store cash: $385.00" in output)
    output = run([2, 101, 250, 8, 1, 6, 0, 2])
    check("daily expenses cannot overdraw cash",
          "Reserve $10.00" in output and "Store cash: $0.00" in output)
    output = run([11])
    check("help and end-of-input exit",
          "HOW TO PLAY" in output and "Store closed" in output)

    output = run(["", "2.5", "999999999999999999999", "4", "101", "nan",
                  "inf", "-5", "10000.01", "2.995", "2", "0", "0", "0", "0", "2"])
    check("blank, overflow, non-finite, negative and fractional menu input",
          "Shelf price updated to $3.00" in output and "Store closed" in output)

    actions = [7, 1] * 11 + [7, 0, 6, 0, 0, 0, 2]
    output = run(actions)
    check("employee cap and returning from the exit prompt",
          "maximum of 10 employees" in output and "Employees: 10/10" in output
          and "Store cash: $250.00" in output)

    output = run([2, 101, 249, 7, 1, 7, 3, 6, 0, 2])
    check("hiring and security require sufficient funds",
          "Hiring requires $25.00" in output and "Installing security requires $75.00" in output
          and "Store cash: $2.00" in output)

    with save.open("wb") as oversized:
        oversized.truncate(17 * 1024 * 1024)
    output = run([3, 101, 1, 10, 1, 6, 0, 2])
    check("oversized save rejected before parsing",
          "Save file is too large" in output and "Store cash: $503.49" in output)

print(f"{len(passed)} integration checks passed")
