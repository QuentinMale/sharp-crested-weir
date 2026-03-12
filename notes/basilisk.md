# Basilisk model

## Governing equations (two-phase incompressible flow)

$$
\frac{\partial (\rho\mathbf{u})}{\partial t} + \nabla\cdot(\rho\mathbf{u}\otimes\mathbf{u})
= -\nabla p + \nabla\cdot\left[\mu\left(\nabla\mathbf{u}+\nabla\mathbf{u}^T\right)\right]
+ \rho\mathbf{g} + \mathbf{f}_{\sigma}
$$

$$
\nabla \cdot \mathbf{u} = 0
$$

$$
\frac{\partial f}{\partial t} + \mathbf{u}\cdot\nabla f = 0
$$
where:
- $f\in[0,1]$ is the VOF phase fraction (liquid volume fraction).
- Both phases are individually incompressible (constant $\rho_1,\rho_2$); density changes in space/time only through advection of $f$.
- Material properties are phase-weighted:
  $$
  \begin{aligned}
  \rho(f) = f\,\rho_1 + (1-f)\,\rho_2  \\
  \mu(f) = f\,\mu_1 + (1-f)\,\mu_2
  \end{aligned}
  $$
- Surface tension $\mathbf f_\sigma = \sigma\,\kappa\,\nabla f$

## Numerics

- Spatial discretization: finite-volume on a quadtree adaptive Cartesian grid.
- Velocity-pressure coupling: centered projection method enforcing $\nabla\cdot\mathbf{u}=0$.
- Two-phase interface: geometric VOF advection.
