#!/usr/bin/env python3
from pathlib import Path
import argparse
import csv
import math

import matplotlib.pyplot as plt


def read_data(csv_path: Path):
    h_values = []
    q_values = []

    with csv_path.open(newline="", encoding="utf-8") as file:
        reader = csv.DictReader(file)
        for row in reader:
            h_values.append(float(row["H_cm"]))
            q_values.append(float(row["q_exp_Lps"]))

    return h_values, q_values


def main():
    parser = argparse.ArgumentParser(
        description="Plot q_exp_Lps as a function of H_cm from a CSV file."
    )
    parser.add_argument(
        "--csv",
        type=Path,
        default=Path(__file__).with_name("data.csv"),
        help="Path to the CSV file (default: data.csv in this folder).",
    )
    args = parser.parse_args()

    h_cm, q_exp_lps = read_data(args.csv)
    h_m = [x / 100.0 for x in h_cm]
    q_exp_m3s = [q / 1000.0 for q in q_exp_lps]
    q_theory_m3s = [(2.0 / 3.0) * math.sqrt(2.0 * 9.81) * (x ** 1.5) for x in h_m]

    plt.figure(figsize=(4, 4/1.618))
    plt.plot(
        h_m,
        q_exp_m3s,
        marker="s",
        markerfacecolor="none",
        linestyle="None",
        color="k",
        label=r"Exp. ($p=0.01$ m)",
    )
    plt.plot(
        h_m,
        q_theory_m3s,
        linestyle="--",
        color="k",
        label=r"$\frac{2}{3}\sqrt{2g}\,h_0^{3/2}$",
    )
    plt.xlabel(r"$h_0 \times 10^2$ [m]")
    plt.ylabel(r"Flow rate [m$^3$/s]")
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(
        Path(__file__).with_name("q_exp_vs_H.svg"),
        format="svg",
        bbox_inches="tight",
    )
    plt.show()


if __name__ == "__main__":
    main()
