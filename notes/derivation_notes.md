## Bernoulli's principle

Hypothesis: no viscous forces, steady flow, constant density

Newton's second law to a fluid particle moving along a streamline

$$
\rho \, a_s = \sum \text{forces per unit volume}
$$

Acceleration
$$
a_s = \frac{dv}{dt} = \frac{dv}{ds} \frac{ds}{dt} = v \frac{dv}{ds} = \frac{1}{2} \frac{d v^2}{ds}
$$
with $s(t)$ the position along the streamline and $v(s)$ the flow speed.

Pressure force
$$
F_{p} = pA - (p+dp)A = -A dp
$$
$$
\frac{F_p}{dV}
=
\frac{-A\,dp}{A\,ds}
=
-\frac{dp}{ds}
$$
"Pressure gradient acts like a driving force, fluids accelerate from high pressure to low pressure."

Gravity force
$$
\mathbf{F}_g = \rho dV \mathbf{g} = - \rho dV g \hat{\mathbf{z}}
$$
$$
\frac{\mathbf{F}_g \cdot \hat{\mathbf t}}{dV} = - \rho g \, \hat{\mathbf{z}} \cdot\hat{\mathbf t} = - \rho g \frac{dz}{ds}
$$
with $\hat{\mathbf{z}}$ the unit tangent to the streamline. $\hat{\mathbf z}\cdot\hat{\mathbf t}=cos(\theta)=dz/ds$ is the vertical component of the tangent vector: how fast the elevation changes as you move along the streamline.
"Gravity depends on slope: it accelerates the flow downhill and slows it uphill."

We therefore have
$$
\rho \frac{1}{2} \frac{d v^2}{ds} = -\frac{dp}{ds}  - \rho g \frac{dz}{ds} 
$$
$$
\frac{d}{ds} \left( \rho \frac{v^2}{2} + p + \rho g z \right) = 0
$$

By integrating along a streamline
$$
 \rho \frac{v^2}{2} + p + \rho g z  = \text{constant}
$$

## Flow rate

Bernoulli's equation in between an upstream section and a point located at an elevation $y$ above the crest
$$
 \rho \frac{v_0^2}{2} + p_\mathrm{atm} + \rho g h_0  = \rho \frac{v(y)^2}{2} + p_\mathrm{atm} + \rho g y
$$
$$
 \rho g h_0  = \rho \frac{v(y)^2}{2} + \rho g y
$$
$$
v(y) = \sqrt{2 g \left( h_0 - y \right)}
$$

By integrating the velocity from crest ($y=0$) to free surface ($y=h_0$), neglecting the contraction of the nappe
$$
q^\prime = \int_0^{h_0}\sqrt{2g\,(h_0-y)}\,dy = \frac{2}{3}\sqrt{2g}\,h_0^{3/2}
$$

## Pi theorem

* Variables that influence the problem: $Q, \, h, \, p, \, g, \, \rho, \, \mu, \, \sigma$ (7)

* Fundamental dimensions: [M], [L], [T] (3)

* Number of dimensionless groups = number of variables - number of fundamental dimensions = 4
