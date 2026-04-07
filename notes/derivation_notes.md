## Bernoulli's Principle

* Newton's second law to a fluid particle moving along a streamline

$$
\rho \, a_s = \sum \text{forces per unit volume}
$$

* Acceleration
$$
a_s = \frac{dv}{dt} = \frac{dv}{ds} \frac{ds}{dt} = v \frac{dv}{ds} = \frac{1}{2} \frac{d v^2}{ds}
$$

* Pressure gradient acts like a driving force, fluids accelerate from high pressure to low pressure
$$
f_p = -\frac{dp}{ds}
$$

* Gravity depends on slope: it accelerates the flow downhill and slows it uphill
$$
f_g = - \rho g \frac{dz}{ds}
$$

* We therfore have
$$
\rho \frac{1}{2} \frac{d v^2}{ds} = -\frac{dp}{ds}  - \rho g \frac{dz}{ds} 
$$
$$
\frac{d}{ds} \left( \rho \frac{v^2}{2} + p + \rho g z \right) = 0
$$

* By integrating along a streamline
$$
 \rho \frac{v^2}{2} + p + \rho g z  = \text{constant}
$$

## Flow rate

* Bernoulli's equation in between an upstream section and a point located at an elevation $y$ above the crest
$$
 \rho \frac{v_0^2}{2} + p_\mathrm{atm} + \rho g h_0  = \rho \frac{v(y)^2}{2} + p_\mathrm{atm} + \rho g y
$$
$$
 \rho g h_0  = \rho \frac{v(y)^2}{2} + \rho g y
$$
$$
v(y) = \sqrt{2 g \left( h_0 - y \right)}
$$

* By integrating the velocity from crest ($y=0$) to free surface ($y=h_0$)
$$
q^\prime = \int_0^{h_0}\sqrt{2g\,(h_0-y)}\,dy = \frac{2}{3}\sqrt{2g}\,h_0^{3/2}
$$