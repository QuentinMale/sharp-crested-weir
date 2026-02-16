# Derivation of Weir Unit Discharge Formula

Goal: derive the ideal sharp-crested weir relation

$$
q^\prime = \frac{2}{3}\sqrt{2g}\,h_0^{3/2}
$$

where:
- $q^\prime$ is discharge per unit width ($m^2/s$),
- $h_0$ is upstream head above the crest,
- $g$ is gravity.

---

## 1) Physical setup and assumptions

For an ideal derivation, assume:

1. Steady flow
2. Incompressible water
3. Negligible viscosity (no head loss)
4. Hydrostatic pressure in the upstream section
5. Upstream approach velocity is small: $V_0 \approx 0$
6. Pressure in the free jet over the crest is atmospheric

---

## 2) Velocity of a thin horizontal strip

Take a horizontal strip of thickness $dy$ located at elevation $y$ above the crest.

At the upstream reference section, Bernoulli gives total head approximately $h_0$.
At the strip crossing over the crest, pressure is atmospheric and elevation is $y$.

So Bernoulli reduces to:

$$
\frac{v(y)^2}{2g} + y = h_0
$$

hence:

$$
v(y) = \sqrt{2g\,(h_0 - y)}
$$

---

## 3) Differential discharge

Per unit width, area of the strip is $dA^\prime = dy$, so:

$$
dq^\prime = v(y)\,dy = \sqrt{2g\,(h_0-y)}\,dy
$$

Integrate from crest ($y=0$) to free surface ($y=h_0$):

$$
q^\prime = \int_0^{h_0}\sqrt{2g\,(h_0-y)}\,dy
$$

Factor out constants:

$$
q^\prime = \sqrt{2g}\int_0^{h_0}(h_0-y)^{1/2}\,dy
$$

Let $u = h_0-y$, so $du=-dy$:

$$
\int_0^{h_0}(h_0-y)^{1/2}\,dy
= \int_0^{h_0}u^{1/2}\,du
= \left[\frac{2}{3}u^{3/2}\right]_0^{h_0}
= \frac{2}{3}h_0^{3/2}
$$

Therefore:

$$
\boxed{
q^\prime = \frac{2}{3}\sqrt{2g}\,h_0^{3/2}
}
$$

---

## 4) If the weir has width $b$

Total ideal discharge is:

$$
Q_{\text{ideal}} = b\,q^\prime
= \frac{2}{3}\,b\,\sqrt{2g}\,h_0^{3/2}
$$

In practice, use a discharge coefficient $C_d$:

$$
Q = C_d\,Q_{\text{ideal}}
= C_d\,\frac{2}{3}\,b\,\sqrt{2g}\,h_0^{3/2}
$$
