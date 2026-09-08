# Migrated analytic-continuation experiments

These files preserve mathematical pieces that were mixed into `isomorphismes/analytic-continuation` before the repositories were separated.

## Lasso / deformed domain

- `lasso/lasso_map.h` extracts the polynomial lasso map, analytic derivative, staged inverse, and derivative-budget calculation from the historical native implementation.
- Historical full Android implementations remain in `analytic-continuation` Git history at PR #10 / branch `lasso` and PR #21 / branch `lasso-mainline`.

## Overlapping convergence discs

- `convergence-disc/continuation.py` is the old closed-form disc planner.
- `convergence-disc/continuation_path.h` is the old native rational nearest-pole path geometry.
- Historical Android implementation: `analytic-continuation` PR #7 / branch `native_convergence_explorer`.

The disc planner and path header are geometry previews. They do not transport a Taylor germ. Branch/sheet/monodromy work is tracked separately in this repository.

Nothing here defines Wegert coloring. Rendering preferences remain owned by `isomorphismes/wegert` and should be consumed as reusable components when a Lacunary experiment needs them.
