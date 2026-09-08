#ifndef LACUNARY_LASSO_MAP_H
#define LACUNARY_LASSO_MAP_H

/*
 * Mathematical core extracted from the historical lasso implementation in
 * isomorphismes/analytic-continuation.
 *
 * phi(w) = w + c2 w^2 + ... + c6 w^6
 *
 * The derivative budget was used as a sufficient injectivity guard on the
 * closed unit disc. Inversion follows the branch continuously from the
 * identity by staged Newton solves.
 */

#include <math.h>
#include <stdbool.h>

#define LACUNARY_LASSO_COEFFICIENT_COUNT 5

static void lacunary_complex_multiply(
    float left_x,
    float left_y,
    float right_x,
    float right_y,
    float output[2]
) {
    output[0] = left_x * right_x - left_y * right_y;
    output[1] = left_x * right_y + left_y * right_x;
}

static bool lacunary_complex_divide(
    float numerator_x,
    float numerator_y,
    float denominator_x,
    float denominator_y,
    float output[2]
) {
    float denominator = denominator_x * denominator_x + denominator_y * denominator_y;
    if (denominator < 1.0e-10f) {
        return false;
    }
    output[0] = (numerator_x * denominator_x + numerator_y * denominator_y) / denominator;
    output[1] = (numerator_y * denominator_x - numerator_x * denominator_y) / denominator;
    return true;
}

static void lacunary_lasso_map_with_coefficients(
    const float coefficients[LACUNARY_LASSO_COEFFICIENT_COUNT][2],
    float w_x,
    float w_y,
    float amount,
    float output[2],
    float derivative[2]
) {
    output[0] = w_x;
    output[1] = w_y;
    derivative[0] = 1.0f;
    derivative[1] = 0.0f;

    float power[2] = {w_x, w_y};
    for (int index = 0; index < LACUNARY_LASSO_COEFFICIENT_COUNT; ++index) {
        int degree = index + 2;
        float next_power[2];
        lacunary_complex_multiply(power[0], power[1], w_x, w_y, next_power);

        float mapped_term[2];
        lacunary_complex_multiply(
            coefficients[index][0], coefficients[index][1],
            next_power[0], next_power[1], mapped_term
        );
        output[0] += amount * mapped_term[0];
        output[1] += amount * mapped_term[1];

        float derivative_term[2];
        lacunary_complex_multiply(
            coefficients[index][0], coefficients[index][1],
            power[0], power[1], derivative_term
        );
        derivative[0] += amount * (float)degree * derivative_term[0];
        derivative[1] += amount * (float)degree * derivative_term[1];

        power[0] = next_power[0];
        power[1] = next_power[1];
    }
}

static bool lacunary_inverse_lasso_with_coefficients(
    const float coefficients[LACUNARY_LASSO_COEFFICIENT_COUNT][2],
    float z_x,
    float z_y,
    float output[2]
) {
    float w_x = z_x;
    float w_y = z_y;

    for (int stage = 1; stage <= 4; ++stage) {
        float amount = 0.25f * (float)stage;
        for (int iteration = 0; iteration < 4; ++iteration) {
            float mapped[2];
            float derivative[2];
            lacunary_lasso_map_with_coefficients(
                coefficients, w_x, w_y, amount, mapped, derivative
            );

            float correction[2];
            if (!lacunary_complex_divide(
                    mapped[0] - z_x, mapped[1] - z_y,
                    derivative[0], derivative[1], correction
                )) {
                return false;
            }

            float correction_length = hypotf(correction[0], correction[1]);
            if (correction_length > 0.55f) {
                float scale = 0.55f / correction_length;
                correction[0] *= scale;
                correction[1] *= scale;
            }
            w_x -= correction[0];
            w_y -= correction[1];
        }
    }

    float mapped[2];
    float derivative[2];
    lacunary_lasso_map_with_coefficients(
        coefficients, w_x, w_y, 1.0f, mapped, derivative
    );
    float residual = hypotf(mapped[0] - z_x, mapped[1] - z_y);
    output[0] = w_x;
    output[1] = w_y;
    return residual < 2.0e-3f;
}

static float lacunary_lasso_derivative_budget(
    const float coefficients[LACUNARY_LASSO_COEFFICIENT_COUNT][2]
) {
    float budget = 0.0f;
    for (int index = 0; index < LACUNARY_LASSO_COEFFICIENT_COUNT; ++index) {
        budget += (float)(index + 2) * hypotf(
            coefficients[index][0], coefficients[index][1]
        );
    }
    return budget;
}

#endif
