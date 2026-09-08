# Migrated analytic-continuation experiments

These files preserve the mathematical/domain experiments that were mixed into `isomorphismes/analytic-continuation` before the repositories were separated.

## Lasso / deformed domain

- `lasso/lasso_map.h` extracts the polynomial lasso map, analytic derivative, staged inverse, and derivative-budget calculation.
- `lasso/continuation.frag` is the final integrated lasso shader snapshot from `analytic-continuation` branch `lasso-mainline` / PR #21. It is intentionally historical: it contains the old app-local coloring implementation as it existed then.
- The corresponding full native activity remains immutably inspectable at `analytic-continuation` commit `0139b009e5fe226391cdec800356de7cf9d1a33f`, path `android/app/src/main/cpp/analytic_continuation.c`.

The lasso archive owns the deformed-domain idea: `phi(w) = w + c2 w^2 + ... + c6 w^6`, inverse continuation from the identity, derivative/univalence budgets, moving factor preimages, and Blaschke constructions tied to the deformed boundary.

## Overlapping convergence discs

- `convergence-disc/continuation.py` is the old closed-form disc planner, made structurally self-contained for the archive.
- `convergence-disc/continuation_path.h` is the old native rational nearest-pole path geometry.
- The historical Android implementation remains inspectable at `analytic-continuation` PR #7 / commit `7e2068ef02bd572b6a1fb012bd404a880a7de453`.

The disc planner and path header are geometry previews. They do not transport a Taylor germ. Branch/sheet/monodromy work is tracked separately in this repository.

## Unit-disc Bergman perturbation

[`bergman-disc/README.md`](bergman-disc/README.md) preserves the mathematics and exact source provenance of the historical normalized Bergman-kernel perturbation. The construction is canonical in the unit-disc Bergman norm, while its pole outside the disc prevents it from serving as an entire whole-plane perturbation for the current `analytic-continuation` explorer.

## Rendering ownership

Nothing archived here defines the current rendering contract. New Lacunary experiments that need phase portraits should consume reusable rendering preferences from `isomorphismes/wegert`, rather than reviving the old copied palette code in historical snapshots.
