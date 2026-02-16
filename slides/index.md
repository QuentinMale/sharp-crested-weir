---
marp: true
title: Sharp-Crested Weir
paginate: true
theme: default
math: mathjax
---

# Models and Approximate Solutions for Open-Channel Flows: Application to a Free Sharp-crested Weir



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
