# Derivation of Bernoulli's Equation from Newton's Law (Euler Equation)

This note derives Bernoulli's equation starting from **Newton's second law** applied to an **inviscid (non-viscous) fluid**. The derivation is standard in fluid mechanics and proceeds through **Euler's equation** and an integration along a **streamline**. A streamline is a curve in a flow field that is everywhere tangent to the instantaneous velocity vector.

---

## 1. Assumptions

To obtain the Bernoulli equation, we assume:

1. **Inviscid flow**: viscosity is negligible (no shear stresses, no dissipation).
2. **Steady flow**: flow properties do not change with time at a fixed point.
3. **Incompressible flow**: density $\rho$ is constant.

The result is guaranteed along a streamline (and everywhere if the flow is also irrotational, i.e. $\nabla \times \mathbf{u}=0$).

---

## 2. Newton's Second Law for a Fluid Particle

Newton's second law states:

$$
\boxed{
\text{(mass)} \times \text{(acceleration)} = \text{sum of forces}
}
$$

For a fluid particle (an infinitesimal moving fluid element), we write the force balance per unit volume in the flow. In inviscid flow, the forces are:
- **Pressure forces** (surface force)
- **Gravity** (body force)

---

## 3. Euler's Equation Along a Streamline

A fluid particle moves along a streamline. Let $s(t)$ be the distance traveled along the streamline at time $t$ (i.e. $s$ is a position coordinate along the streamline) and let the flow speed along the streamline be $v(s)$.

### 3.1 Acceleration along the streamline

By definition, the speed along the streamline is the rate of change of the position coordinate:
$$
v = \frac{ds}{dt}
$$
Tangential acceleration is the time rate of change of speed:
$$
a_s = \frac{dv}{dt}
$$
Along the streamline, the speed can be viewed as a function of position along the streamline $v=v(s)$ with $s=s(t)$. By the chain rule:
$$
\boxed{
a_s = \frac{dv}{dt} = \frac{dv}{ds} \frac{ds}{dt} = v \frac{dv}{ds} = \frac{1}{2} \frac{d v^2}{ds}
}
$$
$dv/ds$ tells you how quickly speed changes as you move along the streamline. $v$ tells you how quickly you move along the streamline. $v dv/ds$ gives how quickly speed changes in time.

### 3.2 Forces along the streamline

#### Pressure force

Consider a tiny fluid slice of cross section $A$, length along streamline $ds$, volume $A ds$. The pressure at the upstream face is $p$, at the downstream face $p+dp$. Pressure acts inward normal to surfaces:
- Upstream face, force pushing forward: $F_{p,1} = p A$
- Downstream face, force pushing backward: $F_{p,2} = (p+dp) A$

The net pressure force is
$$
F_{p} = pA - (p+dp)A = -A dp
$$
Dividing by the volume $dV=Ads$ we have the pressure force per unit volume along $s$:
$$
\boxed{
\frac{F_p}{dV}
=
\frac{-A\,dp}{A\,ds}
=
-\frac{dp}{ds}
}
$$

#### Gravity force

Consider a small fluid element of mass $\rho dV$. The total gravity force is
$$
\mathbf{F}_g = \rho dV \mathbf{g}
$$
with $\mathbf{g} = - g \hat{\mathbf{z}}$. Let $\hat{\mathbf t}$ be the unit tangent to the streamline. $\hat{\mathbf z}\cdot\hat{\mathbf t}$ is the vertical component of the tangent vector, it means how fast the elevation changes as you move along the streamline. Therefore
$$
\hat{\mathbf z}\cdot\hat{\mathbf t} = \frac{dz}{ds}
$$
Hence, we have
$$
\mathbf{F}_g \cdot \hat{\mathbf t} = \rho dV \mathbf{g} \cdot\hat{\mathbf t} = - \rho dV g \hat{\mathbf{z}} \cdot\hat{\mathbf t} = - \rho dV g \frac{dz}{ds}
$$
and therefore the gravity force per unit volume along $s$ is
$$
\boxed{
\frac{\mathbf{F}_g \cdot \hat{\mathbf t}}{ dV} = -\rho g \frac{dz}{ds}
}
$$

### 3.3 Newton's law per unit volume

$$
\rho a_s = \text{sum of forces per unit volume}
$$

Substitute:

$$
\rho \frac{1}{2} \frac{dv^2}{ds} = -\frac{dp}{ds} - \rho g\frac{dz}{ds}
$$

Rearrange:

$$
\frac{dp}{ds} + \rho g\frac{dz}{ds} + \rho \frac{1}{2} \frac{dv^2}{ds} = 0
$$

This is **Euler's equation along a streamline**.

---

## 4. Integration Along a Streamline

Since $\rho$ is constant (incompressible fluid) we can write
$$
\frac{d}{ds} \left( p \right) + \frac{d}{ds} \left( \rho g z \right) + \frac{d}{ds} \left( \rho \frac{v^2}{2}  \right) 
= \frac{d}{ds} \left( p + \rho g z + \rho \frac{v^2}{2}  \right)
= 0
$$
and therefore, by integrating along a streamline
$$
\boxed{
 p + \rho g z + \rho \frac{v^2}{2} = \text{constant along a streamline}
}
$$

This is the **Bernoulli equation for incompressible, steady, inviscid flow** in **energy per unit volume**  $[J/m^3]$.

The Bernoulli equation in energy per unit mass $[J/kg]$ reads
$$
\frac{p}{\rho} + \frac{v^2}{2} + gz = \text{constant}
$$
and the Bernoulli equation in energy per unit height $[m]$ reads
$$
\frac{p}{\rho g} + \frac{v^2}{2g} + z = \text{constant}
$$

## 7. Notes on Validity

### 7.1 Streamline
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

Bernoulli's equation comes from applying Newton's second law to an inviscid fluid particle (Euler's equation) and integrating the resulting force balance along a streamline, giving conservation of mechanical energy per unit volume (or per unit mass/height).