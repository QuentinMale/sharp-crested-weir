# Derivation of Bernoulli's Equation from Newton's Law (Euler Equation)

This note derives Bernoulli's equation starting from **Newton's second law** applied to an **inviscid (non-viscous) fluid**. The derivation is standard in fluid mechanics and proceeds through **Euler's equation** and an integration along a **streamline**.

---

## 1. Assumptions

To obtain the classical Bernoulli equation, we assume:

1. **Inviscid flow**: viscosity is negligible (no shear stresses, no dissipation).
2. **Steady flow**: flow properties do not change with time at a fixed point.
3. **Incompressible flow**: density $\rho$ is constant.
4. **Along a streamline**: the result is guaranteed along a streamline (and everywhere if the flow is also irrotational).

---

## 2. Newton's Second Law for a Fluid Particle

Newton's second law states:

$$
\text{(mass)} \times \text{(acceleration)} = \text{sum of forces}
$$

For a **fluid particle** (an infinitesimal moving fluid element), we write the force balance per unit volume in the flow.

In inviscid flow, the main body and surface forces are:

- **Pressure forces** (surface force)
- **Gravity** (body force)

---

## 3. Euler's Equation Along a Streamline

Let $s$ be the coordinate along a streamline, and let the flow speed along the streamline be $v(s)$.

### 3.1 Acceleration along the streamline

In steady flow, the acceleration of a particle comes from spatial changes in velocity (convective acceleration). Using the chain rule:

$$
a_s = \frac{Dv}{Dt} = \frac{dv}{ds}\frac{ds}{dt}
$$

But $\frac{ds}{dt} = v$, so:

$$
a_s = v\frac{dv}{ds}
$$

### 3.2 Forces along the streamline

- Pressure force per unit volume along $s$: $-\frac{dp}{ds}$
- Gravity component along $s$: $-\rho g \frac{dz}{ds}$

(Here $z$ is elevation, and $g$ is gravitational acceleration.)

### 3.3 Newton's law per unit volume

$$
\rho a_s = \text{sum of forces per unit volume}
$$

Substitute:

$$
\rho v\frac{dv}{ds} = -\frac{dp}{ds} - \rho g\frac{dz}{ds}
$$

Rearrange:

$$
\frac{dp}{ds} + \rho g\frac{dz}{ds} + \rho v\frac{dv}{ds} = 0
$$

This is **Euler's equation along a streamline**.

---

## 4. Convert to Differential Form

Multiply through by $ds$:

$$
dp + \rho g\,dz + \rho v\,dv = 0
$$

Divide by $\rho$ (constant for incompressible flow):

$$
\frac{dp}{\rho} + g\,dz + v\,dv = 0
$$

Recognize:

- $v\,dv = d\left(\frac{v^2}{2}\right)$

So:

$$
\frac{dp}{\rho} + g\,dz + d\left(\frac{v^2}{2}\right) = 0
$$

---

## 5. Integrate Along a Streamline

Integrate between two points (1 and 2) along the streamline:

$$
\int_1^2 \frac{dp}{\rho} + \int_1^2 g\,dz + \int_1^2 d\left(\frac{v^2}{2}\right) = 0
$$

For constant $\rho$ and constant $g$:

$$
\frac{p_2 - p_1}{\rho} + g(z_2 - z_1) + \left(\frac{v_2^2}{2} - \frac{v_1^2}{2}\right) = 0
$$

Rearrange:

$$
\boxed{\frac{p}{\rho} + \frac{v^2}{2} + gz = \text{constant along a streamline}}
$$

This is **Bernoulli's equation** in **energy per unit mass** units $[J/kg]$.

---

## 6. "Head" Form (Energy per Unit Weight)

Divide by $g$:

$$
\boxed{\frac{p}{\rho g} + \frac{v^2}{2g} + z = \text{constant}}
$$

Each term now has units of **meters** and is interpreted as a **head**:
- $p/(\rho g)$: pressure head
- $v^2/(2g)$: velocity head
- $z$: elevation head

---

## 7. Notes on Validity

### 7.1 Streamline vs everywhere
- For steady, inviscid flow: Bernoulli is constant **along a streamline**.
- If the flow is also **irrotational** ($\nabla\times\mathbf{u}=0$), then the constant is the same **throughout the flow field**.

### 7.2 Real flows (losses)
Viscosity and turbulence dissipate energy. A practical engineering form adds head loss $h_L$:

$$
\frac{p_1}{\rho g} + \frac{v_1^2}{2g} + z_1
=
\frac{p_2}{\rho g} + \frac{v_2^2}{2g} + z_2 + h_L
$$

---

## 8. Summary (One Sentence)

Bernoulli's equation comes from applying Newton's second law to an inviscid fluid particle (Euler's equation) and integrating the resulting force balance along a streamline, giving conservation of mechanical energy per unit mass (or per unit weight).