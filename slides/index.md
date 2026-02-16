---
marp: true
title: Sharp-Crested Weir
paginate: true
theme: default
math: mathjax
style: |
  section {
    font-size: 28px;
  }
---

# Models and Approximate Solutions for Open-Channel Flows: Application to a Free Sharp-crested Weir

https://github.com/QuentinMale/sharp-crested-weir

Slide deck available at https://quentinmale.github.io/sharp-crested-weir

---

## Rectangular sharp-crested weir

![bg right:44% w:520px](./figures/Rectangular-weir-picture.jpg)

Application: Irrigation canals & water distribution
- No moving parts
- Converts an easy measurement (water level) into flow rate


---

## Question to answer today

Given a certain water level, what is the water flow rate?

---

## Bernoulli principle (energy budget)

- Inviscid (no friction)
- Steady state
- Incompressible
- Along a streamline

$$
\boxed{
\underbrace{p/\rho}_{\text{pressure work}}
+ \underbrace{{v^2}/{2}}_{\text{kinetic energy}}
+ \underbrace{g z}_{\text{potential energy}}
= \text{constant}
}
$$

---

## Weir-discharge equation

![bg right:50% w:500px](./figures/sharp_crested_weir.svg)

- Contraction is neglected
- $V_0 \approx 0$

$$
\boxed{
q^\prime = 2/3 \sqrt{2g} \,h_0^{3/2}
}
$$

---

## Corrected weir equation

$$
\boxed{
q = \underbrace{C_d}_\text{discharge coefficient} \, 2/3 \sqrt{2g} \, h_0^{3/2}
}
$$

Interpretation: $C_d = q / q^\prime$ (real/ideal) is a correction factor.
Incorporate: viscous friction losses, upstream velocity head, and contraction.

---

## How is $C_d$ determined? (1)

1. Measure head $h_0$

2. Measure discharge $q$

3. Compute $C_d$ from the definition
$$
C_d
= \frac{q}{\frac{2}{3}\sqrt{2g}\,h^{3/2}}
$$

4. Repeat for many heads and/or geometries
You now have a set of points and can fit a curve.

---

## Dimensional analysis (Buckingham $\Pi$ theorem)

$$
\Pi_1=q/\sqrt{gh^3} \text{ , } \Pi_2 = h/p \text{ , } \Pi_3 = \rho \sqrt{gh^3} / \mu \text{ , } \Pi_4 = \rho g h^2 / \sigma
$$

At sufficiently large Reynolds number and Weber number:
- $Re_h \gg 1$  $\Rightarrow$ viscous effects are confined to thin boundary layers  
- $We_h \gg 1$  $\Rightarrow$ surface tension effects are negligible

$$
\boxed{
C_d = \phi \!\left(\frac{h}{p}\right)
}
$$

---

## Discharge coefficient

![w:500px](./figures/cd_vs_h_over_p.svg)

Linear fit (Kandaswamy & Rouse, 1957): $C_d = 0.611 + 0.075 h/p$

---

## Summary (what to remember)

- The ideal derivation gives the scaling: $q^\prime \propto h^{3/2}$.
- Real flows deviate because of **losses + contraction + approach effects**.
- $C_d$ is determined by **calibration**:
  measure $Q$, measure $h$, compute $C_d = q/q^\prime$.
- Over practical ranges (high enough $Re_h$), the dominant dependence collapses to
  $C_d = C_d(h/p)$.

---

## Exercise

Build a program with two steps:

1. Fit a linear discharge coefficient law given experimental data points.
   $$
   C_d = a+b(h/p)
   $$


2. Given $h$ and $b$, find the crest height $p$ to achieve a certain flow rate.
