from __future__ import annotations

import csv
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def load_data(csv_path: Path) -> tuple[list[float], list[float]]:
    h_over_p: list[float] = []
    c_d: list[float] = []

    with csv_path.open(newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            h_over_p.append(float(row["h_over_P"]))
            c_d.append(float(row["C_d"]))

    return h_over_p, c_d


def main() -> None:
    here = Path(__file__).resolve().parent
    csv_path = here / "data.csv"
    output_path = here / "cd_vs_h_over_p.svg"

    h_over_p, c_d = load_data(csv_path)

    x_line = sorted(h_over_p)
    y_line = [0.611 + 0.075 * x for x in x_line]

    plt.figure(figsize=(4, 4/1.618))
    plt.scatter(h_over_p, c_d, label="Exp.", color="black", marker="x")
    plt.plot(x_line, y_line, label=r"$0.611 + 0.075(h/p)$", color="black", linewidth=2)
    plt.xlabel(r"$h/p$")
    plt.ylabel(r"$C_d$")
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_path, format="svg", bbox_inches="tight")
    plt.close()


if __name__ == "__main__":
    main()
