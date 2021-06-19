#pragma once

/// <summary>
/// Calculates a linearly-interpolated value between start and end, with t as the ratio.
/// </summary>
/// <param name="start">The initial value</param>
/// <param name="end">The target value</param>
/// <param name="t">The interpolation ratio</param>
/// <returns></returns>
float lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}