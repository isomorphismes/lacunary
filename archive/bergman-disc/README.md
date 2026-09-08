# Historical unit-disc Bergman perturbation

## Classification

This is a **HISTORICAL EXPERIMENT** and valid bounded-domain construction. It demonstrates the general **MATHEMATICAL CONTRACT** that a continuous local datum in a declared reproducing-kernel Hilbert space has a unique minimum-norm representer. It is not the whole-plane perturbation space of the live [`analytic-continuation`](https://github.com/isomorphismes/analytic-continuation) app.

## Exact bounded-domain statement

Let `D = {z : |z| < 1}` and use the normalized Bergman norm

```text
||h||^2 = (1/pi) integral_D |h(z)|^2 dA(z).
```

The monomials `sqrt(n + 1) z^n` are orthonormal, hence

```text
K_D(z,a) = sum_(n >= 0) (n + 1) z^n conjugate(a)^n
         = 1 / (1 - conjugate(a) z)^2.
```

Point evaluation is continuous. The normalized reproducing representer

```text
phi_a(z) = K_D(z,a) / K_D(a,a)
         = (1 - |a|^2)^2 / (1 - conjugate(a) z)^2
```

satisfies `phi_a(a) = 1`. If `h(a) = 1`, then `h = phi_a + g` with `g(a) = 0`; the reproducing identity makes `g` orthogonal to `phi_a`. Consequently

```text
||h||^2 = ||phi_a||^2 + ||g||^2,
```

so `phi_a` is the unique minimum-Bergman-norm direction for that local value constraint. This is what “least disturbance” meant in the experiment. It did not mean minimum screen-wide RGB change.

The prototype used a pure phase datum

```text
g(z) = i alpha phi_a(z),
f_new(z) = f(z) exp(g(z)).
```

Within `D`, `g` is holomorphic and `exp(g)` is holomorphic and nonzero. The exact rendering increments are

```text
Delta log|f| = -alpha Im(phi_a),
Delta phase(f) = alpha Re(phi_a)  (mod 2 pi).
```

Finite sums of these disc-holomorphic directions remain holomorphic on the common disc.

## Why it is not a whole-plane descriptor

For `a != 0`, the denominator vanishes at

```text
z = 1 / conjugate(a),
```

whose modulus is greater than one. The pole lies outside `D`, so it does not invalidate the disc construction. It does invalidate an attempt to reinterpret `phi_a` as an entire function on `C`. For nonzero `alpha`, exponentiating the pole in `i alpha phi_a` produces an essential singularity there. The resulting factor is therefore not an admissible whole-plane `exp(q)` with entire `q`.

At `a = 0`, `phi_0 = 1` is entire but is a spatially constant global phase direction, not a localized whole-plane model.

The live whole-plane contract and the candidate entire Bargmann-Fock representers remain owned by [`analytic-continuation`](https://github.com/isomorphismes/analytic-continuation/blob/main/docs/holomorphic-mathematical-contract.md). Lacunary owns this bounded-domain provenance and any future chart, lasso, branch, sheet, or monodromy development.

## Implementation provenance

The recovered implementation is immutable in `analytic-continuation` commit [`52703c06d782cbfebb0b7f01d4ad0f949700233a`](https://github.com/isomorphismes/analytic-continuation/commit/52703c06d782cbfebb0b7f01d4ad0f949700233a), historical branch `local-holomorphic-perturbations`:

- `docs/local-holomorphic-perturbations.md` — original derivation and parameter notes;
- `android/app/src/main/cpp/perturbation_workers.c` — three descriptor workers plus the coordinator;
- `android/app/src/main/cpp/perturbation_render.c` — render snapshot and uniform handoff;
- `android/app/src/main/assets/continuation.frag` — full-panel kernel evaluation and exact phase/log-modulus increments;
- `tests/test_perturbation_workers.c` — historical descriptor checks.

The three useful descriptor workers plus a lightweight fourth coach/watch/coordinator (historically described as a cockswain) were a phone-CPU scheduling choice. The amplitudes, decay times, active count, anchor distribution, and cadence were visual/prototype choices. None is part of the Bergman extremal theorem.
